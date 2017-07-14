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

        bool updateDatabase();

        Result getLatestResultFromDatabase();

        void rearrangePredictResult(std::vector<resultStatistics> resultSta, int top);

        void printPredictResult(std::vector<resultStatistics> resultSta);

        Result getMaxProbabilityPredictResult(int top);

        std::vector<redballStatistics> calculateRedBallProbability(int ballType);

        std::vector<blueballStatistics> calculateBlueBallProbability(int ballType);

        void comparePredictResultWithActualResult();

        std::string getLogTitleFromBalltype(int ballType);

        void printRedballNumberProbability(std::vector<rnumStatistics> sta, int total, int ballType);

        void printBlueballNumberProbability(std::vector<bnumStatistics> sta, int total, int ballType);

        void printBallWuxingProbability(std::vector<wuxingStatistics> sta, int total, int ballType);

        int calculateRedBallNumberProbability(int ballType, std::vector<rnumStatistics> staList);

        int calculateBlueBallNumberProbability(int ballType, std::vector<bnumStatistics> staList);

        int calculateBallWuxingProbability(int ballType, std::vector<wuxingStatistics> wuxingList);

        std::vector<RedBall> getRedBallListFromDatabase(char field, int rnum);

        std::vector<BlueBall> getBlueBallListFromDatabase(char field, int rnum);

};
