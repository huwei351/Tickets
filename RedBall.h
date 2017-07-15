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
                    setVariableValue(num, 2, 0, EVEN, SMALL, PRIME, EARTH);
                    break;

				case RED_NUM_THREE:
					setVariableValue(num, 3, 0, ODD, SMALL, PRIME, WOOD);
					break;

				case RED_NUM_FOUR:
					setVariableValue(num, 4, 0, EVEN, SMALL, COMPOSITE, WOOD);
					break;
					
				case RED_NUM_FIVE:
					setVariableValue(num, 5, 0, ODD, SMALL, PRIME, EARTH);
					break;
					
				case RED_NUM_SIX:
					setVariableValue(num, 6, 0, EVEN, SMALL, COMPOSITE, FIRE);
					break;
					
				case RED_NUM_SEVEN:
					setVariableValue(num, 7, 0, ODD, SMALL, PRIME, FIRE);
					break;
					
				case RED_NUM_EIGHT:
					setVariableValue(num, 8, 0, EVEN, SMALL, COMPOSITE, EARTH);
					break;
					
				case RED_NUM_NINE:
					setVariableValue(num, 9, 0, ODD, SMALL, COMPOSITE, METAL);
					break;
					
				case RED_NUM_TEN:
					setVariableValue(num, 0, 1, EVEN, SMALL, COMPOSITE, METAL);
					break;

                case RED_NUM_ELEVEN:
                    setVariableValue(num, 1, 1, ODD, SMALL, PRIME, EARTH);
                    break;

                case RED_NUM_TWELVE:
                    setVariableValue(num, 2, 1, EVEN, SMALL, COMPOSITE, WATER);
                    break;

				case RED_NUM_THIRTEEN:
					setVariableValue(num, 3, 1, ODD, SMALL, PRIME, WATER);
					break;

				case RED_NUM_FOURTEEN:
					setVariableValue(num, 4, 1, EVEN, SMALL, COMPOSITE, EARTH);
					break;
					
				case RED_NUM_FIFTEEN:
					setVariableValue(num, 5, 1, ODD, SMALL, COMPOSITE, WOOD);
					break;
					
				case RED_NUM_SIXTEEN:
					setVariableValue(num, 6, 1, EVEN, SMALL, COMPOSITE, WOOD);
					break;
					
				case RED_NUM_SEVENTEEN:
					setVariableValue(num, 7, 1, ODD, BIG, PRIME, EARTH);
					break;
					
				case RED_NUM_EIGHTEEN:
					setVariableValue(num, 8, 1, EVEN, BIG, COMPOSITE, FIRE);
					break;
					
				case RED_NUM_NINETEEN:
					setVariableValue(num, 9, 1, ODD, BIG, PRIME, FIRE);
					break;
					
				case RED_NUM_TWENTY:
					setVariableValue(num, 0, 2, EVEN, BIG, COMPOSITE, EARTH);
					break;

				case RED_NUM_TWENTY_ONE:
					setVariableValue(num, 1, 2, ODD, BIG, COMPOSITE, METAL);
					break;
				
				case RED_NUM_TWENTY_TWO:
					setVariableValue(num, 2, 2, EVEN, BIG, COMPOSITE, METAL);
					break;
				
				case RED_NUM_TWENTY_THREE:
					setVariableValue(num, 3, 2, ODD, BIG, PRIME, EARTH);
					break;
				
				case RED_NUM_TWENTY_FOUR:
					setVariableValue(num, 4, 2, EVEN, BIG, COMPOSITE, WATER);
					break;
					
				case RED_NUM_TWENTY_FIVE:
					setVariableValue(num, 5, 2, ODD, BIG, COMPOSITE, WATER);
					break;
					
				case RED_NUM_TWENTY_SIX:
					setVariableValue(num, 6, 2, EVEN, BIG, COMPOSITE, EARTH);
					break;
					
				case RED_NUM_TWENTY_SEVEN:
					setVariableValue(num, 7, 2, ODD, BIG, COMPOSITE, WOOD);
					break;
					
				case RED_NUM_TWENTY_EIGHT:
					setVariableValue(num, 8, 2, EVEN, BIG, COMPOSITE, WOOD);
					break;
					
				case RED_NUM_TWENTY_NINE:
					setVariableValue(num, 9, 2, ODD, BIG, PRIME, EARTH);
					break;
					
				case RED_NUM_THIRTY:
					setVariableValue(num, 0, 3, EVEN, BIG, COMPOSITE, FIRE);
					break;

				case RED_NUM_THIRTY_ONE:
					setVariableValue(num, 1, 3, ODD, BIG, PRIME, FIRE);
					break;
					
				case RED_NUM_THIRTY_TWO:
					setVariableValue(num, 2, 3, EVEN, BIG, COMPOSITE, EARTH);
					break;
					
				case RED_NUM_THIRTY_THREE:
					setVariableValue(num, 3, 3, ODD, BIG, COMPOSITE, METAL);
					break;

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

