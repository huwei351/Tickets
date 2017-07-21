#ifndef PROPERTY_H
#define PROPERTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>


/* RedBall Numbers */
enum RedNumbers {
    RED_NUM_INVALID = 0,
    RED_NUM_ONE = 1,
    RED_NUM_TWO,
    RED_NUM_THREE,
    RED_NUM_FOUR,
    RED_NUM_FIVE,
    RED_NUM_SIX,
    RED_NUM_SEVEN,
    RED_NUM_EIGHT,
    RED_NUM_NINE,
    RED_NUM_TEN,
    RED_NUM_ELEVEN,
    RED_NUM_TWELVE,
    RED_NUM_THIRTEEN,
    RED_NUM_FOURTEEN,
    RED_NUM_FIFTEEN,
    RED_NUM_SIXTEEN,
    RED_NUM_SEVENTEEN,
    RED_NUM_EIGHTEEN,
    RED_NUM_NINTEEN,
    RED_NUM_TWENTY,
    RED_NUM_TWENTY_ONE,
    RED_NUM_TWENTY_TWO,
    RED_NUM_TWENTY_THREE,
    RED_NUM_TWENTY_FOUR,
    RED_NUM_TWENTY_FIVE,
    RED_NUM_TWENTY_SIX,
    RED_NUM_TWENTY_SEVEN,
    RED_NUM_TWENTY_EIGHT,
    RED_NUM_TWENTY_NINE,
    RED_NUM_THIRTY,
    RED_NUM_THIRTY_ONE,
    RED_NUM_THIRTY_TWO,
    RED_NUM_THIRTY_THREE = 33
};

/* BlueBall Numbers */
enum BlueNumbers {
    BLUE_NUM_INVALID = 0,
    BLUE_NUM_ONE = 1,
    BLUE_NUM_TWO,
    BLUE_NUM_THREE,
    BLUE_NUM_FOUR,
    BLUE_NUM_FIVE,
    BLUE_NUM_SIX,
    BLUE_NUM_SEVEN,
    BLUE_NUM_EIGHT,
    BLUE_NUM_NINE,
    BLUE_NUM_TEN,
    BLUE_NUM_ELEVEN,
    BLUE_NUM_TWELVE,
    BLUE_NUM_THIRTEEN,
    BLUE_NUM_FOURTEEN,
    BLUE_NUM_FIFTEEN,
    BLUE_NUM_SIXTEEN = 16
};

/* parity */
enum Parity {
    PARITY_UNKNOWN = -1,
    ODD = 0,
    EVEN = 1
};

/* big: num >= 17, small: num <= 16*/
enum BigOrSmall {
    BIG_SMALL_UNKNOWN = -1,
    BIG = 0,
    SMALL = 1
};

/* Prime number or Composite number*/
enum PrimeOrComposite {
    PRIME_COMPOSITE_UNKNOWN = -1,
    PRIME = 0,
    COMPOSITE = 1
};

enum Elememts {
    ELEMEMTS_UNKNOWN = -1,
    METAL = 0,
    WOOD = 1,
    WATER = 2,
    FIRE = 3,
    EARTH = 4
};

#endif

