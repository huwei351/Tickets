#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>

//#include "Property.h"
#include "Algorithm.h"
#include "MySqlOperator.h"
#include "Result.h"
#include "RedBall.h"
#include "BlueBall.h"
#include "StringUtil.h"
#include "Callpy.h"


Algorithm::Algorithm()
{
    mMySqlOperator = new MySqlOperator();
}

Algorithm::~Algorithm()
{
    delete mMySqlOperator;
}

bool Algorithm::updateDatabase()
{
	mLatestResult = getLatestResultFromDatabase();
	int qid = mLatestResult->getQid();
	char cqid[128];
	sprintf(cqid, "%d", qid);
	Callpy *py = new Callpy();
	int res = py->runPythonFunction(std::string("update_database"), std::string("1")+std::string("\n")+std::string(cqid)+std::string("\n"));
	delete py;
                if (res == 0) {
                    mLatestResult = getLatestResultFromDatabase();
                    return true;
                } else {
                    return false;
                }
}

Result* Algorithm::getLatestResultFromDatabase()
{
    std::string str;
    std::vector<std::string> lines;
    Result *result;

    if(mMySqlOperator!= NULL) {
        if(mMySqlOperator->ConnMySQL(HOST, PORT, DATABASE, USER, PASSWORD, CHARSET) == 0) {
            str = mMySqlOperator->SelectData(TABLE_SSQ, NULL, 1);

            if(!StringUtil::StringIsEmpty(str)) {
                StringUtil::StringSplit(lines, str, COLUMN_G);
				int qid = atoi(lines[1].c_str());
				std::string date = lines[2];
                RedNumbers r1 = (RedNumbers) atoi(lines[3].c_str());
                RedNumbers r2 = (RedNumbers) atoi(lines[4].c_str());
                RedNumbers r3 = (RedNumbers) atoi(lines[5].c_str());
                RedNumbers r4 = (RedNumbers) atoi(lines[6].c_str());
                RedNumbers r5 = (RedNumbers) atoi(lines[7].c_str());
                RedNumbers r6 = (RedNumbers) atoi(lines[8].c_str());
                BlueNumbers b0 = (BlueNumbers) atoi(lines[9].c_str());
				printf("qid=%d, date=%s, r1=%d, r2=%d, r3=%d, r4=%d, r5=%d, r6=%d, b0=%d\n", qid, date.c_str(), r1, r2, r3, r4, r5, r6, b0);
                result = new Result(new RedBall(r1, REDBALL_FIRST), new RedBall(r2, REDBALL_SECOND), new RedBall(r3, REDBALL_THIRD),
						new RedBall(r4, REDBALL_FOURTH), new RedBall(r5, REDBALL_FIFTH), new RedBall(r6, REDBALL_SIXTH),
						new BlueBall(b0, BLUEBALL_FIRST));
				result->setDate(date);
				result->setQid(qid);
            }
        }

        mMySqlOperator->CloseMySQLConn();
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
    std::vector<redballStatistics> rsta1 = calculateRedBallProbability(mLatestResult->mR1);
    std::vector<redballStatistics> rsta2 = calculateRedBallProbability(mLatestResult->mR2);
    std::vector<redballStatistics> rsta3 = calculateRedBallProbability(mLatestResult->mR3);
    std::vector<redballStatistics> rsta4 = calculateRedBallProbability(mLatestResult->mR4);
    std::vector<redballStatistics> rsta5 = calculateRedBallProbability(mLatestResult->mR5);
    std::vector<redballStatistics> rsta6 = calculateRedBallProbability(mLatestResult->mR6);
    std::vector<blueballStatistics> bsta = calculateBlueBallProbability(mLatestResult->mB0);

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
    printPredictResult(resultSta);
    return resultSta;
}

std::vector<redballStatistics> Algorithm::calculateRedBallProbability(RedBall *rb)
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

std::vector<blueballStatistics> Algorithm::calculateBlueBallProbability(BlueBall *bb)
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
/*
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

char* Algorithm::Balltype2FieldName(int ballType)
{
    switch(ballType) {
        case REDBALL_FIRST:
            return FIELD_RB_FIRST;

        case REDBALL_SECOND:
            return FIELD_RB_SECOND;

        case REDBALL_THIRD:
            return FIELD_RB_THIRD;

        case REDBALL_FOURTH:
            return FIELD_RB_FOURTH;

        case REDBALL_FIFTH:
            return FIELD_RB_FIFTH;

        case REDBALL_SIXTH:
            return FIELD_RB_SIXTH;

        case BLUEBALL_FIRST:
            return FIELD_BB;

        case BLUEBALL_SECOND:
            return "2nd BlueBall";

        default:
            break;
    }

    return "";
}
*/
void Algorithm::printRedballNumberProbability(std::vector<rnumStatistics> *sta, int total, BallType ballType)
{
    std::string title = getLogTitleFromBalltype(ballType);

    for(int i = 0; i < (int)sta->size(); i++) {
        printf("%s [%d] : num = %d, count = %d, probability = %0.3f\n", title.c_str(), i + 1, sta->at(i).rn, sta->at(i).count, (float)sta->at(i).count / total);
    }
}

void Algorithm::printBlueballNumberProbability(std::vector<bnumStatistics> *sta, int total, BallType ballType)
{
    std::string title = getLogTitleFromBalltype(ballType);

    for(int i = 0; i < (int)sta->size(); i++) {
        printf("%s [%d] : num = %d, count = %d, probability = %0.3f\n", title.c_str(), i + 1, sta->at(i).bn, sta->at(i).count, (float)sta->at(i).count / total);
    }
}

void Algorithm::printBallWuxingProbability(std::vector<wuxingStatistics> *sta, int total, BallType ballType)
{
    std::string title = getLogTitleFromBalltype(ballType);

    for(int i = 0; i < (int)sta->size(); i++) {
        printf("%s [%d] : wuxing = %s, count = %d, probability = %0.3f\n", title.c_str(), i + 1, Elememts2String(sta->at(i).wuxing).c_str(), sta->at(i).count, (float)sta->at(i).count / total);
    }
}

int Algorithm::calculateRedBallNumberAndWuxingProbability(RedBall *rb, int &total_rnum, int &total_wuxing,
	std::vector<rnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList)
{
    RedNumbers num = rb->mNum;
	Elememts wuxing = rb->mWuxing;
	BallType ballType = rb->mBalltype;
    std::vector<RedBall*> mList = getRedBallListFromDatabase(Balltype2FieldName(ballType), 500);

    for(int i = (int)mList.size()-1; i > 0; i--) {
        if(num == mList[i]->mNum) {
			if ((int)staList->size() == 0) {
	            rnumStatistics sta;
	            sta.rn = mList[i-1]->mNum;
	            sta.count = 1;
	            staList->push_back(sta);
			} else {
				bool exist = false;
		        for(int j = 0; j < (int)staList->size(); j++) {
		            if(mList[i-1]->mNum == staList->at(j).rn) {
		                staList->at(j).count ++;
						exist= true;
						break;
		            }
		        }
				if (!exist) {
		            rnumStatistics sta;
		            sta.rn = mList[i-1]->mNum;
		            sta.count = 1;
		            staList->push_back(sta);
				}
			}

            total_rnum++;
        }

        if(wuxing == mList[i]->mWuxing) {
			if ((int)wuxingList->size() == 0) {
                wuxingStatistics sta;
                sta.wuxing = mList[i-1]->mWuxing;
                sta.count = 1;
                wuxingList->push_back(sta);
			} else {
				bool found = false;
	            for(int j = 0; j < (int) wuxingList->size(); j++) {
	                if(mList[i-1]->mWuxing == wuxingList->at(j).wuxing) {
	                    wuxingList->at(j).count ++;
						found = true;
						break;
	                }
	            }
				if (!found) {
	                wuxingStatistics sta;
	                sta.wuxing = mList[i-1]->mWuxing;
	                sta.count = 1;
	                wuxingList->push_back(sta);
				}
			}

            total_wuxing++;
        }
    }

    printRedballNumberProbability(staList, total_rnum, ballType);
	printBallWuxingProbability(wuxingList, total_wuxing, ballType);
}

int Algorithm::calculateBlueBallNumberAndWuxingProbability(BlueBall *bb, int &total_bnum, int &total_wuxing,
	std::vector<bnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList)
{
    BlueNumbers num = bb->mNum;
	Elememts wuxing = bb->mWuxing;
	BallType ballType = bb->mBalltype;
    std::vector<BlueBall*> mList = getBlueBallListFromDatabase(Balltype2FieldName(ballType), 500);

    for(int i = (int)mList.size(); i > 0; i--) {
        if(num == mList[i]->mNum) {
			if ((int)staList->size() == 0) {
				bnumStatistics sta;
				sta.bn = mList[i-1]->mNum;
				sta.count = 1;
				staList->push_back(sta);
			} else {
				bool exist = false;
	            for(int j = 0; j < (int)staList->size(); j++) {
	                if(mList[i-1]->mNum == staList->at(j).bn) {
	                    staList->at(j).count ++;
						exist = true;
						break;
	                }
	            }
				if (!exist) {
					bnumStatistics sta;
					sta.bn = mList[i-1]->mNum;
					sta.count = 1;
					staList->push_back(sta);
				}
			}

            total_bnum++;
        }

        if(wuxing == mList[i]->mWuxing) {
			if ((int)wuxingList->size() == 0) {
				wuxingStatistics sta;
				sta.wuxing = mList[i-1]->mWuxing;
				sta.count = 1;
				wuxingList->push_back(sta);
			} else {
				bool found = false;
	            for(int j = 0; j < (int)wuxingList->size(); j++) {
	                if(mList[i-1]->mWuxing == wuxingList->at(j).wuxing) {
	                    wuxingList->at(j).count ++;
						found = true;
						break;
	                }
	            }
				if (!found) {
					wuxingStatistics sta;
					sta.wuxing = mList[i-1]->mWuxing;
					sta.count = 1;
					wuxingList->push_back(sta);
				}
			}

            total_wuxing++;
        }
    }

    printBlueballNumberProbability(staList, total_bnum, ballType);
	printBallWuxingProbability(wuxingList, total_wuxing, ballType);
}
/*
int Algorithm::calculateRedBallNumberProbability(int ballType, std::vector<rnumStatistics> *staList)
{
    Result *result = getLatestResultFromDatabase();
    RedBall *rb = result->mR1;
    RedNumbers num = rb->mNum;
    std::vector<RedBall*> mList = getRedBallListFromDatabase(Balltype2FieldName(ballType), 500);
    int totalCount = 0;

    for(int i = 0; i < (int)mList.size(); i++) {
        if(num == mList[i]->mNum) {
            for(int j = 0; j < (int) staList->size(); j++) {
                if(mList[i + 1]->mNum == staList->at(j).rn) {
                    staList->at(j).count ++;
                } else {
                    rnumStatistics sta;
                    sta.rn = mList[i + 1]->mNum;
                    sta.count = 0;
                    staList->push_back(sta);
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
    std::vector<BlueBall*> mList = getBlueBallListFromDatabase(Balltype2FieldName(ballType), 500);
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
        std::vector<RedBall*> mList = getRedBallListFromDatabase(Balltype2FieldName(ballType), 500);

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
        std::vector<BlueBall*> mList = getBlueBallListFromDatabase(Balltype2FieldName(ballType), 500);

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
*/
std::vector<RedBall*> Algorithm::getRedBallListFromDatabase(char *field, int rnum)
{
    std::vector<RedBall*> redList;
    std::vector<std::string> lines;
    std::string str;

    if(mMySqlOperator!= NULL) {
        if(mMySqlOperator->ConnMySQL(HOST, PORT, DATABASE, USER, PASSWORD, CHARSET) == 0) {
            str = mMySqlOperator->SelectData(TABLE_SSQ, field, rnum);

            if(!StringUtil::StringIsEmpty(str)) {
                StringUtil::StringSplit(lines, str, CR_G);

                for(int i = 0; i < (int)lines.size(); i++) {
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

std::vector<BlueBall*> Algorithm::getBlueBallListFromDatabase(char *field, int rnum)
{
    std::vector<BlueBall*> blueList;
    std::vector<std::string> lines;
    std::string str;

    if(mMySqlOperator!= NULL) {
        if(mMySqlOperator->ConnMySQL(HOST, PORT, DATABASE, USER, PASSWORD, CHARSET) == 0) {
            str = mMySqlOperator->SelectData(TABLE_SSQ, field, rnum);

            if(!StringUtil::StringIsEmpty(str)) {
                StringUtil::StringSplit(lines, str, CR_G);

                for(int i = 0; i < (int)lines.size(); i++) {
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
