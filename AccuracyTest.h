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

        AccuracyTest(sptr(MySqlOperator) mysqloperator);

        ~AccuracyTest();

        int getDatabaseTableLength(char *table);

        sptr(Result) getResultFromDatabase(int id);

        std::vector<sptr(Result)> getResultListFromDatabase(int begin, int end);

        static bool sortByPro(const resultStatistics &rs1, const resultStatistics &rs2);

        static bool sortByPro1(const redballStatistics &rs1, const redballStatistics &rs2);

        static bool sortByPro2(const blueballStatistics &bs1, const blueballStatistics &bs2);

        static bool sortByCount(const wuxingStatistics &ws1, const wuxingStatistics &ws2);

        static bool sortByCount1(const rnumStatistics &rs1, const rnumStatistics &rs2);

        static bool sortByCount2(const bnumStatistics &bs1, const bnumStatistics &bs2);

        void rearrangePredictResult(std::vector<resultStatistics> *resultSta, int top);

        std::string printPredictResult(std::vector<resultStatistics> resultSta);

        std::vector<resultStatistics> getMaxProbabilityPredictResult(int id);

        std::vector<redballStatistics> calculateRedBallProbability(sptr(RedBall) rb, int id);

        std::vector<blueballStatistics> calculateBlueBallProbability(sptr(BlueBall) bb, int id);

        int calculateRedBallNumberAndWuxingProbability(int id, sptr(RedBall) rb, int &total_rnum, int &total_wuxing,
                                                       std::vector<rnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList);
        int calculateBlueBallNumberAndWuxingProbability(int id, sptr(BlueBall) bb, int &total_bnum, int &total_wuxing,
                                                        std::vector<bnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList);

        std::vector< sptr(RedBall) > getRedBallListFromDatabase(char *field, int id);

        std::vector< sptr(BlueBall) > getBlueBallListFromDatabase(char *field, int id);

        bool is2ResultsEqual(sptr(Result) r1, sptr(Result) r2, int level);

        std::vector<float> getAccuracyForDifferentWeight(float num_wt, float wuxing_wt);

        void startAccuracyTest();

        void startAccuracyTest2();

        void startAccuracyTest3();

        void startAccuracyTest4();

        void startAccuracyTest5();

        void startAccuracyTest6();

        bool writeAccuracyData2File(std::string data, int index);

    private:

        sptr(MySqlOperator) mMySqlOperator;
        float NUM_WEIGHT = 0.5;
        float WUXING_WEIGHT = 0.5;
        int TABALE_LENGTH;
        int PREDICT_BASE = 1500;

};

#endif
