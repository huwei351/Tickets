#include <string>
#include <vector>
#include <utils/Singleton.h>
#include <utils/Mutex.h>
#include <utils/String8.h>


class Property
{
    public:

        /* parity */
        typedef enum {
            ODD = 0X01,
            EVEN = 0x02
        } Parity;

        /* big: num >= 17, small: num <= 16*/
        typedef enum {
            BIG = 0x01,
            SMALL = 0x02
        } BigOrSmall;

        /* Prime number or Composite number*/
        typedef enum {
            PRIME = 0x01,
            COMPOSITE = 0x02
        } PrimeOrComposite;

        typedef enum {
            METAL = 0x01;
            WOOD = 0x02;
            WATER = 0x04;
            FIRE = 0x08;
            EARTH = 0x1F;
        } Elememts;



}

