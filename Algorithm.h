#include <stdio.h>
#include <stdlib.h>

#include "MySqlOperator.h"
#include "Result.h"

class Algorithm
{

    public:

        Algorithm();

        ~Algorithm();

    private:

        Result getLatestResultFromDatabase();

        Result getMaxProbabilityPredictResult();

        void calculateEveryRedBallProbability();

        void calculateEveryBlueBallProbability();

        void comparePredictResultWithActualResult();

        void calculateFirstRedballNumberProbability();

        void calculateFirstRedballWuxingProbability();
}
