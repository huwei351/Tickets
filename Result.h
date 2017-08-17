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

        /* Red ball sum */
        int mRedSum;

        /* the sum of each red ball unit number */
        int mUnitSum;

        /* the decade number, example: 12, unit is 1 */
        int mRedSumAverage;

        /* parity JI or OU */
        RedRatio mJiouRatio;

        /* DA or XIAO */
        RedRatio mDaxiaoRatio;

        /* ZHI or HE */
        RedRatio mZhiheRatio;

#ifdef DLT
        BlueRatio mBlueJiouRatio;

        BlueRatio mBlueDaxiaoRatio;

        BlueRatio mBlueZhiheRatio;
#endif

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
#ifdef DLT
            mBlueJiouRatio = BLUE_RATIO_UNKNOWN;
            mBlueDaxiaoRatio = BLUE_RATIO_UNKNOWN;
            mBlueZhiheRatio = BLUE_RATIO_UNKNOWN;
#endif
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
#ifdef DLT
            mRedSum = (int)(rn1 + rn2 + rn3 + rn4 + rn5);
            mUnitSum = mR1->mUnit + mR2->mUnit + mR3->mUnit + mR4->mUnit + mR5->mUnit;
            mRedSumAverage = mRedSum / 5;
#else
            mRedSum = (int)(rn1 + rn2 + rn3 + rn4 + rn5 + rn6);
            mUnitSum = mR1->mUnit + mR2->mUnit + mR3->mUnit + mR4->mUnit + mR5->mUnit + mR6->mUnit;
            mRedSumAverage = mRedSum / 6;
#endif
            mJiouRatio = calculateJiouRatio();
            mDaxiaoRatio = calculateDaxiaoRatio();
            mZhiheRatio = calculateZhiheRatio();
#ifdef DLT
            mBlueJiouRatio = calculateBlueJiouRatio();
            mBlueDaxiaoRatio = calculateBlueDaxiaoRatio();
            mBlueZhiheRatio = calculateBlueZhiheRatio();
#endif
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
#ifdef DLT
            mRedSum = (int)(r1->mNum + r2->mNum + r3->mNum + r4->mNum + r5->mNum);
            mUnitSum = r1->mUnit + r2->mUnit + r3->mUnit + r4->mUnit + r5->mUnit;
            mRedSumAverage = mRedSum / 5;
#else
            mRedSum = (int)(r1->mNum + r2->mNum + r3->mNum + r4->mNum + r5->mNum + r6->mNum);
            mUnitSum = r1->mUnit + r2->mUnit + r3->mUnit + r4->mUnit + r5->mUnit + r6->mUnit;
            mRedSumAverage = mRedSum / 6;
#endif
            mJiouRatio = calculateJiouRatio();
            mDaxiaoRatio = calculateDaxiaoRatio();
            mZhiheRatio = calculateZhiheRatio();
#ifdef DLT
            mBlueJiouRatio = calculateBlueJiouRatio();
            mBlueDaxiaoRatio = calculateBlueDaxiaoRatio();
            mBlueZhiheRatio = calculateBlueZhiheRatio();
#endif
            mQid = 0;
            mDate = "1997-01-01";
        }

        RedRatio calculateJiouRatio() {
            int odd_count = 0;

            if(mR1->mJiou == ODD) { odd_count++; }

            if(mR2->mJiou == ODD) { odd_count++; }

            if(mR3->mJiou == ODD) { odd_count++; }

            if(mR4->mJiou == ODD) { odd_count++; }

            if(mR5->mJiou == ODD) { odd_count++; }

#ifndef DLT

            if(mR6->mJiou == ODD) { odd_count++; }

            if(odd_count == 0) { return ZERO_AND_SIX; }

            if(odd_count == 1) { return ONE_AND_FIVE; }

            if(odd_count == 2) { return TWO_AND_FOUR; }

            if(odd_count == 3) { return THREE_AND_THREE; }

            if(odd_count == 4) { return FOUR_AND_TWO; }

            if(odd_count == 5) { return FIVE_AND_ONE; }

            if(odd_count == 6) { return SIX_AND_ZERO; }

#else

            if(odd_count == 0) { return ZERO_AND_FIVE; }

            if(odd_count == 1) { return ONE_AND_FOUR; }

            if(odd_count == 2) { return TWO_AND_THREE; }

            if(odd_count == 3) { return THREE_AND_TWO; }

            if(odd_count == 4) { return FOUR_AND_ONE; }

            if(odd_count == 5) { return FIVE_AND_ZERO; }

#endif
        }

        RedRatio calculateDaxiaoRatio() {
            int big_count = 0;

            if(mR1->mDaxiao == BIG) { big_count++; }

            if(mR2->mDaxiao == BIG) { big_count++; }

            if(mR3->mDaxiao == BIG) { big_count++; }

            if(mR4->mDaxiao == BIG) { big_count++; }

            if(mR5->mDaxiao == BIG) { big_count++; }

#ifndef DLT

            if(mR6->mDaxiao == BIG) { big_count++; }

            if(big_count == 0) { return ZERO_AND_SIX; }

            if(big_count == 1) { return ONE_AND_FIVE; }

            if(big_count == 2) { return TWO_AND_FOUR; }

            if(big_count == 3) { return THREE_AND_THREE; }

            if(big_count == 4) { return FOUR_AND_TWO; }

            if(big_count == 5) { return FIVE_AND_ONE; }

            if(big_count == 6) { return SIX_AND_ZERO; }

#else

            if(big_count == 0) { return ZERO_AND_FIVE; }

            if(big_count == 1) { return ONE_AND_FOUR; }

            if(big_count == 2) { return TWO_AND_THREE; }

            if(big_count == 3) { return THREE_AND_TWO; }

            if(big_count == 4) { return FOUR_AND_ONE; }

            if(big_count == 5) { return FIVE_AND_ZERO; }

#endif
        }

        RedRatio calculateZhiheRatio() {
            int prime_count = 0;

            if(mR1->mZhihe == PRIME) { prime_count++; }

            if(mR2->mZhihe == PRIME) { prime_count++; }

            if(mR3->mZhihe == PRIME) { prime_count++; }

            if(mR4->mZhihe == PRIME) { prime_count++; }

            if(mR5->mZhihe == PRIME) { prime_count++; }

#ifndef DLT

            if(mR6->mZhihe == PRIME) { prime_count++; }

            if(prime_count == 0) { return ZERO_AND_SIX; }

            if(prime_count == 1) { return ONE_AND_FIVE; }

            if(prime_count == 2) { return TWO_AND_FOUR; }

            if(prime_count == 3) { return THREE_AND_THREE; }

            if(prime_count == 4) { return FOUR_AND_TWO; }

            if(prime_count == 5) { return FIVE_AND_ONE; }

            if(prime_count == 6) { return SIX_AND_ZERO; }

#else

            if(prime_count == 0) { return ZERO_AND_FIVE; }

            if(prime_count == 1) { return ONE_AND_FOUR; }

            if(prime_count == 2) { return TWO_AND_THREE; }

            if(prime_count == 3) { return THREE_AND_TWO; }

            if(prime_count == 4) { return FOUR_AND_ONE; }

            if(prime_count == 5) { return FIVE_AND_ZERO; }

#endif
        }

#ifdef DLT
        BlueRatio calculateBlueJiouRatio() {
            int odd_count = 0;

            if(mB1->mJiou == ODD) { odd_count++; }

            if(mB2->mJiou == ODD) { odd_count++; }

            if(odd_count == 0) { return ZERO_AND_TWO; }

            if(odd_count == 1) { return ONE_AND_ONE; }

            if(odd_count == 2) { return TWO_AND_ZERO; }
        }

        BlueRatio calculateBlueDaxiaoRatio() {
            int big_count = 0;

            if(mB1->mDaxiao == BIG) { big_count++; }

            if(mB2->mDaxiao == BIG) { big_count++; }

            if(big_count == 0) { return ZERO_AND_TWO; }

            if(big_count == 1) { return ONE_AND_ONE; }

            if(big_count == 2) { return TWO_AND_ZERO; }
        }

        BlueRatio calculateBlueZhiheRatio() {
            int prime_count = 0;

            if(mB1->mZhihe == PRIME) { prime_count++; }

            if(mB2->mZhihe == PRIME) { prime_count++; }

            if(prime_count == 0) { return ZERO_AND_TWO; }

            if(prime_count == 1) { return ONE_AND_ONE; }

            if(prime_count == 2) { return TWO_AND_ZERO; }
        }
#endif
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

        int getRedSum() {
            return mRedSum;
        }

        int getUnitSum() {
            return mUnitSum;
        }

        int getRedSumAverage() {
            return mRedSumAverage;
        }

        RedRatio getJiouRatio() {
            return mJiouRatio;
        }

        RedRatio getDaxiaoRatio() {
            return mDaxiaoRatio;
        }

        RedRatio getZhiheRatio() {
            return mZhiheRatio;
        }

#ifdef DLT
        BlueRatio getBlueJiouRatio() {
            return mBlueJiouRatio;
        }

        BlueRatio getBlueDaxiaoRatio() {
            return mBlueDaxiaoRatio;
        }

        BlueRatio getBlueZhiheRatio() {
            return mBlueZhiheRatio;
        }
#endif


};

#endif

