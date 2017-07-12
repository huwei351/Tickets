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

        void printRedballNumberProbability(std::vector<numStatistics> sta, int total);

        void printRedballWuxingProbability(std::vector<wuxingStatistics> sta, int total);

        void calculateRedballNumberProbability();

        void calculateRedballWuxingProbability();

        std::vector<RedBall> getBallListFromDatabase(char field, int from, int end);
}
