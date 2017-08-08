#ifndef ACCURACY_TEST_PATH
#define ACCURACY_TEST_PATH

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "MySqlOperator.h"
#include "Result.h"
#include "MyConfig.h"
#include "Algorithm.h"

class AccuracyTest
{

    public:

        AccuracyTest(MySqlOperator *mysqloperator);

        ~AccuracyTest();

		int getDatabaseTableLength(char *table);

        Result* getResultFromDatabase(int id);

        static bool sortByPro(const resultStatistics &rs1, const resultStatistics &rs2);

        static bool sortByPro1(const redballStatistics &rs1, const redballStatistics &rs2);

        static bool sortByPro2(const blueballStatistics &bs1, const blueballStatistics &bs2);

        static bool sortByCount(const wuxingStatistics &ws1, const wuxingStatistics &ws2);

        static bool sortByCount1(const rnumStatistics &rs1, const rnumStatistics &rs2);

        static bool sortByCount2(const bnumStatistics &bs1, const bnumStatistics &bs2);

        void rearrangePredictResult(std::vector<resultStatistics> *resultSta, int top);

        std::vector<resultStatistics> getMaxProbabilityPredictResult(int id);

        std::vector<redballStatistics> calculateRedBallProbability(RedBall *rb, int id);

        std::vector<blueballStatistics> calculateBlueBallProbability(BlueBall *bb, int id);

        int calculateRedBallNumberAndWuxingProbability(int id, RedBall *rb, int &total_rnum, int &total_wuxing,
                                                       std::vector<rnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList);
        int calculateBlueBallNumberAndWuxingProbability(int id, BlueBall *bb, int &total_bnum, int &total_wuxing,
                                                        std::vector<bnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList);

        std::vector<RedBall*> getRedBallListFromDatabase(char *field, int id);

        std::vector<BlueBall*> getBlueBallListFromDatabase(char *field, int id);

        bool is2ResultsEqual(Result *r1, Result *r2, int level);

        std::vector<float> getAccuracyForDifferentWeight(float num_wt, float wuxing_wt);

        void startAccuracyTest();

        bool writeAccuracyData2File(std::vector<float> accuList, int index);

    private:

        MySqlOperator* mMySqlOperator;
        float NUM_WEIGHT = 0.5;
        float WUXING_WEIGHT = 0.5;
        int TABALE_LENGTH;

};

#endif
