#include <string>
#include <vector>
#include <utils/Singleton.h>
#include <utils/Mutex.h>
#include <utils/String8.h>

#include "Property.h"


class BlueBall : public RefBase
{
    public:

        /* ball number 01-33 */
        int mNum;

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

        BlueBall(int num,
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
}

