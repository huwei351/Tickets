#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Property.h"


class RedBall
{
    public:

        /* ball number 01-33 */
        RedNumbers mNum;

        /* the unit number, example: 12, unit is 2 */
        int mUnit;

        /* the decade number, example: 12, unit is 1 */
        int mDecade;

        /* parity JI or OU */
        Parity mJiou;

        /* DA or XIAO */
        BigOrSmall mDaxiao;

        /* ZHI or HE */
        PrimeOrComposite mZhihe;

        /* WuXing : JIN, MU, SHUI, HUO, TU */
        Elememts mWuxing;


        RedBall() {
            mNum = 0;
            mUnit = 0;
            mDecade = 0;
            mJiou = -1;
            mDaxiao = -1;
            mZhihe = -1;
            mWuxing = -1;
        }

        RedBall(RedNumbers num) {
            completeInstanceAccordingNum(num);
        }

        RedBall(RedNumbers num,
                int unit,
                int decade,
                Parity jiou,
                BigOrSmall daxiao,
                PrimeOrComposite zhihe,
                Elememts wuxing) {
            mNum = num;
            mUnit = unit;
            mDecade = decade;
            mJiou = jiou;
            mDaxiao = daxiao;
            mZhihe = zhihe;
            mWuxing = wuxing;
        }

        void setNum(RedNumbers num) {
            mNum = num;
        }

        void setUnit(int unit) {
            mUnit = unit;
        }

        void setDecade(int decade) {
            mDecade = decade;
        }

        void setParity(Parity jiou) {
            mJiou = jiou;
        }

        void setBigOrSmall(BigOrSmall daxiao) {
            mDaxiao = daxiao;
        }

        void setPrimeOrComposite(PrimeOrComposite zhihe) {
            mZhihe = zhihe;
        }

        void setElememts(Elememts wuxing) {
            mWuxing = wuxing;
        }

        void setVariableValue(RedNumbers num,
                              int unit,
                              int decade,
                              Parity jiou,
                              BigOrSmall daxiao,
                              PrimeOrComposite zhihe,
                              Elememts wuxing) {
            setNum(num);
            setUnit(unit);
            setDecade(decade);
            setParity(jiou);
            setBigOrSmall(daxiao);
            setPrimeOrComposite(zhihe);
            setElememts(wuxing);
        }

        void completeInstanceAccordingNum(RedNumbers num) {
            switch(num) {
                case RED_NUM_ONE:
                    setVariableValue(num, 1, 0, ODD, SMALL, PRIME, WATER);
                    break;

                case RED_NUM_TWO:
                    setVariableValue(num, 2, 0, EVEN, SMALL, PRIME, WATER);
                    break;

                    //TODO
                default:
                    break;
            }
        }

#if 0
        int getUnitFromNum(RedNumbers num) {
        }

        int getDecadeFromNum(RedNumbers num) {
        }

        Parity getParityFromNum(RedNumbers num) {
        }

        BigOrSmall getBigOrSmallFromNum(RedNumbers num) {
        }

        PrimeOrComposite getPrimeOrCompositeFromNum(RedNumbers num) {
        }

        Elememts getElememtsFromNum(RedNumbers num) {
        }
#endif
};

