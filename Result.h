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
        sptr(RedBall) mR1;

        /* red ball 2 */
        sptr(RedBall) mR2;

        /* red ball 3 */
        sptr(RedBall) mR3;

        /* red ball 4 */
        sptr(RedBall) mR4;

        /* red ball 5 */
        sptr(RedBall) mR5;
#ifdef DLT
        /* blue ball 1 */
        sptr(BlueBall) mB1;

        /* blue ball 2 */
        sptr(BlueBall) mB2;
#else
        /* red ball 6 */
        sptr(RedBall) mR6;

        /* blue ball */
        sptr(BlueBall) mB0;
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
#ifdef DLT
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
            mR1 = make(RedBall);
            mR2 = make(RedBall);
            mR3 = make(RedBall);
            mR4 = make(RedBall);
            mR5 = make(RedBall);
#ifdef DLT
            mB1 = make(BlueBall);
            mB2 = make(BlueBall);
#else
            mR6 = make(RedBall);
            mB0 = make(BlueBall);
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

		Result(RedNumbers rn1, RedNumbers rn2, RedNumbers rn3, RedNumbers rn4, RedNumbers rn5,
#ifdef DLT
			   BlueNumbers bn1, BlueNumbers bn2)
#else
			   RedNumbers rn6, BlueNumbers bn0)
#endif
		{
			mR1 = make(RedBall, rn1);
			mR2 = make(RedBall, rn2);
			mR3 = make(RedBall, rn3);
			mR4 = make(RedBall, rn4);
			mR5 = make(RedBall, rn5);
#ifdef DLT
			mB1 = make(BlueBall, bn1);
			mB2 = make(BlueBall, bn2);
#else
			mR6 = make(RedBall, rn6);
			mB0 = make(BlueBall, bn0);
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

        Result(sptr(RedBall) r1, sptr(RedBall) r2, sptr(RedBall) r3, sptr(RedBall) r4, sptr(RedBall) r5,
#ifdef DLT
               sptr(BlueBall) b1, sptr(BlueBall) b2)
#else
               sptr(RedBall) r6, sptr(BlueBall) b0)
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

