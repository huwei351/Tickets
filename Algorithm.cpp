#include <stdio.h>
#include <stdlib.h>

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

typedef struct numStatistics
{
	RedNumbers rn;
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

Algorithm::Algorithm()
{
}

Result Algorithm::getLatestResultFromDatabase()
{
}

Result Algorithm::getMaxProbabilityPredictResult()
{
}

void Algorithm::calculateEveryRedBallProbability()
{
	static float NUM_WEIGHT = 0.5;
	static float WUXING_WEIGHT = 0.5;
	std::vector<numStatistics> staList;
	std::vector<wuxingStatistics> wuxingList;
	std::vector<redballStatistics> rStaList;
	float PROBABILITY_METAL = 0;
	float PROBABILITY_WOOD = 0;
	float PROBABILITY_WATER = 0;
	float PROBABILITY_FIRE = 0;
	float PROBABILITY_EARTH = 0;

	int total1 = calculateBallNumberProbability(REDBALL_FIRST, staList);
	int total2 = calculateBallWuxingProbability(REDBALL_FIRST, wuxingList);

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

	for (int j = 0; j < (int)staList.size(); j++) {
		RedBall redball = new RedBall(staList[i].rn);
		switch (redball.mWuxing) {
			case Elememts.METAL:
				prob = (float) staList[i].count/total1 * PROBABILITY_METAL; 
				break;
			case Elememts.WOOD:
				prob = (float) staList[i].count/total1 * PROBABILITY_WOOD; 
				break;
			case Elememts.WATER:
				prob = (float) staList[i].count/total1 * PROBABILITY_WATER; 
				break;
			case Elememts.FIRE:
				prob = (float) staList[i].count/total1 * PROBABILITY_FIRE; 
				break;
			case Elememts.EARTH:
				prob = (float) staList[i].count/total1 * PROBABILITY_EARTH; 
				break;
			default:
				break;
		}

		redballStatistics rsta;
		rsta.redball = redball;
		rsta.probability = prob;
		rStaList.push_back(rsta);
	}
}

void Algorithm::calculateEveryBlueBallProbability()
{
}

void Algorithm::comparePredictResultWithActualResult()
{
}

void Algorithm::printRedballNumberProbability(std::vector<numStatistics> sta, int total)
{
	for (int i = 0; i < (int)sta.size(); i++) {
		printf("1st RedBall [%d] : num = %d, count = %d, probability = %0.3f\n", i+1, sta[i].rn, sta[i].count, (float)sta[i].count/total);
	}
}

void Algorithm::printRedballWuxingProbability(std::vector<wuxingStatistics> sta, int total)
{
	for (int i = 0; i < (int)sta.size(); i++) {
		printf("1st RedBall [%d] : wuxing = %d, count = %d, probability = %0.3f\n", i+1, sta[i].wuxing, sta[i].count, (float)sta[i].count/total);
	}
}

int Algorithm::calculateBallNumberProbability(int ballType, std::vector<numStatistics> staList)
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
					numStatistics sta;
					sta.rn = mList[i+1].mNum;
					sta.count = 0;
					staList.push_back(sta);
				}
			}

			totalCount++;
		}
	}

	printRedballNumberProbability(staList, totalCount);
	return totalCount;
}

int Algorithm::calculateBallWuxingProbability(int ballType, std::vector<wuxingStatistics> wuxingList)
{
	Result result = getLatestResultFromDatabase();
	RedBall rb = result.mR1;
	Elememts wuxing = rb.mWuxing;
	std::vector<RedBall> mList = getBallListFromDatabase("", 0, 0);
	int totalCount = 0;

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

	printRedballWuxingProbability(wuxingList, totalCount);
	return totalCount;
}

std::vector<RedBall> getBallListFromDatabase(char field, int from, int end)
{

}