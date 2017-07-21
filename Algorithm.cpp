#include <stdio.h>
#include <stdlib.h>
#include <vector>

//#include "Property.h"
#include "Algorithm.h"
#include "MySqlOperator.h"
#include "Result.h"
#include "RedBall.h"
#include "BlueBall.h"
#include "StringUtil.h"


Algorithm::Algorithm()
{
}

bool Algorithm::updateDatabase()
{
    return true;
}

Result* Algorithm::getLatestResultFromDatabase()
{
    std::string str;
    std::vector<std::string> lines;
    Result *result = NULL;
    char *rg = "\n";
    char *cg = ",";
    updateDatabase();
    MySqlOperator *sql = new MySqlOperator();

    if(sql != NULL) {
        if(sql->ConnMySQL(HOST, PORT, DATABASE, USER, PASSWORD, CHARSET) == 0) {
            str = sql->SelectData(TABLE_SSQ, NULL, 1);

            if(!StringUtil::StringIsEmpty(str)) {
                StringUtil::StringSplit(lines, str, cg);
                RedNumbers r1 = (RedNumbers) atoi(lines[3].c_str());
                RedNumbers r2 = (RedNumbers) atoi(lines[4].c_str());
                RedNumbers r3 = (RedNumbers) atoi(lines[5].c_str());
                RedNumbers r4 = (RedNumbers) atoi(lines[6].c_str());
                RedNumbers r5 = (RedNumbers) atoi(lines[7].c_str());
                RedNumbers r6 = (RedNumbers) atoi(lines[8].c_str());
                BlueNumbers b0 = (BlueNumbers) atoi(lines[9].c_str());
                result = new Result(new RedBall(r1), new RedBall(r2), new RedBall(r3), new RedBall(r4), new RedBall(r5), new RedBall(r6), new BlueBall(b0));
            }
        }

        sql->CloseMySQLConn();
    }

    return result;
}

void Algorithm::rearrangePredictResult(std::vector<resultStatistics> resultSta, int top)
{
    int size = (int) resultSta.size();

    for(int i = 0; i < size - 1; i++) {
        for(int j = 0; j < size - i - 1; j++) {
            if(resultSta[j].probability < resultSta[j + 1].probability) {
                std::swap(resultSta[j], resultSta[j + 1]);
            }
        }
    }

    resultSta.erase(resultSta.begin() + top, resultSta.end());
}

void Algorithm::printPredictResult(std::vector<resultStatistics> resultSta)
{
    for(int i = 0; i < (int)resultSta.size(); i++) {
        Result *result = resultSta[i].result;
        RedNumbers rnum1 = result->mR1->mNum;
        RedNumbers rnum2 = result->mR2->mNum;
        RedNumbers rnum3 = result->mR3->mNum;
        RedNumbers rnum4 = result->mR4->mNum;
        RedNumbers rnum5 = result->mR5->mNum;
        RedNumbers rnum6 = result->mR6->mNum;
        BlueNumbers bnum = result->mB0->mNum;
        printf("[%d] %2d %2d %2d %2d %2d %2d + %2d  probability = %0.3f", i + 1, rnum1, rnum2, rnum3, rnum4, rnum5, rnum6, bnum, resultSta[i].probability);
    }
}

std::vector<resultStatistics> Algorithm::getMaxProbabilityPredictResult(int top)
{
    std::vector<resultStatistics> resultSta;
    std::vector<redballStatistics> rsta1 = calculateRedBallProbability(REDBALL_FIRST);
    std::vector<redballStatistics> rsta2 = calculateRedBallProbability(REDBALL_SECOND);
    std::vector<redballStatistics> rsta3 = calculateRedBallProbability(REDBALL_THIRD);
    std::vector<redballStatistics> rsta4 = calculateRedBallProbability(REDBALL_FOURTH);
    std::vector<redballStatistics> rsta5 = calculateRedBallProbability(REDBALL_FIFTH);
    std::vector<redballStatistics> rsta6 = calculateRedBallProbability(REDBALL_SIXTH);
    std::vector<blueballStatistics> bsta = calculateBlueBallProbability(BLUEBALL_FIRST);

    for(int i = 0; i < (int)rsta1.size(); i++) {
        for(int j = 0; j < (int)rsta2.size(); j++) {
            for(int k = 0; k < (int)rsta3.size(); k++) {
                for(int m = 0; m < (int)rsta4.size(); m++) {
                    for(int n = 0; n < (int)rsta5.size(); n++) {
                        for(int r = 0; r < (int)rsta6.size(); r++) {
                            for(int s = 0; s < (int)bsta.size(); s++) {
                                Result *result = new Result(rsta1[i].redball, rsta2[j].redball, rsta3[k].redball, rsta4[m].redball, rsta5[n].redball, rsta6[r].redball, bsta[s].blueball);
                                float prob = rsta1[i].probability * rsta2[j].probability * rsta3[k].probability * rsta4[m].probability * rsta5[n].probability * rsta6[r].probability * bsta[s].probability;
                                resultStatistics sta;
                                sta.result = result;
                                sta.probability = prob;
                                resultSta.push_back(sta);
                            }
                        }
                    }
                }
            }
        }
    }

    rearrangePredictResult(resultSta, top);
    //printPredictResult(resultSta);
    return resultSta;
}

std::vector<redballStatistics> Algorithm::calculateRedBallProbability(int ballType)
{
    static float NUM_WEIGHT = 0.5;
    static float WUXING_WEIGHT = 0.5;
    std::vector<rnumStatistics> rnumList;
    std::vector<wuxingStatistics> wuxingList;
    std::vector<redballStatistics> rBallList;
    float PROBABILITY_METAL = 0;
    float PROBABILITY_WOOD = 0;
    float PROBABILITY_WATER = 0;
    float PROBABILITY_FIRE = 0;
    float PROBABILITY_EARTH = 0;
    float prob = 0;
    int total1 = calculateRedBallNumberProbability(ballType, rnumList);
    int total2 = calculateBallWuxingProbability(ballType, wuxingList);

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
                prob = (float) rnumList[j].count / total1 * PROBABILITY_METAL;
                break;

            case WOOD:
                prob = (float) rnumList[j].count / total1 * PROBABILITY_WOOD;
                break;

            case WATER:
                prob = (float) rnumList[j].count / total1 * PROBABILITY_WATER;
                break;

            case FIRE:
                prob = (float) rnumList[j].count / total1 * PROBABILITY_FIRE;
                break;

            case EARTH:
                prob = (float) rnumList[j].count / total1 * PROBABILITY_EARTH;
                break;

            default:
                break;
        }

        redballStatistics rsta;
        rsta.redball = redball;
        rsta.probability = prob;
        rBallList.push_back(rsta);
    }

    return rBallList;
}

std::vector<blueballStatistics> Algorithm::calculateBlueBallProbability(int ballType)
{
    static float NUM_WEIGHT = 0.5;
    static float WUXING_WEIGHT = 0.5;
    std::vector<bnumStatistics> bnumList;
    std::vector<wuxingStatistics> wuxingList;
    std::vector<blueballStatistics> bBallList;
    float PROBABILITY_METAL = 0;
    float PROBABILITY_WOOD = 0;
    float PROBABILITY_WATER = 0;
    float PROBABILITY_FIRE = 0;
    float PROBABILITY_EARTH = 0;
    float prob = 0;
    int total1 = calculateBlueBallNumberProbability(ballType, bnumList);
    int total2 = calculateBallWuxingProbability(ballType, wuxingList);

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
                prob = (float) bnumList[j].count / total1 * PROBABILITY_METAL;
                break;

            case WOOD:
                prob = (float) bnumList[j].count / total1 * PROBABILITY_WOOD;
                break;

            case WATER:
                prob = (float) bnumList[j].count / total1 * PROBABILITY_WATER;
                break;

            case FIRE:
                prob = (float) bnumList[j].count / total1 * PROBABILITY_FIRE;
                break;

            case EARTH:
                prob = (float) bnumList[j].count / total1 * PROBABILITY_EARTH;
                break;

            default:
                break;
        }

        blueballStatistics bsta;
        bsta.blueball = blueball;
        bsta.probability = prob;
        bBallList.push_back(bsta);
    }

    return bBallList;
}

void Algorithm::comparePredictResultWithActualResult()
{
}

std::string Algorithm::getLogTitleFromBalltype(int ballType)
{
    switch(ballType) {
        case REDBALL_FIRST:
            return "1st RedBall";

        case REDBALL_SECOND:
            return "2nd RedBall";

        case REDBALL_THIRD:
            return "3rd RedBall";

        case REDBALL_FOURTH:
            return "4th RedBall";

        case REDBALL_FIFTH:
            return "5th RedBall";

        case REDBALL_SIXTH:
            return "6th RedBall";

        case BLUEBALL_FIRST:
            return "BlueBall";

        case BLUEBALL_SECOND:
            return "2nd BlueBall";

        default:
            break;
    }

    return "";
}

void Algorithm::printRedballNumberProbability(std::vector<rnumStatistics> sta, int total, int ballType)
{
    std::string title = getLogTitleFromBalltype(ballType);

    for(int i = 0; i < (int)sta.size(); i++) {
        printf("%s [%d] : num = %d, count = %d, probability = %0.3f\n", title.c_str(), i + 1, sta[i].rn, sta[i].count, (float)sta[i].count / total);
    }
}

void Algorithm::printBlueballNumberProbability(std::vector<bnumStatistics> sta, int total, int ballType)
{
    std::string title = getLogTitleFromBalltype(ballType);

    for(int i = 0; i < (int)sta.size(); i++) {
        printf("%s [%d] : num = %d, count = %d, probability = %0.3f\n", title.c_str(), i + 1, sta[i].bn, sta[i].count, (float)sta[i].count / total);
    }
}

void Algorithm::printBallWuxingProbability(std::vector<wuxingStatistics> sta, int total, int ballType)
{
    std::string title = getLogTitleFromBalltype(ballType);

    for(int i = 0; i < (int)sta.size(); i++) {
        printf("%s [%d] : wuxing = %d, count = %d, probability = %0.3f\n", title.c_str(), i + 1, sta[i].wuxing, sta[i].count, (float)sta[i].count / total);
    }
}

int Algorithm::calculateRedBallNumberProbability(int ballType, std::vector<rnumStatistics> staList)
{
    Result *result = getLatestResultFromDatabase();
    RedBall *rb = result->mR1;
    RedNumbers num = rb->mNum;
    std::vector<RedBall*> mList = getRedBallListFromDatabase("", 0);
    int totalCount = 0;

    for(int i = 0; i < (int)mList.size(); i++) {
        if(num == mList[i]->mNum) {
            for(int j = 0; j < (int) staList.size(); j++) {
                if(mList[i + 1]->mNum == staList[j].rn) {
                    staList[j].count ++;
                } else {
                    rnumStatistics sta;
                    sta.rn = mList[i + 1]->mNum;
                    sta.count = 0;
                    staList.push_back(sta);
                }
            }

            totalCount++;
        }
    }

    printRedballNumberProbability(staList, totalCount, ballType);
    return totalCount;
}

int Algorithm::calculateBlueBallNumberProbability(int ballType, std::vector<bnumStatistics> staList)
{
    Result *result = getLatestResultFromDatabase();
    BlueBall *bb = result->mB0;
    BlueNumbers num = bb->mNum;
    std::vector<BlueBall*> mList = getBlueBallListFromDatabase("", 0);
    int totalCount = 0;

    for(int i = 0; i < (int)mList.size(); i++) {
        if(num == mList[i]->mNum) {
            for(int j = 0; j < (int) staList.size(); j++) {
                if(mList[i + 1]->mNum == staList[j].bn) {
                    staList[j].count ++;
                } else {
                    bnumStatistics sta;
                    sta.bn = mList[i + 1]->mNum;
                    sta.count = 0;
                    staList.push_back(sta);
                }
            }

            totalCount++;
        }
    }

    printBlueballNumberProbability(staList, totalCount, ballType);
    return totalCount;
}

int Algorithm::calculateBallWuxingProbability(int ballType, std::vector<wuxingStatistics> wuxingList)
{
    int totalCount = 0;
    Result *result = getLatestResultFromDatabase();
    RedBall *rb = result->mR1;
    Elememts wuxing = rb->mWuxing;

    if(ballType > 0 && ballType < BLUEBALL_FIRST) {
        std::vector<RedBall*> mList = getRedBallListFromDatabase("", 0);

        for(int i = 0; i < (int)mList.size(); i++) {
            if(wuxing == mList[i]->mWuxing) {
                for(int j = 0; j < (int) wuxingList.size(); j++) {
                    if(mList[i + 1]->mWuxing == wuxingList[j].wuxing) {
                        wuxingList[j].count ++;
                    } else {
                        wuxingStatistics sta;
                        sta.wuxing = mList[i + 1]->mWuxing;
                        sta.count = 0;
                        wuxingList.push_back(sta);
                    }
                }

                totalCount++;
            }
        }
    } else {
        std::vector<BlueBall*> mList = getBlueBallListFromDatabase("", 0);

        for(int i = 0; i < (int)mList.size(); i++) {
            if(wuxing == mList[i]->mWuxing) {
                for(int j = 0; j < (int) wuxingList.size(); j++) {
                    if(mList[i + 1]->mWuxing == wuxingList[j].wuxing) {
                        wuxingList[j].count ++;
                    } else {
                        wuxingStatistics sta;
                        sta.wuxing = mList[i + 1]->mWuxing;
                        sta.count = 0;
                        wuxingList.push_back(sta);
                    }
                }

                totalCount++;
            }
        }
    }

    printBallWuxingProbability(wuxingList, totalCount, ballType);
    return totalCount;
}

std::vector<RedBall*> Algorithm::getRedBallListFromDatabase(char *field, int rnum)
{
    std::vector<RedBall*> redList;
    std::vector<std::string> lines;
    std::string str;
    char *rg = "\n"; // row
    char *cg = ","; // field
    updateDatabase();
    MySqlOperator *sql = new MySqlOperator();

    if(sql != NULL) {
        if(sql->ConnMySQL(HOST, PORT, DATABASE, USER, PASSWORD, CHARSET) == 0) {
            str = sql->SelectData(TABLE_SSQ, field, 500);

            if(!StringUtil::StringIsEmpty(str)) {
                StringUtil::StringSplit(lines, str, rg);

                for(int i = 0; i < (int)lines.size(); i++) {
                    RedNumbers rn = (RedNumbers) atoi(lines[i].c_str());
                    RedBall *rb = new RedBall(rn);
                    redList.push_back(rb);
                }
            }
        }

        sql->CloseMySQLConn();
    }

    return redList;
}

std::vector<BlueBall*> Algorithm::getBlueBallListFromDatabase(char *field, int rnum)
{
    std::vector<BlueBall*> blueList;
    std::vector<std::string> lines;
    std::string str;
    char *rg = "\n"; // row
    char *cg = ","; // field
    updateDatabase();
    MySqlOperator *sql = new MySqlOperator();

    if(sql != NULL) {
        if(sql->ConnMySQL(HOST, PORT, DATABASE, USER, PASSWORD, CHARSET) == 0) {
            str = sql->SelectData(TABLE_SSQ, field, 500);

            if(!StringUtil::StringIsEmpty(str)) {
                StringUtil::StringSplit(lines, str, rg);

                for(int i = 0; i < (int)lines.size(); i++) {
                    BlueNumbers bn = (BlueNumbers) atoi(lines[i].c_str());
                    BlueBall *bb = new BlueBall(bn);
                    blueList.push_back(bb);
                }
            }
        }

        sql->CloseMySQLConn();
    }

    return blueList;
}