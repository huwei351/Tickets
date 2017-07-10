#include <stdio.h>
#include <stdlib.h>

#include "MySqlOperator.h"
#include "Result.h"
#include "RedBall.h"
#include "BlueBall.h"

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
}

void Algorithm::calculateEveryBlueBallProbability()
{
}

void Algorithm::comparePredictResultWithActualResult()
{
}

void Algorithm::calculateFirstRedballNumberProbability()
{
	Result result = getLatestResultFromDatabase();
	RedBall rb = result.mR1;
	RedNumbers num = rb.mNum;
}

void Algorithm::calculateFirstRedballWuxingProbability()
{

}