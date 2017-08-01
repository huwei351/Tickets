#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdio.h>
#include <stdlib.h>

#include "MySqlOperator.h"
#include "Result.h"
/*
enum {
    REDBALL_FIRST = 1,
    REDBALL_SECOND,
    REDBALL_THIRD,
    REDBALL_FOURTH,
    REDBALL_FIFTH,
    REDBALL_SIXTH,
    BLUEBALL_FIRST,
    BLUEBALL_SECOND = 8
};
*/
struct rnumStatistics {
    RedNumbers rn;
    int count;
};

struct bnumStatistics {
    BlueNumbers bn;
    int count;
};

struct wuxingStatistics {
    Elememts wuxing;
    int count;
};

struct redballStatistics {
    RedBall *redball;
    float probability;
};

struct blueballStatistics {
    BlueBall *blueball;
    float probability;
};

struct resultStatistics {
    Result *result;
    float probability;
};

class Algorithm
{

    public:

        Algorithm();

        ~Algorithm();

        bool updateDatabase();

        Result* getLatestResultFromDatabase();

        void rearrangePredictResult(std::vector<resultStatistics> resultSta, int top);

        void printPredictResult(std::vector<resultStatistics> resultSta);

        std::vector<resultStatistics> getMaxProbabilityPredictResult(int top);

        std::vector<redballStatistics> calculateRedBallProbability(RedBall *rb);

        std::vector<blueballStatistics> calculateBlueBallProbability(BlueBall *bb);

        void comparePredictResultWithActualResult();

        //std::string getLogTitleFromBalltype(int ballType);
        //char* Balltype2FieldName(int ballType);

        void printRedballNumberProbability(std::vector<rnumStatistics> *sta, int total, BallType ballType);

        void printBlueballNumberProbability(std::vector<bnumStatistics> *sta, int total, BallType ballType);

        void printBallWuxingProbability(std::vector<wuxingStatistics> *sta, int total, BallType ballType);
        int calculateRedBallNumberAndWuxingProbability(RedBall *rb, int &total_rnum, int &total_wuxing,
                                                       std::vector<rnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList);
        int calculateBlueBallNumberAndWuxingProbability(BlueBall *bb, int &total_bnum, int &total_wuxing,
                                                        std::vector<bnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList);

        //int calculateRedBallNumberProbability(int ballType, std::vector<rnumStatistics> *staList);

        //int calculateBlueBallNumberProbability(int ballType, std::vector<bnumStatistics> staList);

        //int calculateBallWuxingProbability(int ballType, std::vector<wuxingStatistics> wuxingList);

        std::vector<RedBall*> getRedBallListFromDatabase(char *field, int rnum);

        std::vector<BlueBall*> getBlueBallListFromDatabase(char *field, int rnum);

    private:

        MySqlOperator* mMySqlOperator;
        Result *mLatestResult;

};

#endif
