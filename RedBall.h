#include <string>
#include <vector>
#include <utils/Singleton.h>
#include <utils/Mutex.h>
#include <utils/String8.h>

#include "Property.h"


class RedBall : public RefBase
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
            mNum = num;
            mUnit = getUnitFromNum(num);
            mDecade = getDecadeFromNum(num);
            mJiou = getParityFromNum(num);
            mDaxiao = getBigOrSmallFromNum(num);
            mZhihe = getPrimeOrCompositeFromNum(num);
            mWuxing = getElememtsFromNum(num);
        }

        RedBall(RedNumbers num,
                int unit,
                int decade,
                Property::Parity jiou,
                Property::BigOrSmall daxiao,
                Property::PrimeOrComposite zhihe,
                Property::Elememts wuxing) {
            mNum = num;
            mUnit = unit;
            mDecade = decade;
            mJiou = jiou;
            mDaxiao = daxiao;
            mZhihe = zhihe;
            mWuxing = wuxing;
        }

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
}

