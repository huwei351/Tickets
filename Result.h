#include <string>
#include <vector>

#include "RedBall.h"
#include "BlueBall.h"


class Result
{
    public:

        /* red ball 1 */
        RedBall mR1;

        /* red ball 2 */
        RedBall mR2;

        /* red ball 3 */
        RedBall mR3;

        /* red ball 4 */
        RedBall mR4;

        /* red ball 5 */
        RedBall mR5;
#if defined(SSQ)
        /* red ball 6 */
        RedBall mR6;

        /* blue ball */
        BlueBall mB0;
#elif defined(DLT)
        /* blue ball 1 */
        BlueBall mB1;

        /* blue ball 2 */
        BlueBall mB2;
#endif

        typedef enum {
#if defined(DLT)
            ZERO_AND_TWO = 0,
            ONE_AND_ONE,
            TWO_AND_ZERO
        } BlueRatio;

        typedef enum {
            ZERO_AND_FIVE = 0,
            ONE_AND_FOUR,
            TWO_AND_THREE,
            THREE_AND_TWO,
            FOUR_AND_ONE,
            FIVE_AND_ZERO
#elif defined(SSQ)
			ZERO_AND_SIX = 0,
            ONE_AND_FIVE,
            TWO_AND_FOUR,
            THREE_AND_THREE,
            FOUR_AND_TWO,
            FIVE_AND_ONE,
            SIX_AND_ZERO
#endif
        } RedRatio;

        /* Red ball sum */
        int mRedSum;

        /* the sum of each red ball unit number */
        int mUnitSum;

        /* the decade number, example: 12, unit is 1 */
#if defined(SSQ)
        int mRedSumAverage = mRedSum / 6;
#elif defined(DLT)
        int mRedSumAverage = mRedSum / 5;
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
#if defined(SSQ)
            mR6 = new RedBall();
            mB0 = new BlueBall();
#elif defined(DLT)
            mB1 = new BlueBall();
            mB2 = new BlueBall();
#endif
            mRedSum = 0;
            mUnitSum = 0;
            mRedSumAverage = 0;
            mJiouRatio = -1;
            mDaxiaoRatio = -1;
            mZhiheRatio = -1;
        }

        Result(RedBall r1, RedBall r2, RedBall r3, RedBall r4, RedBall r5, 
#if defined(SSQ)
            RedBall r6, BlueBall b0)
#elif defined(DLT)
            BlueBall b1, BlueBall b2)
#endif
{
			mR1 = r1;
            mR2 = r2;
            mR3 = r3;
            mR4 = r4;
            mR5 = r5;
#if defined(SSQ)
            mR6 = r6;
            mB0 = b0;
#elif defined(DLT)
            mB1 = b1;
            mB2 = b2;
#endif
            mRedSum = 0;
            mUnitSum = 0;
            mRedSumAverage = 0;
            mJiouRatio = -1;
            mDaxiaoRatio = -1;
            mZhiheRatio = -1;
        }

};

