#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

        static bool sortByPro(const resultStatistics &rs1, const resultStatistics &rs2);
		
		static bool sortByPro1(const redballStatistics &rs1, const redballStatistics &rs2);
		
		static bool sortByPro2(const blueballStatistics &bs1, const blueballStatistics &bs2);
				
		static bool sortByCount(const wuxingStatistics &ws1, const wuxingStatistics &ws2);

		static bool sortByCount1(const rnumStatistics &rs1, const rnumStatistics &rs2);

		static bool sortByCount2(const bnumStatistics &bs1, const bnumStatistics &bs2);

        void rearrangePredictResult(std::vector<resultStatistics> *resultSta, int top);

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

		void printRedballPredictTable(BallType type, std::vector<rnumStatistics> rsList,
				std::vector<wuxingStatistics> wsList, std::vector<redballStatistics> rbList);

		void printBlueballPredictTable(BallType type, std::vector<bnumStatistics> bsList,
				std::vector<wuxingStatistics> wsList, std::vector<blueballStatistics> bbList);

    private:

        MySqlOperator* mMySqlOperator;
        Result *mLatestResult;

};

#endif
