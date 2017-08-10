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
#include "Algorithm.h"
#include "MySqlOperator.h"
#include "Result.h"
#include "RedBall.h"
#include "BlueBall.h"
#include "StringUtil.h"
#include "Callpy.h"


Algorithm::Algorithm(sptr(MySqlOperator) mysqloperator, sptr(MyConfig) myconfig)
{
    mMyConfig = myconfig;
    mMySqlOperator = mysqloperator;
    NUM_WEIGHT = mMyConfig->getNumWeight();
    WUXING_WEIGHT = mMyConfig->getWuxingWeight();
}

Algorithm::~Algorithm()
{
}

void Algorithm::setNumAndWuxingWeight(float num, float wuxing)
{
    mMyConfig->setNumWeight(num);
    mMyConfig->setWuxingWeight(wuxing);
    printf("Set Weight: num_weight = %0.3f, wuxing_weight = %0.3f\n", num, wuxing);
}

void Algorithm::getCurNumAndWuxingWeight(float &num, float &wuxing)
{
    num = mMyConfig->getNumWeight();
    wuxing = mMyConfig->getWuxingWeight();
    printf("Get Current Weight: num_weight = %0.3f, wuxing_weight = %0.3f\n", num, wuxing);
}

bool Algorithm::updateDatabase()
{
    mLatestResult = getLatestResultFromDatabase();
    int qid = mLatestResult->getQid();
    char cqid[128];
    sprintf(cqid, "%d", qid);
    sptr(Callpy) py = make(Callpy);
    int res = py->runPythonFunction(std::string("update_database"), std::string("1") + std::string("\n") + std::string(cqid) + std::string("\n"));

    if(res == 0) {
        mLatestResult = getLatestResultFromDatabase();
        writeActualLatestResult2LastPredictFile();
        return true;
    } else if(res == -2) {
        printf("Database already updated to latest!\n");
        return true;
    } else {
        return false;
    }
}

sptr(Result) Algorithm::getLatestResultFromDatabase()
{
    std::string str;
    std::vector<std::string> lines;
    sptr(Result) result;

    if(mMySqlOperator != NULL) {
        if(mMySqlOperator->ConnMySQL(HOST, PORT, DATABASE, USER, PASSWORD, CHARSET) == 0) {
#ifdef DLT
            str = mMySqlOperator->SelectData(TABLE_DLT, NULL, 1);
#else
            str = mMySqlOperator->SelectData(TABLE_SSQ, NULL, 1);
#endif

            if(!StringUtil::StringIsEmpty(str)) {
                StringUtil::StringSplit(lines, str, COLUMN_G);
                int qid = atoi(lines[1].c_str());
                std::string date = lines[2];
                RedNumbers r1 = (RedNumbers) atoi(lines[3].c_str());
                RedNumbers r2 = (RedNumbers) atoi(lines[4].c_str());
                RedNumbers r3 = (RedNumbers) atoi(lines[5].c_str());
                RedNumbers r4 = (RedNumbers) atoi(lines[6].c_str());
                RedNumbers r5 = (RedNumbers) atoi(lines[7].c_str());
#ifdef DLT
                BlueNumbers b1 = (BlueNumbers) atoi(lines[8].c_str());
                BlueNumbers b2 = (BlueNumbers) atoi(lines[9].c_str());
                printf("LatestResultFromDatabase: qid=%d, date=%s, r1=%d, r2=%d, r3=%d, r4=%d, r5=%d, b1=%d, b2=%d\n", qid, date.c_str(), r1, r2, r3, r4, r5, b1, b2);
#else
                RedNumbers r6 = (RedNumbers) atoi(lines[8].c_str());
                BlueNumbers b0 = (BlueNumbers) atoi(lines[9].c_str());
                printf("LatestResultFromDatabase: qid=%d, date=%s, r1=%d, r2=%d, r3=%d, r4=%d, r5=%d, r6=%d, b0=%d\n", qid, date.c_str(), r1, r2, r3, r4, r5, r6, b0);
#endif
                result = make(Result, make(RedBall, r1, REDBALL_FIRST), make(RedBall, r2, REDBALL_SECOND), make(RedBall, r3, REDBALL_THIRD),
                              make(RedBall, r4, REDBALL_FOURTH), make(RedBall, r5, REDBALL_FIFTH),
#ifdef DLT
                              make(BlueBall, b1, BLUEBALL_FIRST), make(BlueBall, b2, BLUEBALL_SECOND));
#else
                              make(RedBall, r6, REDBALL_SIXTH), make(BlueBall, b0, BLUEBALL_FIRST));
#endif
                result->setDate(date);
                result->setQid(qid);
            }
        }

        mMySqlOperator->CloseMySQLConn();
    }

    return result;
}

bool Algorithm::sortByPro(const resultStatistics &rs1, const resultStatistics &rs2)
{
    return rs1.probability > rs2.probability;
}

bool Algorithm::sortByPro1(const redballStatistics &rs1, const redballStatistics &rs2)
{
    return rs1.probability > rs2.probability;
}

bool Algorithm::sortByPro2(const blueballStatistics &bs1, const blueballStatistics &bs2)
{
    return bs1.probability > bs2.probability;
}

bool Algorithm::sortByCount(const wuxingStatistics &ws1, const wuxingStatistics &ws2)
{
    return ws1.count > ws2.count;
}

bool Algorithm::sortByCount1(const rnumStatistics &rs1, const rnumStatistics &rs2)
{
    return rs1.count > rs2.count;
}

bool Algorithm::sortByCount2(const bnumStatistics &bs1, const bnumStatistics &bs2)
{
    return bs1.count > bs2.count;
}

void Algorithm::rearrangePredictResult(std::vector<resultStatistics> *resultSta, int top)
{
    std::sort(resultSta->begin(), resultSta->end(), sortByPro);
    resultSta->erase(resultSta->begin() + top, resultSta->end());
}

std::string Algorithm::printPredictResult(std::vector<resultStatistics> resultSta)
{
    std::string content = "\n";
    char temp[512];
    memset(temp, 0, 512);

    for(int i = 0; i < (int)resultSta.size(); i++) {
        sptr(Result) result = resultSta[i].result;
        RedNumbers rnum1 = result->mR1->mNum;
        RedNumbers rnum2 = result->mR2->mNum;
        RedNumbers rnum3 = result->mR3->mNum;
        RedNumbers rnum4 = result->mR4->mNum;
        RedNumbers rnum5 = result->mR5->mNum;
#ifdef DLT
        BlueNumbers bnum1 = result->mB1->mNum;
        BlueNumbers bnum2 = result->mB2->mNum;
        sprintf(temp, "PredictResult[%02d] %02d %02d %02d %02d %02d + %02d %02d  probability = %0.3f\n", i + 1, rnum1, rnum2, rnum3, rnum4, rnum5, bnum1, bnum2, resultSta[i].probability);
#else
        RedNumbers rnum6 = result->mR6->mNum;
        BlueNumbers bnum = result->mB0->mNum;
        sprintf(temp, "PredictResult[%02d] %02d %02d %02d %02d %02d %02d + %02d  probability = %0.3f\n", i + 1, rnum1, rnum2, rnum3, rnum4, rnum5, rnum6, bnum, resultSta[i].probability);
#endif
        content += std::string(temp);
        memset(temp, 0, 512);
    }

    printf("%s", content.c_str());
    return content;
}

std::vector<resultStatistics> Algorithm::getMaxProbabilityPredictResult(int top)
{
    std::vector<resultStatistics> resultSta;
    std::string printContent = "";
    std::string tempBuf = "";
    std::vector<redballStatistics> rsta1 = calculateRedBallProbability(mLatestResult->mR1, tempBuf);
    printContent += tempBuf;
    tempBuf = "";
    std::vector<redballStatistics> rsta2 = calculateRedBallProbability(mLatestResult->mR2, tempBuf);
    printContent += tempBuf;
    tempBuf = "";
    std::vector<redballStatistics> rsta3 = calculateRedBallProbability(mLatestResult->mR3, tempBuf);
    printContent += tempBuf;
    tempBuf = "";
    std::vector<redballStatistics> rsta4 = calculateRedBallProbability(mLatestResult->mR4, tempBuf);
    printContent += tempBuf;
    tempBuf = "";
    std::vector<redballStatistics> rsta5 = calculateRedBallProbability(mLatestResult->mR5, tempBuf);
    printContent += tempBuf;
    tempBuf = "";
#ifdef DLT
    std::vector<blueballStatistics> bsta1 = calculateBlueBallProbability(mLatestResult->mB1, tempBuf);
    printContent += tempBuf;
    tempBuf = "";
    std::vector<blueballStatistics> bsta2 = calculateBlueBallProbability(mLatestResult->mB2, tempBuf);
    printContent += tempBuf;
    tempBuf = "";
#else
    std::vector<redballStatistics> rsta6 = calculateRedBallProbability(mLatestResult->mR6, tempBuf);
    printContent += tempBuf;
    tempBuf = "";
    std::vector<blueballStatistics> bsta = calculateBlueBallProbability(mLatestResult->mB0, tempBuf);
    printContent += tempBuf;
    tempBuf = "";
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
                                    sptr(Result) result = make(Result, rsta1[i].redball, rsta2[j].redball, rsta3[k].redball,
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
                                    sptr(Result) result = make(Result, rsta1[i].redball, rsta2[j].redball, rsta3[k].redball,
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
    //printPredictResult(resultSta);// before reaffange
    rearrangePredictResult(&resultSta, top);
    tempBuf = printPredictResult(resultSta);// after reaffange
    printContent += tempBuf;
    writeLatestPredictResult2File(printContent);
    return resultSta;
}

std::vector<redballStatistics> Algorithm::calculateRedBallProbability(sptr(RedBall) rb, std::string &content)
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
    //int total1 = calculateRedBallNumberProbability(ballType, &rnumList);
    //int total2 = calculateBallWuxingProbability(ballType, wuxingList);
    int total1 = 0, total2 = 0;
    calculateRedBallNumberAndWuxingProbability(rb, total1, total2, &rnumList, &wuxingList);

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
        sptr(RedBall) redball = make(RedBall, rnumList[j].rn);

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
    content = printRedballPredictTable(rb->mBalltype, rnumList, wuxingList, rBallList);
    return rBallList;
}

std::vector<blueballStatistics> Algorithm::calculateBlueBallProbability(sptr(BlueBall) bb, std::string &content)
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
    //int total1 = calculateBlueBallNumberProbability(ballType, bnumList);
    //int total2 = calculateBallWuxingProbability(ballType, wuxingList);
    int total1 = 0, total2 = 0;
    calculateBlueBallNumberAndWuxingProbability(bb, total1, total2, &bnumList, &wuxingList);

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
        sptr(BlueBall) blueball = make(BlueBall, bnumList[j].bn);

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
    content = printBlueballPredictTable(bb->mBalltype, bnumList, wuxingList, bBallList);
    return bBallList;
}

void Algorithm::comparePredictResultWithActualResult()
{
}

void Algorithm::printRedballNumberProbability(std::vector<rnumStatistics> *sta, int total, BallType ballType)
{
    std::string title = getLogTitleFromBalltype(ballType);

    for(int i = 0; i < (int)sta->size(); i++) {
        printf("%s [%02d] : num = %d, count = %d, probability = %0.3f\n", title.c_str(), i + 1, sta->at(i).rn, sta->at(i).count, (float)sta->at(i).count / total);
    }
}

void Algorithm::printBlueballNumberProbability(std::vector<bnumStatistics> *sta, int total, BallType ballType)
{
    std::string title = getLogTitleFromBalltype(ballType);

    for(int i = 0; i < (int)sta->size(); i++) {
        printf("%s [%02d] : num = %d, count = %d, probability = %0.3f\n", title.c_str(), i + 1, sta->at(i).bn, sta->at(i).count, (float)sta->at(i).count / total);
    }
}

void Algorithm::printBallWuxingProbability(std::vector<wuxingStatistics> *sta, int total, BallType ballType)
{
    std::string title = getLogTitleFromBalltype(ballType);

    for(int i = 0; i < (int)sta->size(); i++) {
        printf("%s [%02d] : wuxing = %s, count = %d, probability = %0.3f\n", title.c_str(), i + 1, Elememts2String(sta->at(i).wuxing).c_str(), sta->at(i).count, (float)sta->at(i).count / total);
    }
}

int Algorithm::calculateRedBallNumberAndWuxingProbability(sptr(RedBall) rb, int &total_rnum, int &total_wuxing,
                                                          std::vector<rnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList)
{
    RedNumbers num = rb->mNum;
    Elememts wuxing = rb->mWuxing;
    BallType ballType = rb->mBalltype;
    std::vector< sptr(RedBall) > mList = getRedBallListFromDatabase(Balltype2FieldName(ballType), 500);

    for(int i = (int)mList.size() - 1; i > 0; i--) {
        if(num == mList[i]->mNum) {
            if((int)staList->size() == 0) {
                rnumStatistics sta;
                sta.rn = mList[i - 1]->mNum;
                sta.count = 1;
                staList->push_back(sta);
            } else {
                bool exist = false;

                for(int j = 0; j < (int)staList->size(); j++) {
                    if(mList[i - 1]->mNum == staList->at(j).rn) {
                        staList->at(j).count ++;
                        exist = true;
                        break;
                    }
                }

                if(!exist) {
                    rnumStatistics sta;
                    sta.rn = mList[i - 1]->mNum;
                    sta.count = 1;
                    staList->push_back(sta);
                }
            }

            total_rnum++;
        }

        if(wuxing == mList[i]->mWuxing) {
            if((int)wuxingList->size() == 0) {
                wuxingStatistics sta;
                sta.wuxing = mList[i - 1]->mWuxing;
                sta.count = 1;
                wuxingList->push_back(sta);
            } else {
                bool found = false;

                for(int j = 0; j < (int) wuxingList->size(); j++) {
                    if(mList[i - 1]->mWuxing == wuxingList->at(j).wuxing) {
                        wuxingList->at(j).count ++;
                        found = true;
                        break;
                    }
                }

                if(!found) {
                    wuxingStatistics sta;
                    sta.wuxing = mList[i - 1]->mWuxing;
                    sta.count = 1;
                    wuxingList->push_back(sta);
                }
            }

            total_wuxing++;
        }
    }

    std::sort(staList->begin(), staList->end(), sortByCount1);
    std::sort(wuxingList->begin(), wuxingList->end(), sortByCount);
    //printRedballNumberProbability(staList, total_rnum, ballType);
    //printBallWuxingProbability(wuxingList, total_wuxing, ballType);
}

int Algorithm::calculateBlueBallNumberAndWuxingProbability(sptr(BlueBall) bb, int &total_bnum, int &total_wuxing,
                                                           std::vector<bnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList)
{
    BlueNumbers num = bb->mNum;
    Elememts wuxing = bb->mWuxing;
    BallType ballType = bb->mBalltype;
    std::vector< sptr(BlueBall) > mList = getBlueBallListFromDatabase(Balltype2FieldName(ballType), 500);

    for(int i = (int)mList.size() - 1; i > 0; i--) {
        if(num == mList[i]->mNum) {
            if((int)staList->size() == 0) {
                bnumStatistics sta;
                sta.bn = mList[i - 1]->mNum;
                sta.count = 1;
                staList->push_back(sta);
            } else {
                bool exist = false;

                for(int j = 0; j < (int)staList->size(); j++) {
                    if(mList[i - 1]->mNum == staList->at(j).bn) {
                        staList->at(j).count ++;
                        exist = true;
                        break;
                    }
                }

                if(!exist) {
                    bnumStatistics sta;
                    sta.bn = mList[i - 1]->mNum;
                    sta.count = 1;
                    staList->push_back(sta);
                }
            }

            total_bnum++;
        }

        if(wuxing == mList[i]->mWuxing) {
            if((int)wuxingList->size() == 0) {
                wuxingStatistics sta;
                sta.wuxing = mList[i - 1]->mWuxing;
                sta.count = 1;
                wuxingList->push_back(sta);
            } else {
                bool found = false;

                for(int j = 0; j < (int)wuxingList->size(); j++) {
                    if(mList[i - 1]->mWuxing == wuxingList->at(j).wuxing) {
                        wuxingList->at(j).count ++;
                        found = true;
                        break;
                    }
                }

                if(!found) {
                    wuxingStatistics sta;
                    sta.wuxing = mList[i - 1]->mWuxing;
                    sta.count = 1;
                    wuxingList->push_back(sta);
                }
            }

            total_wuxing++;
        }
    }

    std::sort(staList->begin(), staList->end(), sortByCount2);
    std::sort(wuxingList->begin(), wuxingList->end(), sortByCount);
    //printBlueballNumberProbability(staList, total_bnum, ballType);
    //printBallWuxingProbability(wuxingList, total_wuxing, ballType);
}

std::vector< sptr(RedBall) > Algorithm::getRedBallListFromDatabase(char *field, int rnum)
{
    std::vector< sptr(RedBall) > redList;
    std::vector<std::string> lines;
    std::string str;

    if(mMySqlOperator != NULL) {
        if(mMySqlOperator->ConnMySQL(HOST, PORT, DATABASE, USER, PASSWORD, CHARSET) == 0) {
#ifdef DLT
            str = mMySqlOperator->SelectData(TABLE_DLT, field, rnum);
#else
            str = mMySqlOperator->SelectData(TABLE_SSQ, field, rnum);
#endif

            if(!StringUtil::StringIsEmpty(str)) {
                StringUtil::StringSplit(lines, str, CR_G);

                for(int i = 0; i < (int)lines.size(); i++) {
                    RedNumbers rn = (RedNumbers) atoi(lines[i].c_str());
                    sptr(RedBall) rb = make(RedBall, rn);
                    redList.push_back(rb);
                }
            }
        }

        mMySqlOperator->CloseMySQLConn();
    }

    return redList;
}

std::vector< sptr(BlueBall) > Algorithm::getBlueBallListFromDatabase(char *field, int rnum)
{
    std::vector< sptr(BlueBall) > blueList;
    std::vector<std::string> lines;
    std::string str;

    if(mMySqlOperator != NULL) {
        if(mMySqlOperator->ConnMySQL(HOST, PORT, DATABASE, USER, PASSWORD, CHARSET) == 0) {
#ifdef DLT
            str = mMySqlOperator->SelectData(TABLE_DLT, field, rnum);
#else
            str = mMySqlOperator->SelectData(TABLE_SSQ, field, rnum);
#endif

            if(!StringUtil::StringIsEmpty(str)) {
                StringUtil::StringSplit(lines, str, CR_G);

                for(int i = 0; i < (int)lines.size(); i++) {
                    BlueNumbers bn = (BlueNumbers) atoi(lines[i].c_str());
                    sptr(BlueBall) bb = make(BlueBall, bn);
                    blueList.push_back(bb);
                }
            }
        }

        mMySqlOperator->CloseMySQLConn();
    }

    return blueList;
}

std::string Algorithm::printRedballPredictTable(BallType type, std::vector<rnumStatistics> rsList,
                                                std::vector<wuxingStatistics> wsList, std::vector<redballStatistics> rbList)
{
    int sort = 0;
    std::string buf;
    char temp[256];
    memset(temp, 0, 256);
    sprintf(temp, "%s| wuxing |", Balltype2FieldName(type));
    buf += std::string(temp);
    memset(temp, 0, 256);

    for(int i = 0; i < (int)wsList.size(); i++) {
        sprintf(temp, " %5s |", Elememts2String(wsList[i].wuxing).c_str());
        buf += std::string(temp);
        memset(temp, 0, 256);
    }

    buf += std::string("\n");
    sprintf(temp, "%s", "num|  count |");
    buf += std::string(temp);
    memset(temp, 0, 256);

    for(int j = 0; j < (int)wsList.size(); j++) {
        sprintf(temp, "   %02d  |", wsList[j].count);
        buf += std::string(temp);
        memset(temp, 0, 256);
    }

    buf += std::string("\n");

    for(int k = 0; k < (int)rsList.size(); k++) {
        memset(temp, 0, 256);
        sprintf(temp, "%02d |   %02d   |", rsList[k].rn, rsList[k].count);
        buf += std::string(temp);

        for(int m = 0; m < (int)wsList.size(); m++) {
            if(RedNumber2Elememt(rsList[k].rn) == wsList[m].wuxing) {
                for(int n = 0; n < (int)rbList.size(); n++) {
                    if(rbList[n].redball->mNum == rsList[k].rn) {
                        memset(temp, 0, 256);
                        sprintf(temp, " %0.3f |", rbList[n].probability);
                        buf += std::string(temp);
                        sort = n + 1;
                    }
                }
            } else {
                memset(temp, 0, 256);
                sprintf(temp, "%s", "	    |");
                buf += std::string(temp);
            }
        }

        memset(temp, 0, 256);
        sprintf(temp, " %02d |\n", sort);
        buf += std::string(temp);
    }

    printf("%s", buf.c_str());
    return buf;
}

std::string Algorithm::printBlueballPredictTable(BallType type, std::vector<bnumStatistics> bsList,
                                                 std::vector<wuxingStatistics> wsList, std::vector<blueballStatistics> bbList)
{
    int sort = 0;
    std::string buf;
    char temp[256];
    memset(temp, 0, 256);
    sprintf(temp, "%s | wuxing |", Balltype2FieldName(type));
    buf += std::string(temp);
    memset(temp, 0, 256);

    for(int i = 0; i < (int)wsList.size(); i++) {
        sprintf(temp, " %5s |", Elememts2String(wsList[i].wuxing).c_str());
        buf += std::string(temp);
        memset(temp, 0, 256);
    }

    buf += std::string("\n");
    sprintf(temp, "%s", "num|  count |");
    buf += std::string(temp);
    memset(temp, 0, 256);

    for(int j = 0; j < (int)wsList.size(); j++) {
        sprintf(temp, "   %02d  |", wsList[j].count);
        buf += std::string(temp);
        memset(temp, 0, 256);
    }

    buf += std::string("\n");

    for(int k = 0; k < (int)bsList.size(); k++) {
        memset(temp, 0, 256);
        sprintf(temp, "%02d |   %02d   |", bsList[k].bn, bsList[k].count);
        buf += std::string(temp);

        for(int m = 0; m < (int)wsList.size(); m++) {
            if(BlueNumber2Elememt(bsList[k].bn) == wsList[m].wuxing) {
                for(int n = 0; n < (int)bbList.size(); n++) {
                    if(bbList[n].blueball->mNum == bsList[k].bn) {
                        memset(temp, 0, 256);
                        sprintf(temp, " %0.3f |", bbList[n].probability);
                        buf += std::string(temp);
                        sort = n + 1;
                    }
                }
            } else {
                memset(temp, 0, 256);
                sprintf(temp, "%s", "	    |");
                buf += std::string(temp);
            }
        }

        memset(temp, 0, 256);
        sprintf(temp, " %02d |\n", sort);
        buf += std::string(temp);
    }

    printf("%s", buf.c_str());
    return buf;
}

bool Algorithm::saveData2File(std::string dirname, std::string filename, std::string data)
{
    printf("saveData2File-->data len = %d\n", data.length());
    // write data to file
    FILE *fp;
    char buf[10240];
    memset(buf, 0, 10240);
    fp = fopen((dirname + std::string("/") + filename).c_str(), "a+");

    if(fp == NULL) {
        printf("open file %s fail!\n", filename.c_str());
        fclose(fp);
        return false;
    }

    sprintf(buf, "\n%s", data.c_str());

    if(fwrite(buf, strlen(buf), 1, fp) < 1) {
        printf("write file %s fail!\n", filename.c_str());
        fclose(fp);
        return false;
    }

    fclose(fp);
    return true;
}

bool Algorithm::writeLatestPredictResult2File(std::string data)
{
    char qid[64];
    memset(qid, 0, 64);
    // qid 2017154->2018001???
    sprintf(qid, "%d", mLatestResult->mQid + 1);
    std::string latestQid = std::string(qid);
#ifdef DLT
    std::string dirname = std::string("./dlt_results");
#else
    std::string dirname = std::string("./ssq_results");
#endif
    std::string filename = latestQid + std::string("-predict.txt");

    // check if dir exist
    if(access(dirname.c_str(), F_OK)) {
        printf("dir %s not exist, try to create it\n", dirname.c_str());

        if(mkdir(dirname.c_str(), 00755)) {
            printf("create dir %s fail!\n", dirname.c_str());
            return false;
        }
    }

    // if file exist, do nothing; not exsist, create it
    if(access((dirname + std::string("/") + filename).c_str(), F_OK)) {
        return saveData2File(dirname, filename, data);
    } else {
        printf("file %s exist\n", filename.c_str());
        return true;
    }
}

bool Algorithm::writeActualLatestResult2LastPredictFile()
{
    char qid[64];
    memset(qid, 0, 64);
    sprintf(qid, "%d", mLatestResult->mQid);
    std::string latestQid = std::string(qid);
    std::string latestDate = mLatestResult->mDate;
#ifdef DLT
    std::string dirname = std::string("./dlt_results");
#else
    std::string dirname = std::string("./ssq_results");
#endif
    std::string oldname = latestQid + std::string("-predict.txt");
    std::string newname = latestQid + std::string("_") + latestDate + std::string(".txt");

    // if file exist, do nothing; not exsist, create it
    if(access((dirname + std::string("/") + oldname).c_str(), F_OK)) {//file not exist
        printf("predict file %s not exist\n", oldname.c_str());
        return false;
    } else {//file exist
        sptr(RedBall) rb1 = mLatestResult->mR1;
        sptr(RedBall) rb2 = mLatestResult->mR2;
        sptr(RedBall) rb3 = mLatestResult->mR3;
        sptr(RedBall) rb4 = mLatestResult->mR4;
        sptr(RedBall) rb5 = mLatestResult->mR5;
#ifdef DLT
        sptr(BlueBall) bb1 = mLatestResult->mB1;
        sptr(BlueBall) bb2 = mLatestResult->mB2;
#else
        sptr(RedBall) rb6 = mLatestResult->mR6;
        sptr(BlueBall) bb = mLatestResult->mB0;
#endif
        std::string data = "";
        char temp[512];
        memset(temp, 0, 512);
#ifdef DLT
        sprintf(temp, "\nActual Result: %s %s %5d %5d %5d %5d %5d + %5d %5d\n", latestQid.c_str(), latestDate.c_str(),
                rb1->mNum, rb2->mNum, rb3->mNum, rb4->mNum, rb5->mNum, bb1->mNum, bb2->mNum);
#else
        sprintf(temp, "\nActual Result: %s %s %5d %5d %5d %5d %5d %5d + %5d\n", latestQid.c_str(), latestDate.c_str(),
                rb1->mNum, rb2->mNum, rb3->mNum, rb4->mNum, rb5->mNum, rb6->mNum, bb->mNum);
#endif
        data += std::string(temp);
        memset(temp, 0, 512);
#ifdef DLT
        sprintf(temp, "Actual Result: %s %s %5s %5s %5s %5s %5s + %5s %5s\n", latestQid.c_str(), latestDate.c_str(),
                Elememts2String(rb1->mWuxing).c_str(), Elememts2String(rb2->mWuxing).c_str(), Elememts2String(rb3->mWuxing).c_str(),
                Elememts2String(rb4->mWuxing).c_str(), Elememts2String(rb5->mWuxing).c_str(), Elememts2String(bb1->mWuxing).c_str(),
                Elememts2String(bb2->mWuxing).c_str());
#else
        sprintf(temp, "Actual Result: %s %s %5s %5s %5s %5s %5s %5s + %5s\n", latestQid.c_str(), latestDate.c_str(),
                Elememts2String(rb1->mWuxing).c_str(), Elememts2String(rb2->mWuxing).c_str(), Elememts2String(rb3->mWuxing).c_str(),
                Elememts2String(rb4->mWuxing).c_str(), Elememts2String(rb5->mWuxing).c_str(), Elememts2String(rb6->mWuxing).c_str(),
                Elememts2String(bb->mWuxing).c_str());
#endif
        data += std::string(temp);
        printf("write data:%s\n", data.c_str());

        if(saveData2File(dirname, oldname, data)) {
            printf("write data sucess, rename file %s to %s\n", oldname.c_str(), newname.c_str());

            if(rename(oldname.c_str(), newname.c_str()))
            { printf("rename fail, please modify file name manually\n"); }

            return true;
        } else {
            printf("predict file %s exsist, but write data fail\n", oldname.c_str());
            return false;
        }
    }
}

