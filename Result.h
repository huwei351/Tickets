#ifndef RESULT_H
#define RESULT_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "RedBall.h"
#include "BlueBall.h"


class Result
{
    public:

        /* kaijiang qihao */
        int mQid;

        /* kaijiang date */
        std::string mDate;

        /* red ball 1 */
        RedBall *mR1;

        /* red ball 2 */
        RedBall *mR2;

        /* red ball 3 */
        RedBall *mR3;

        /* red ball 4 */
        RedBall *mR4;

        /* red ball 5 */
        RedBall *mR5;
#ifdef DLT
        /* blue ball 1 */
        BlueBall *mB1;

        /* blue ball 2 */
        BlueBall *mB2;
#else
        /* red ball 6 */
        RedBall *mR6;

        /* blue ball */
        BlueBall *mB0;
#endif

#ifdef DLT
        typedef enum {
            BLUE_RATIO_UNKNOWN = -1,
            ZERO_AND_TWO = 0,
            ONE_AND_ONE,
            TWO_AND_ZERO
        } BlueRatio;

        typedef enum {
            RED_RATIO_UNKNOWN = -1,
            ZERO_AND_FIVE = 0,
            ONE_AND_FOUR,
            TWO_AND_THREE,
            THREE_AND_TWO,
            FOUR_AND_ONE,
            FIVE_AND_ZERO
        } RedRatio;
#else
        typedef enum {
            RED_RATIO_UNKNOWN = -1,
            ZERO_AND_SIX = 0,
            ONE_AND_FIVE,
            TWO_AND_FOUR,
            THREE_AND_THREE,
            FOUR_AND_TWO,
            FIVE_AND_ONE,
            SIX_AND_ZERO
        } RedRatio;
#endif

        /* Red ball sum */
        int mRedSum;

        /* the sum of each red ball unit number */
        int mUnitSum;

        /* the decade number, example: 12, unit is 1 */
#ifdef SSQ
        int mRedSumAverage = mRedSum / 5;
#else
        int mRedSumAverage = mRedSum / 6;
#endif

        /* parity JI or OU */
        RedRatio mJiouRatio;

        /* DA or XIAO */
        RedRatio mDaxiaoRatio;

        /* ZHI or HE */
        RedRatio mZhiheRatio;

        Result() {
            mR1 = new RedBall();
            mR2 = new RedBall();
            mR3 = new RedBall();
            mR4 = new RedBall();
            mR5 = new RedBall();
#ifdef DLT
            mB1 = new BlueBall();
            mB2 = new BlueBall();
#else
            mR6 = new RedBall();
            mB0 = new BlueBall();
#endif
            mRedSum = 0;
            mUnitSum = 0;
            mRedSumAverage = 0;
            mJiouRatio = RED_RATIO_UNKNOWN;
            mDaxiaoRatio = RED_RATIO_UNKNOWN;
            mZhiheRatio = RED_RATIO_UNKNOWN;
            mQid = 0;
            mDate = "1997-01-01";
        }

        Result(RedBall *r1, RedBall *r2, RedBall *r3, RedBall *r4, RedBall *r5,
#ifdef DLT
               BlueBall *b1, BlueBall *b2)
#else
               RedBall *r6, BlueBall *b0)
#endif
        {
            mR1 = r1;
            mR2 = r2;
            mR3 = r3;
            mR4 = r4;
            mR5 = r5;
#ifdef DLT
            mB1 = b1;
            mB2 = b2;
#else
            mR6 = r6;
            mB0 = b0;
#endif
            mRedSum = 0;
            mUnitSum = 0;
            mRedSumAverage = 0;
            mJiouRatio = RED_RATIO_UNKNOWN;
            mDaxiaoRatio = RED_RATIO_UNKNOWN;
            mZhiheRatio = RED_RATIO_UNKNOWN;
            mQid = 0;
            mDate = "1997-01-01";
        }

        void setQid(int qid) {
            mQid = qid;
        }

        void setDate(std::string date) {
            mDate = date;
        }

        int getQid() {
            return mQid;
        }

        std::string getDate() {
            return mDate;
        }

};

#endif

