#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

//#include "Property.h"
#include "MySqlOperator.h"
#include "Result.h"
#include "RedBall.h"
#include "BlueBall.h"
#include "StringUtil.h"
#include "Callpy.h"
#include "AccuracyTest.h"


AccuracyTest::AccuracyTest()
{
    mMyConfig = new MyConfig();
    mMySqlOperator = new MySqlOperator(mMyConfig);
    NUM_WEIGHT = mMyConfig->getNumWeight();
    WUXING_WEIGHT = mMyConfig->getWuxingWeight();
#ifdef DLT
    TABALE_LENGTH = mMyConfig->getDatabaseTableLength(TABLE_DLT);
#else
    TABALE_LENGTH = mMyConfig->getDatabaseTableLength(TABLE_SSQ);
#endif
}

AccuracyTest::~AccuracyTest()
{
    delete mMySqlOperator;
    delete mMyConfig;
}

void AccuracyTest::setNumAndWuxingWeight(float num, float wuxing)
{
    mMyConfig->setNumWeight(num);
    mMyConfig->setWuxingWeight(wuxing);
    printf("Set Weight: num_weight = %0.3f, wuxing_weight = %0.3f\n", num, wuxing);
}

void AccuracyTest::getCurNumAndWuxingWeight(float &num, float &wuxing)
{
    num = mMyConfig->getNumWeight();
    wuxing = mMyConfig->getWuxingWeight();
    printf("Get Current Weight: num_weight = %0.3f, wuxing_weight = %0.3f\n", num, wuxing);
}

Result* AccuracyTest::getResultFromDatabase(int id)
{
    std::string str;
    std::vector<std::string> rlines;
    std::vector<std::string> clines;
    Result *result;

    if(mMySqlOperator != NULL) {
        if(mMySqlOperator->ConnMySQL(HOST, PORT, DATABASE, USER, PASSWORD, CHARSET) == 0) {
#ifdef DLT
            str = mMySqlOperator->SelectData(TABLE_DLT, NULL, id, "ASC");
#else
            str = mMySqlOperator->SelectData(TABLE_SSQ, NULL, id, "ASC");
#endif

            if(!StringUtil::StringIsEmpty(str)) {
                StringUtil::StringSplit(rlines, str, COLUMN_G);
                StringUtil::StringSplit(clines, rlines[id - 1], COLUMN_G);
                int qid = atoi(clines[1].c_str());
                std::string date = clines[2];
                RedNumbers r1 = (RedNumbers) atoi(clines[3].c_str());
                RedNumbers r2 = (RedNumbers) atoi(clines[4].c_str());
                RedNumbers r3 = (RedNumbers) atoi(clines[5].c_str());
                RedNumbers r4 = (RedNumbers) atoi(clines[6].c_str());
                RedNumbers r5 = (RedNumbers) atoi(clines[7].c_str());
#ifdef DLT
                BlueNumbers b1 = (BlueNumbers) atoi(clines[8].c_str());
                BlueNumbers b2 = (BlueNumbers) atoi(clines[9].c_str());
                printf("LatestResultFromDatabase: qid=%d, date=%s, r1=%d, r2=%d, r3=%d, r4=%d, r5=%d, b1=%d, b2=%d\n", qid, date.c_str(), r1, r2, r3, r4, r5, b1, b2);
#else
                RedNumbers r6 = (RedNumbers) atoi(clines[8].c_str());
                BlueNumbers b0 = (BlueNumbers) atoi(clines[9].c_str());
                printf("LatestResultFromDatabase: qid=%d, date=%s, r1=%d, r2=%d, r3=%d, r4=%d, r5=%d, r6=%d, b0=%d\n", qid, date.c_str(), r1, r2, r3, r4, r5, r6, b0);
#endif
                result = new Result(new RedBall(r1, REDBALL_FIRST), new RedBall(r2, REDBALL_SECOND), new RedBall(r3, REDBALL_THIRD),
                                    new RedBall(r4, REDBALL_FOURTH), new RedBall(r5, REDBALL_FIFTH),
#ifdef DLT
                                    new BlueBall(b1, BLUEBALL_FIRST), new BlueBall(b2, BLUEBALL_SECOND));
#else
                                    new RedBall(r6, REDBALL_SIXTH), new BlueBall(b0, BLUEBALL_FIRST));
#endif
                result->setDate(date);
                result->setQid(qid);
            }
        }

        mMySqlOperator->CloseMySQLConn();
    }

    return result;
}

bool AccuracyTest::sortByPro(const resultStatistics &rs1, const resultStatistics &rs2)
{
    return rs1.probability > rs2.probability;
}

bool AccuracyTest::sortByPro1(const redballStatistics &rs1, const redballStatistics &rs2)
{
    return rs1.probability > rs2.probability;
}

bool AccuracyTest::sortByPro2(const blueballStatistics &bs1, const blueballStatistics &bs2)
{
    return bs1.probability > bs2.probability;
}

bool AccuracyTest::sortByCount(const wuxingStatistics &ws1, const wuxingStatistics &ws2)
{
    return ws1.count > ws2.count;
}

bool AccuracyTest::sortByCount1(const rnumStatistics &rs1, const rnumStatistics &rs2)
{
    return rs1.count > rs2.count;
}

bool AccuracyTest::sortByCount2(const bnumStatistics &bs1, const bnumStatistics &bs2)
{
    return bs1.count > bs2.count;
}

void AccuracyTest::rearrangePredictResult(std::vector<resultStatistics> *resultSta, int top)
{
    std::sort(resultSta->begin(), resultSta->end(), sortByPro);

    if(top != 0)
    { resultSta->erase(resultSta->begin() + top, resultSta->end()); }
}

std::vector<resultStatistics> AccuracyTest::getMaxProbabilityPredictResult(int id)
{
    Result* mResult = getResultFromDatabase(id);
    std::vector<resultStatistics> resultSta;
    std::vector<redballStatistics> rsta1 = calculateRedBallProbability(mResult->mR1, id);
    std::vector<redballStatistics> rsta2 = calculateRedBallProbability(mResult->mR2, id);
    std::vector<redballStatistics> rsta3 = calculateRedBallProbability(mResult->mR3, id);
    std::vector<redballStatistics> rsta4 = calculateRedBallProbability(mResult->mR4, id);
    std::vector<redballStatistics> rsta5 = calculateRedBallProbability(mResult->mR5, id);
#ifdef DLT
    std::vector<blueballStatistics> bsta1 = calculateBlueBallProbability(mResult->mB1, id);
    std::vector<blueballStatistics> bsta2 = calculateBlueBallProbability(mResult->mB2, id);
#else
    std::vector<redballStatistics> rsta6 = calculateRedBallProbability(mResult->mR6, id);
    std::vector<blueballStatistics> bsta = calculateBlueBallProbability(mResult->mB0, id);
#endif
    printf("start create resultStatistics...\n");

    for(int i = 0; i < (int)rsta1.size(); i++) {
        for(int j = 0; j < (int)rsta2.size(); j++) {
            for(int k = 0; k < (int)rsta3.size(); k++) {
                for(int m = 0; m < (int)rsta4.size(); m++) {
                    for(int n = 0; n < (int)rsta5.size(); n++) {
#ifdef DLT

                        for(int r = 0; r < (int)bsta1.size(); r++) {
                            for(int s = 0; s < (int)bsta2.size(); s++) {
                                if(rsta1[i].redball->mNum < rsta2[j].redball->mNum &&
                                    rsta2[j].redball->mNum < rsta3[k].redball->mNum &&
                                    rsta3[k].redball->mNum < rsta4[m].redball->mNum &&
                                    rsta4[m].redball->mNum < rsta5[n].redball->mNum &&
                                    bsta1[r].blueball->mNum < bsta2[s].blueball->mNum) {
                                    Result *result = new Result(rsta1[i].redball, rsta2[j].redball, rsta3[k].redball,
                                                                rsta4[m].redball, rsta5[n].redball, bsta1[r].blueball, bsta2[s].blueball);
                                    float prob = rsta1[i].probability + rsta2[j].probability + rsta3[k].probability + rsta4[m].probability
                                                 + rsta5[n].probability + bsta1[r].probability + bsta2[s].probability;
                                    resultStatistics sta;
                                    sta.result = result;
                                    sta.probability = prob;
                                    resultSta.push_back(sta);
                                }
                            }
                        }

#else

                        for(int r = 0; r < (int)rsta6.size(); r++) {
                            for(int s = 0; s < (int)bsta.size(); s++) {
                                if(rsta1[i].redball->mNum < rsta2[j].redball->mNum &&
                                    rsta2[j].redball->mNum < rsta3[k].redball->mNum &&
                                    rsta3[k].redball->mNum < rsta4[m].redball->mNum &&
                                    rsta4[m].redball->mNum < rsta5[n].redball->mNum &&
                                    rsta5[n].redball->mNum < rsta6[r].redball->mNum) {
                                    Result *result = new Result(rsta1[i].redball, rsta2[j].redball, rsta3[k].redball,
                                                                rsta4[m].redball, rsta5[n].redball, rsta6[r].redball, bsta[s].blueball);
                                    float prob = rsta1[i].probability + rsta2[j].probability + rsta3[k].probability + rsta4[m].probability
                                                 + rsta5[n].probability + rsta6[r].probability + bsta[s].probability;
                                    resultStatistics sta;
                                    sta.result = result;
                                    sta.probability = prob;
                                    resultSta.push_back(sta);
                                }
                            }
                        }

#endif
                    }
                }
            }
        }
    }

    printf("create resultStatistics complete!\n");
    rearrangePredictResult(&resultSta, 0);
    return resultSta;
}

std::vector<redballStatistics> AccuracyTest::calculateRedBallProbability(RedBall *rb, int id)
{
    std::vector<rnumStatistics> rnumList;
    std::vector<wuxingStatistics> wuxingList;
    std::vector<redballStatistics> rBallList;
    float PROBABILITY_METAL = 0;
    float PROBABILITY_WOOD = 0;
    float PROBABILITY_WATER = 0;
    float PROBABILITY_FIRE = 0;
    float PROBABILITY_EARTH = 0;
    float prob = 0;
    int total1 = 0, total2 = 0;
    calculateRedBallNumberAndWuxingProbability(id, rb, total1, total2, &rnumList, &wuxingList);

    for(int i = 0; i < (int)wuxingList.size(); i++) {
        switch(wuxingList[i].wuxing) {
            case METAL:
                PROBABILITY_METAL = (float)wuxingList[i].count / total2;
                break;

            case WOOD:
                PROBABILITY_WOOD = (float)wuxingList[i].count / total2;
                break;

            case WATER:
                PROBABILITY_WATER = (float)wuxingList[i].count / total2;
                break;

            case FIRE:
                PROBABILITY_FIRE = (float)wuxingList[i].count / total2;
                break;

            case EARTH:
                PROBABILITY_EARTH = (float)wuxingList[i].count / total2;
                break;

            default:
                break;
        }
    }

    for(int j = 0; j < (int)rnumList.size(); j++) {
        RedBall *redball = new RedBall(rnumList[j].rn);

        switch(redball->mWuxing) {
            case METAL:
                prob = (float) rnumList[j].count / total1 * NUM_WEIGHT + PROBABILITY_METAL * WUXING_WEIGHT;
                break;

            case WOOD:
                prob = (float) rnumList[j].count / total1 * NUM_WEIGHT + PROBABILITY_WOOD * WUXING_WEIGHT;
                break;

            case WATER:
                prob = (float) rnumList[j].count / total1 * NUM_WEIGHT + PROBABILITY_WATER * WUXING_WEIGHT;
                break;

            case FIRE:
                prob = (float) rnumList[j].count / total1 * NUM_WEIGHT + PROBABILITY_FIRE * WUXING_WEIGHT;
                break;

            case EARTH:
                prob = (float) rnumList[j].count / total1 * NUM_WEIGHT + PROBABILITY_EARTH * WUXING_WEIGHT;
                break;

            default:
                break;
        }

        redballStatistics rsta;
        rsta.redball = redball;
        rsta.probability = prob;
        rBallList.push_back(rsta);
    }

    std::sort(rBallList.begin(), rBallList.end(), sortByPro1);
    return rBallList;
}

std::vector<blueballStatistics> AccuracyTest::calculateBlueBallProbability(BlueBall *bb, int id)
{
    std::vector<bnumStatistics> bnumList;
    std::vector<wuxingStatistics> wuxingList;
    std::vector<blueballStatistics> bBallList;
    float PROBABILITY_METAL = 0;
    float PROBABILITY_WOOD = 0;
    float PROBABILITY_WATER = 0;
    float PROBABILITY_FIRE = 0;
    float PROBABILITY_EARTH = 0;
    float prob = 0;
    int total1 = 0, total2 = 0;
    calculateBlueBallNumberAndWuxingProbability(id, bb, total1, total2, &bnumList, &wuxingList);

    for(int i = 0; i < (int)wuxingList.size(); i++) {
        switch(wuxingList[i].wuxing) {
            case METAL:
                PROBABILITY_METAL = (float)wuxingList[i].count / total2;
                break;

            case WOOD:
                PROBABILITY_WOOD = (float)wuxingList[i].count / total2;
                break;

            case WATER:
                PROBABILITY_WATER = (float)wuxingList[i].count / total2;
                break;

            case FIRE:
                PROBABILITY_FIRE = (float)wuxingList[i].count / total2;
                break;

            case EARTH:
                PROBABILITY_EARTH = (float)wuxingList[i].count / total2;
                break;

            default:
                break;
        }
    }

    for(int j = 0; j < (int)bnumList.size(); j++) {
        BlueBall *blueball = new BlueBall(bnumList[j].bn);

        switch(blueball->mWuxing) {
            case METAL:
                prob = (float) bnumList[j].count / total1 * NUM_WEIGHT + PROBABILITY_METAL * WUXING_WEIGHT;
                break;

            case WOOD:
                prob = (float) bnumList[j].count / total1 * NUM_WEIGHT + PROBABILITY_WOOD * WUXING_WEIGHT;
                break;

            case WATER:
                prob = (float) bnumList[j].count / total1 * NUM_WEIGHT + PROBABILITY_WATER * WUXING_WEIGHT;
                break;

            case FIRE:
                prob = (float) bnumList[j].count / total1 * NUM_WEIGHT + PROBABILITY_FIRE * WUXING_WEIGHT;
                break;

            case EARTH:
                prob = (float) bnumList[j].count / total1 * NUM_WEIGHT + PROBABILITY_EARTH * WUXING_WEIGHT;
                break;

            default:
                break;
        }

        blueballStatistics bsta;
        bsta.blueball = blueball;
        bsta.probability = prob;
        bBallList.push_back(bsta);
    }

    std::sort(bBallList.begin(), bBallList.end(), sortByPro2);
    return bBallList;
}

int AccuracyTest::calculateRedBallNumberAndWuxingProbability(int id, RedBall *rb, int &total_rnum, int &total_wuxing,
                                                             std::vector<rnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList)
{
    RedNumbers num = rb->mNum;
    Elememts wuxing = rb->mWuxing;
    BallType ballType = rb->mBalltype;
    std::vector<RedBall*> mList = getRedBallListFromDatabase(Balltype2FieldName(ballType), id);

    for(int i = 0; i < (int)mList.size() - 1; i++) {
        if(num == mList[i]->mNum) {
            if((int)staList->size() == 0) {
                rnumStatistics sta;
                sta.rn = mList[i + 1]->mNum;
                sta.count = 1;
                staList->push_back(sta);
            } else {
                bool exist = false;

                for(int j = 0; j < (int)staList->size(); j++) {
                    if(mList[i + 1]->mNum == staList->at(j).rn) {
                        staList->at(j).count ++;
                        exist = true;
                        break;
                    }
                }

                if(!exist) {
                    rnumStatistics sta;
                    sta.rn = mList[i + 1]->mNum;
                    sta.count = 1;
                    staList->push_back(sta);
                }
            }

            total_rnum++;
        }

        if(wuxing == mList[i]->mWuxing) {
            if((int)wuxingList->size() == 0) {
                wuxingStatistics sta;
                sta.wuxing = mList[i + 1]->mWuxing;
                sta.count = 1;
                wuxingList->push_back(sta);
            } else {
                bool found = false;

                for(int j = 0; j < (int) wuxingList->size(); j++) {
                    if(mList[i + 1]->mWuxing == wuxingList->at(j).wuxing) {
                        wuxingList->at(j).count ++;
                        found = true;
                        break;
                    }
                }

                if(!found) {
                    wuxingStatistics sta;
                    sta.wuxing = mList[i + 1]->mWuxing;
                    sta.count = 1;
                    wuxingList->push_back(sta);
                }
            }

            total_wuxing++;
        }
    }

    std::sort(staList->begin(), staList->end(), sortByCount1);
    std::sort(wuxingList->begin(), wuxingList->end(), sortByCount);
}

int AccuracyTest::calculateBlueBallNumberAndWuxingProbability(int id, BlueBall *bb, int &total_bnum, int &total_wuxing,
                                                              std::vector<bnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList)
{
    BlueNumbers num = bb->mNum;
    Elememts wuxing = bb->mWuxing;
    BallType ballType = bb->mBalltype;
    std::vector<BlueBall*> mList = getBlueBallListFromDatabase(Balltype2FieldName(ballType), id);

    for(int i = 0; i < (int)mList.size() - 1; i++) {
        if(num == mList[i]->mNum) {
            if((int)staList->size() == 0) {
                bnumStatistics sta;
                sta.bn = mList[i + 1]->mNum;
                sta.count = 1;
                staList->push_back(sta);
            } else {
                bool exist = false;

                for(int j = 0; j < (int)staList->size(); j++) {
                    if(mList[i + 1]->mNum == staList->at(j).bn) {
                        staList->at(j).count ++;
                        exist = true;
                        break;
                    }
                }

                if(!exist) {
                    bnumStatistics sta;
                    sta.bn = mList[i + 1]->mNum;
                    sta.count = 1;
                    staList->push_back(sta);
                }
            }

            total_bnum++;
        }

        if(wuxing == mList[i]->mWuxing) {
            if((int)wuxingList->size() == 0) {
                wuxingStatistics sta;
                sta.wuxing = mList[i + 1]->mWuxing;
                sta.count = 1;
                wuxingList->push_back(sta);
            } else {
                bool found = false;

                for(int j = 0; j < (int)wuxingList->size(); j++) {
                    if(mList[i + 1]->mWuxing == wuxingList->at(j).wuxing) {
                        wuxingList->at(j).count ++;
                        found = true;
                        break;
                    }
                }

                if(!found) {
                    wuxingStatistics sta;
                    sta.wuxing = mList[i + 1]->mWuxing;
                    sta.count = 1;
                    wuxingList->push_back(sta);
                }
            }

            total_wuxing++;
        }
    }

    std::sort(staList->begin(), staList->end(), sortByCount2);
    std::sort(wuxingList->begin(), wuxingList->end(), sortByCount);
}

std::vector<RedBall*> AccuracyTest::getRedBallListFromDatabase(char *field, int id)
{
    std::vector<RedBall*> redList;
    std::vector<std::string> lines;
    std::string str;

    if(mMySqlOperator != NULL) {
        if(mMySqlOperator->ConnMySQL(HOST, PORT, DATABASE, USER, PASSWORD, CHARSET) == 0) {
#ifdef DLT
            str = mMySqlOperator->SelectData(TABLE_DLT, field, id, "ASC");
#else
            str = mMySqlOperator->SelectData(TABLE_SSQ, field, id, "ASC");
#endif

            if(!StringUtil::StringIsEmpty(str)) {
                StringUtil::StringSplit(lines, str, CR_G);

                for(int i = id - 500; i < (int)lines.size(); i++) {
                    RedNumbers rn = (RedNumbers) atoi(lines[i].c_str());
                    RedBall *rb = new RedBall(rn);
                    redList.push_back(rb);
                }
            }
        }

        mMySqlOperator->CloseMySQLConn();
    }

    return redList;
}

std::vector<BlueBall*> AccuracyTest::getBlueBallListFromDatabase(char *field, int id)
{
    std::vector<BlueBall*> blueList;
    std::vector<std::string> lines;
    std::string str;

    if(mMySqlOperator != NULL) {
        if(mMySqlOperator->ConnMySQL(HOST, PORT, DATABASE, USER, PASSWORD, CHARSET) == 0) {
#ifdef DLT
            str = mMySqlOperator->SelectData(TABLE_DLT, field, id, "ASC");
#else
            str = mMySqlOperator->SelectData(TABLE_SSQ, field, id, "ASC");
#endif

            if(!StringUtil::StringIsEmpty(str)) {
                StringUtil::StringSplit(lines, str, CR_G);

                for(int i = id - 500; i < (int)lines.size(); i++) {
                    BlueNumbers bn = (BlueNumbers) atoi(lines[i].c_str());
                    BlueBall *bb = new BlueBall(bn);
                    blueList.push_back(bb);
                }
            }
        }

        mMySqlOperator->CloseMySQLConn();
    }

    return blueList;
}

/* level 0: all the balls same
 * level 1: only the red balls same
 */
bool AccuracyTest::is2ResultsEqual(Result *r1, Result *r2, int level)
{
    bool same = (r1->mR1->mNum == r2->mR1->mNum && r1->mR2->mNum == r2->mR2->mNum &&
                 r1->mR3->mNum == r2->mR3->mNum && r1->mR4->mNum == r2->mR4->mNum && r1->mR5->mNum == r2->mR5->mNum
#ifndef DLT
                 && r1->mR6->mNum == r2->mR6->mNum
#endif
                );

    if(level == 0) {
#ifdef DLT
        return same && r1->mB1->mNum == r2->mB1->mNum && r1->mB2->mNum == r2->mB2->mNum;
#else
        return same && r1->mB0->mNum == r2->mB0->mNum;
#endif
    } else if (level == 1) {
        return same;
    } else {
        printf("Invalid level!\n");
        return false;
    }
}


std::vector<float> AccuracyTest::getAccuracyForDifferentWeight(float num_wt, float wuxing_wt)
{
    NUM_WEIGHT = num_wt;
    WUXING_WEIGHT = wuxing_wt;
    std::vector<float> mList;

    for(int i = 500; i < TABALE_LENGTH; i++) {
        std::vector<resultStatistics> rsta = getMaxProbabilityPredictResult(i);
        Result* actualResult = getResultFromDatabase(i + 1);
        float accuracy = 1.0;

        for(int j = 0; j < (int)rsta.size(); j++) {
            if(is2ResultsEqual(actualResult, rsta[j].result, 0)) {
                accuracy = (float)j / (int)rsta.size();
                break;
            }
        }

        mList.push_back(accuracy);
    }

    return mList;
}

void AccuracyTest::startAccuracyTest()
{
    for(int i = 1; i < 10; i++) {
        float num = (float) i * 0.1;
        float wuxing = 1.0 - num;
        std::vector<float> aList = getAccuracyForDifferentWeight(num, wuxing);
        writeAccuracyData2ExcelFile(aList);
    }
}

void AccuracyTest::writeAccuracyData2ExcelFile(std::vector<float> accuList)
{
}
