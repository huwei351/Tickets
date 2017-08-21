#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "MySqlOperator.h"
#include "Result.h"
#include "MyConfig.h"

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
    sptr(RedBall) redball;
    float probability;
};

struct blueballStatistics {
    sptr(BlueBall) blueball;
    float probability;
};

struct resultStatistics {
    sptr(Result) result;
    float probability;
};

class Algorithm
{

    public:

        Algorithm(sptr(MySqlOperator) mysqloperator, sptr(MyConfig) myconfig);

        ~Algorithm();

        void setNumAndWuxingWeight(float num, float wuxing);

        void getCurNumAndWuxingWeight(float &num, float &wuxing);

        bool updateDatabase();

        sptr(Result) getLatestResultFromDatabase();

        static bool sortByPro(const resultStatistics &rs1, const resultStatistics &rs2);

        static bool sortByPro1(const redballStatistics &rs1, const redballStatistics &rs2);

        static bool sortByPro2(const blueballStatistics &bs1, const blueballStatistics &bs2);

        static bool sortByCount(const wuxingStatistics &ws1, const wuxingStatistics &ws2);

        static bool sortByCount1(const rnumStatistics &rs1, const rnumStatistics &rs2);

        static bool sortByCount2(const bnumStatistics &bs1, const bnumStatistics &bs2);

        void rearrangePredictResult(std::vector<resultStatistics> *resultSta, int top);

        std::string printPredictResult(std::vector<resultStatistics> resultSta);

        std::vector<resultStatistics> getMaxProbabilityPredictResult(int top);

        std::vector<resultStatistics> getMaxProbabilityPredictResult2(bool all = false);

        float calculateResultProbability(sptr(Result) result);

        std::vector<redballStatistics> calculateRedBallProbability(sptr(RedBall) rb, std::string &content);

        std::vector<blueballStatistics> calculateBlueBallProbability(sptr(BlueBall) bb, std::string &content);

        void comparePredictResultWithActualResult();

        //std::string getLogTitleFromBalltype(int ballType);
        //char* Balltype2FieldName(int ballType);

        void printRedballNumberProbability(std::vector<rnumStatistics> *sta, int total, BallType ballType);

        void printBlueballNumberProbability(std::vector<bnumStatistics> *sta, int total, BallType ballType);

        void printBallWuxingProbability(std::vector<wuxingStatistics> *sta, int total, BallType ballType);
        int calculateRedBallNumberAndWuxingProbability(sptr(RedBall) rb, int &total_rnum, int &total_wuxing,
                                                       std::vector<rnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList);
        int calculateBlueBallNumberAndWuxingProbability(sptr(BlueBall) bb, int &total_bnum, int &total_wuxing,
                                                        std::vector<bnumStatistics> *staList, std::vector<wuxingStatistics> *wuxingList);

        //int calculateRedBallNumberProbability(int ballType, std::vector<rnumStatistics> *staList);

        //int calculateBlueBallNumberProbability(int ballType, std::vector<bnumStatistics> staList);

        //int calculateBallWuxingProbability(int ballType, std::vector<wuxingStatistics> wuxingList);

        std::vector< sptr(RedBall) > getRedBallListFromDatabase(char *field, int rnum);

        std::vector< sptr(BlueBall) > getBlueBallListFromDatabase(char *field, int rnum);

        std::string printRedballPredictTable(BallType type, std::vector<rnumStatistics> rsList,
                                             std::vector<wuxingStatistics> wsList, std::vector<redballStatistics> rbList);

        std::string printBlueballPredictTable(BallType type, std::vector<bnumStatistics> bsList,
                                              std::vector<wuxingStatistics> wsList, std::vector<blueballStatistics> bbList);

        bool saveData2File(std::string dirname, std::string filename, std::string data);

        bool writeLatestPredictResult2File(std::string data);

        bool writeActualLatestResult2LastPredictFile();

    private:

        sptr(MyConfig) mMyConfig;
        sptr(MySqlOperator) mMySqlOperator;
        sptr(Result) mLatestResult;
        float NUM_WEIGHT;
        float WUXING_WEIGHT;
        int rn1_min = 1;
        int rn1_max = 28;
        int rn2_min = 2;
        int rn2_max = 29;
        int rn3_min = 3;
        int rn3_max = 30;
        int rn4_min = 4;
        int rn4_max = 31;
        int rn5_min = 5;
        int rn5_max = 32;
#ifndef DLT
        int rn6_min = 6;
        int rn6_max = 33;
        int bn_min = 1;
        int bn_max = 16;
        int rnsum_min = 21;
        int rnsum_max = 183;
        int unitsum_min = 3;
        int unitsum_max = 51;
        RedRatio red_jiou_ratio = FOUR_AND_TWO;
        RedRatio red_daxiao_ratio = FOUR_AND_TWO;
        RedRatio red_zhihe_ratio = FOUR_AND_TWO;
#else
        int bn1_min = 1;
        int bn1_max = 11;
        int bn2_min = 2;
        int bn2_max = 12;
        int rnsum_min = 15;
        int rnsum_max = 183;
        int unitsum_min = 3;
        int unitsum_max = 51;
        RedRatio red_jiou_ratio = THREE_AND_TWO;
        RedRatio red_daxiao_ratio = THREE_AND_TWO;
        RedRatio red_zhihe_ratio = THREE_AND_TWO;
        BlueRatio blue_jiou_ratio = ZERO_AND_TWO;
        BlueRatio blue_daxiao_ratio = ZERO_AND_TWO;
        BlueRatio blue_zhihe_ratio = ZERO_AND_TWO;
#endif
};

#endif
