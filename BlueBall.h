#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Property.h"


class BlueBall
{
    public:

        /* ball number 01-33 */
        BlueNumbers mNum;

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


        BlueBall() {
            mNum = 0;
            mUnit = 0;
            mDecade = 0;
            mJiou = -1;
            mDaxiao = -1;
            mZhihe = -1;
            mWuxing = -1;
        }

        RedBall(BlueNumbers num) {
            completeInstanceAccordingNum(num);
        }

        BlueBall(BlueNumbers num,
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

        void setNum(BlueNumbers num) {
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

        void setVariableValue(BlueNumbers num,
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

        void completeInstanceAccordingNum(BlueNumbers num) {
            switch(num) {
				case BLUE_NUM_ONE:
					setVariableValue(num, 1, 0, ODD, SMALL, PRIME, WATER);
					break;
				
				case BLUE_NUM_TWO:
					setVariableValue(num, 2, 0, EVEN, SMALL, PRIME, EARTH);
					break;
				
				case BLUE_NUM_THREE:
					setVariableValue(num, 3, 0, ODD, SMALL, PRIME, WOOD);
					break;
				
				case BLUE_NUM_FOUR:
					setVariableValue(num, 4, 0, EVEN, SMALL, COMPOSITE, WOOD);
					break;
					
				case BLUE_NUM_FIVE:
					setVariableValue(num, 5, 0, ODD, SMALL, PRIME, EARTH);
					break;
					
				case BLUE_NUM_SIX:
					setVariableValue(num, 6, 0, EVEN, SMALL, COMPOSITE, FIRE);
					break;
					
				case BLUE_NUM_SEVEN:
					setVariableValue(num, 7, 0, ODD, SMALL, PRIME, FIRE);
					break;
					
				case BLUE_NUM_EIGHT:
					setVariableValue(num, 8, 0, EVEN, SMALL, COMPOSITE, EARTH);
					break;
					
				case BLUE_NUM_NINE:
					setVariableValue(num, 9, 0, ODD, BIG, COMPOSITE, METAL);
					break;
					
				case BLUE_NUM_TEN:
					setVariableValue(num, 0, 1, EVEN, BIG, COMPOSITE, METAL);
					break;
				
				case BLUE_NUM_ELEVEN:
					setVariableValue(num, 1, 1, ODD, BIG, PRIME, EARTH);
					break;
				
				case BLUE_NUM_TWELVE:
					setVariableValue(num, 2, 1, EVEN, BIG, COMPOSITE, WATER);
					break;
				
				case BLUE_NUM_THIRTEEN:
					setVariableValue(num, 3, 1, ODD, BIG, PRIME, WATER);
					break;
				
				case BLUE_NUM_FOURTEEN:
					setVariableValue(num, 4, 1, EVEN, BIG, COMPOSITE, EARTH);
					break;
					
				case BLUE_NUM_FIFTEEN:
					setVariableValue(num, 5, 1, ODD, BIG, COMPOSITE, WOOD);
					break;
					
				case BLUE_NUM_SIXTEEN:
					setVariableValue(num, 6, 1, EVEN, BIG, COMPOSITE, WOOD);
					break;

                default:
                    break;
            }
        }
#if 0
        int getUnitFromNum(BlueNumbers num) {
        }

        int getDecadeFromNum(BlueNumbers num) {
        }

        Parity getParityFromNum(BlueNumbers num) {
        }

        BigOrSmall getBigOrSmallFromNum(BlueNumbers num) {
        }

        PrimeOrComposite getPrimeOrCompositeFromNum(BlueNumbers num) {
        }

        Elememts getElememtsFromNum(BlueNumbers num) {
        }
#endif
};

