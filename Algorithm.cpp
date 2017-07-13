#include <stdio.h>
#include <stdlib.h>

#include "Property.h"
#include "MySqlOperator.h"
#include "Result.h"
#include "RedBall.h"
#include "BlueBall.h"

typedef enum {
	REDBALL_FIRST = 1,
	REDBALL_SECOND,
	REDBALL_THIRD,
	REDBALL_FOURTH,
	REDBALL_FIFTH,
	REDBALL_SIXTH,
	BLUEBALL_FIRST,
	BLUEBALL_SECOND = 8
};

typedef struct rnumStatistics
{
	RedNumbers rn;
	int count;
};

typedef struct bnumStatistics
{
	BlueNumbers bn;
	int count;
};

typedef struct wuxingStatistics
{
	Elememts wuxing;
	int count;
};

typedef struct redballStatistics
{
	RedBall redball;
	float probability;
};

typedef struct blueballStatistics
{
	BlueBall blueball;
	float probability;
};

typedef struct resultStatistics
{
	Result result;
	float probability;
};

Algorithm::Algorithm()
{
}

bool Algorithm::updateDatabase()
{
	return true;
}

Result Algorithm::getLatestResultFromDatabase()
{
}

void Algorithm::rearrangePredictResult(std::vector<resultStatistics> resultSta, int top)
{
	int size = (int) resultSta.size();

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i -1; j++) {
			if (resultSta[j].probability < resultSta[j+1].probability) {
				swap(resultSta[j], resultSta[j+1]);
			}
		}
	}

	resultSta.erase(resultSta.begin() + top, resultSta.end());
}

void Algorithm::printPredictResult(std::vector<resultStatistics> resultSta)
{
	for (int i = 0; i < (int)resultSta.size(); i++) {
		Result result = resultSta[i].result;
		RedNumbers rnum1 = result.mR1.mNum;
		RedNumbers rnum2 = result.mR2.mNum;
		RedNumbers rnum3 = result.mR3.mNum;
		RedNumbers rnum4 = result.mR4.mNum;
		RedNumbers rnum5 = result.mR5.mNum;
		RedNumbers rnum6 = result.mR6.mNum;
		BlueNumbers bnum = result.mB0.mNum;
		printf("[%d] %2d %2d %2d %2d %2d %2d + %2d  probability = %0.3f", i+1, rnum1, rnum2, rnum3, rnum4, rnum5, rnum6, bnum, resultSta[i].probability);
	}
}

Result Algorithm::getMaxProbabilityPredictResult(int top)
{
	std::vector<resultStatistics> resultSta;
	std::vector<redballStatistics> rsta1 = calculateRedBallProbability(REDBALL_FIRST);
	std::vector<redballStatistics> rsta2 = calculateRedBallProbability(REDBALL_SECOND);
	std::vector<redballStatistics> rsta3 = calculateRedBallProbability(REDBALL_THIRD);
	std::vector<redballStatistics> rsta4 = calculateRedBallProbability(REDBALL_FOURTH);
	std::vector<redballStatistics> rsta5 = calculateRedBallProbability(REDBALL_FIFTH);
	std::vector<redballStatistics> rsta6 = calculateRedBallProbability(REDBALL_SIXTH);
	std::vector<blueballStatistics> bsta = calculateBlueBallProbability(BLUEBALL_FIRST);

	for (int i = 0; i < (int)rsta1.size(); i++) {
		for (int j = 0; j < (int)rsta2.size(); j++) {
			for (int k = 0; k < (int)rsta3.size(); k++) {
				for (int m = 0; m < (int)rsta4.size(); m++) {
					for (int n = 0; n < (int)rsta5.size(); n++) {
						for (int r = 0; r < (int)rsta6.size(); r++) {
							for(int s = 0; s < (int)bsta.size(); s++) {
								Result result = new Result(rsta1[i].redball, rsta2[j].redball, rsta3[k].redball, rsta4[m].redball, rsta5[n].redball, rsta6[r].redball, bsta[s].blueball);
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

	int total1 = calculateBallNumberProbability(ballType, rnumList);
	int total2 = calculateBallWuxingProbability(ballType, wuxingList);

	for (int i = 0; i < (int)wuxingList.size(); i++) {
		switch (wuxingList[i].wuxing) {
			case Elememts.METAL:
				PROBABILITY_METAL = (float)wuxingList[i].count/total2;
				break;
			case Elememts.WOOD:
				PROBABILITY_WOOD = (float)wuxingList[i].count/total2;
				break;
			case Elememts.WATER:
				PROBABILITY_WATER = (float)wuxingList[i].count/total2;
				break;
			case Elememts.FIRE:
				PROBABILITY_FIRE = (float)wuxingList[i].count/total2;
				break;
			case Elememts.EARTH:
				PROBABILITY_EARTH = (float)wuxingList[i].count/total2;
				break;
			default:
				break;
		}
	}

	for (int j = 0; j < (int)rnumList.size(); j++) {
		RedBall redball = new RedBall(rnumList[i].rn);
		switch (redball.mWuxing) {
			case Elememts.METAL:
				prob = (float) rnumList[i].count/total1 * PROBABILITY_METAL; 
				break;
			case Elememts.WOOD:
				prob = (float) rnumList[i].count/total1 * PROBABILITY_WOOD; 
				break;
			case Elememts.WATER:
				prob = (float) rnumList[i].count/total1 * PROBABILITY_WATER; 
				break;
			case Elememts.FIRE:
				prob = (float) rnumList[i].count/total1 * PROBABILITY_FIRE; 
				break;
			case Elememts.EARTH:
				prob = (float) rnumList[i].count/total1 * PROBABILITY_EARTH; 
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

	int total1 = calculateBallNumberProbability(ballType, bnumList);
	int total2 = calculateBallWuxingProbability(ballType, wuxingList);

	for (int i = 0; i < (int)wuxingList.size(); i++) {
		switch (wuxingList[i].wuxing) {
			case Elememts.METAL:
				PROBABILITY_METAL = (float)wuxingList[i].count/total2;
				break;
			case Elememts.WOOD:
				PROBABILITY_WOOD = (float)wuxingList[i].count/total2;
				break;
			case Elememts.WATER:
				PROBABILITY_WATER = (float)wuxingList[i].count/total2;
				break;
			case Elememts.FIRE:
				PROBABILITY_FIRE = (float)wuxingList[i].count/total2;
				break;
			case Elememts.EARTH:
				PROBABILITY_EARTH = (float)wuxingList[i].count/total2;
				break;
			default:
				break;
		}
	}

	for (int j = 0; j < (int)bnumList.size(); j++) {
		BlueBall blueball = new BlueBall(bnumList[i].bn);
		switch (blueball.mWuxing) {
			case Elememts.METAL:
				prob = (float) bnumList[i].count/total1 * PROBABILITY_METAL; 
				break;
			case Elememts.WOOD:
				prob = (float) bnumList[i].count/total1 * PROBABILITY_WOOD; 
				break;
			case Elememts.WATER:
				prob = (float) bnumList[i].count/total1 * PROBABILITY_WATER; 
				break;
			case Elememts.FIRE:
				prob = (float) bnumList[i].count/total1 * PROBABILITY_FIRE; 
				break;
			case Elememts.EARTH:
				prob = (float) bnumList[i].count/total1 * PROBABILITY_EARTH; 
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
	switch (ballType) {
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
	for (int i = 0; i < (int)sta.size(); i++) {
		printf("%s [%d] : num = %d, count = %d, probability = %0.3f\n", title, i+1, sta[i].rn, sta[i].count, (float)sta[i].count/total);
	}
}

void Algorithm::printBlueballNumberProbability(std::vector<bnumStatistics> sta, int total, int ballType)
{
	std::string title = getLogTitleFromBalltype(ballType);
	for (int i = 0; i < (int)sta.size(); i++) {
		printf("%s [%d] : num = %d, count = %d, probability = %0.3f\n", title, i+1, sta[i].rn, sta[i].count, (float)sta[i].count/total);
	}
}

void Algorithm::printBallWuxingProbability(std::vector<wuxingStatistics> sta, int total, int ballType)
{
	std::string title = getLogTitleFromBalltype(ballType);
	for (int i = 0; i < (int)sta.size(); i++) {
		printf("%s [%d] : wuxing = %d, count = %d, probability = %0.3f\n", title, i+1, sta[i].wuxing, sta[i].count, (float)sta[i].count/total);
	}
}

int Algorithm::calculateRedBallNumberProbability(int ballType, std::vector<rnumStatistics> staList)
{
	Result result = getLatestResultFromDatabase();
	RedBall rb = result.mR1;
	RedNumbers num = rb.mNum;
	std::vector<RedBall> mList = getBallListFromDatabase("", 0, 0);
	int totalCount = 0;

	for (int i = 0; i < (int)mList.size(); i++) {
		if (num == mList[i].mNum) {
			for (int j = 0; j < (int) staList.size(); j++) {
				if (mList[i+1].mNum == staList[j].rn) {
					staList[j].count ++;
				} else {
					rnumStatistics sta;
					sta.rn = mList[i+1].mNum;
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
	Result result = getLatestResultFromDatabase();
	BlueBall bb = result.mB0;
	BlueNumbers num = bb.mNum;
	std::vector<BlueBall> mList = getBallListFromDatabase("", 0, 0);
	int totalCount = 0;

	for (int i = 0; i < (int)mList.size(); i++) {
		if (num == mList[i].mNum) {
			for (int j = 0; j < (int) staList.size(); j++) {
				if (mList[i+1].mNum == staList[j].rn) {
					staList[j].count ++;
				} else {
					bnumStatistics sta;
					sta.bn = mList[i+1].mNum;
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
	Result result = getLatestResultFromDatabase();
	RedBall rb = result.mR1;
	Elememts wuxing = rb.mWuxing;
	if (ballType > 0 && ballType < BLUEBALL_FIRST) 
		std::vector<RedBall> mList = getRedBallListFromDatabase("", 0, 0);
	else
		std::vector<BlueBall> mList = getBlueBallListFromDatabase("", 0, 0);

	for (int i = 0; i < (int)mList.size(); i++) {
		if (wuxing == mList[i].mWuxing) {
			for (int j = 0; j < (int) wuxingList.size(); j++) {
				if (mList[i+1].mWuxing == wuxingList[j].wuxing) {
					wuxingList[j].count ++;
				} else {
					wuxingStatistics sta;
					sta.wuxing = mList[i+1].mWuxing;
					sta.count = 0;
					wuxingList.push_back(sta);
				}
			}

			totalCount++;
		}
	}

	printBallWuxingProbability(wuxingList, totalCount, ballType);
	return totalCount;
}

std::vector<RedBall> Algorithm::getRedBallListFromDatabase(char field, int from, int end)
{

}

std::vector<BlueBall> Algorithm::getBlueBallListFromDatabase(char field, int from, int end)
{

}