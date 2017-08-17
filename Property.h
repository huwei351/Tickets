#ifndef PROPERTY_H
#define PROPERTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <memory>

#define sptr(T) std::shared_ptr<T>
#define make(T,...) std::make_shared<T>(__VA_ARGS__)

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
#ifdef DLT
    RED_NUM_THIRTY_THREE,
    RED_NUM_THIRTY_FOUR,
    RED_NUM_THIRTY_FIVE = 35
#else
    RED_NUM_THIRTY_THREE = 33
#endif
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
#ifndef DLT
    BLUE_NUM_TWELVE = 12,
    BLUE_NUM_THIRTEEN,
    BLUE_NUM_FOURTEEN,
    BLUE_NUM_FIFTEEN,
    BLUE_NUM_SIXTEEN = 16
#else
    BLUE_NUM_TWELVE = 12
#endif
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

enum BallType {
    BALLTYPE_UNKNOWN = 0,
    REDBALL_FIRST = 1,
    REDBALL_SECOND,
    REDBALL_THIRD,
    REDBALL_FOURTH,
    REDBALL_FIFTH,
    REDBALL_SIXTH,
    BLUEBALL_FIRST,
    BLUEBALL_SECOND = 8
};

#ifdef DLT
enum BlueRatio {
    BLUE_RATIO_UNKNOWN = -1,
    ZERO_AND_TWO = 0,
    ONE_AND_ONE,
    TWO_AND_ZERO = 2
};

enum RedRatio {
    RED_RATIO_UNKNOWN = -1,
    ZERO_AND_FIVE = 0,
    ONE_AND_FOUR,
    TWO_AND_THREE,
    THREE_AND_TWO,
    FOUR_AND_ONE,
    FIVE_AND_ZERO = 5
};
#else
enum RedRatio {
    RED_RATIO_UNKNOWN = -1,
    ZERO_AND_SIX = 0,
    ONE_AND_FIVE,
    TWO_AND_FOUR,
    THREE_AND_THREE,
    FOUR_AND_TWO,
    FIVE_AND_ONE,
    SIX_AND_ZERO = 6
};
#endif

static std::string Elememts2String(Elememts elememt)
{
    std::string str = "UNKNOWN";

    switch(elememt) {
        case METAL:
            str = "metal";
            break;

        case WOOD:
            str = "wood";
            break;

        case WATER:
            str = "water";
            break;

        case FIRE:
            str = "fire";
            break;

        case EARTH:
            str = "earth";
            break;

        default:
            break;
    }

    return str;
}

static std::string getLogTitleFromBalltype(BallType ballType)
{
    switch(ballType) {
        case REDBALL_FIRST:
            return "1st RedBall";

        case REDBALL_SECOND:
            return "2nd RedBall";

        case REDBALL_THIRD:
            return "3rd RedBall";

        case REDBALL_FOURTH:
            return "4th RedBall";

        case REDBALL_FIFTH:
            return "5th RedBall";

        case REDBALL_SIXTH:
            return "6th RedBall";

        case BLUEBALL_FIRST:
            return "1st BlueBall";

        case BLUEBALL_SECOND:
            return "2nd BlueBall";

        default:
            break;
    }

    return "";
}

static char* Balltype2FieldName(BallType ballType)
{
    switch(ballType) {
        case REDBALL_FIRST:
            return FIELD_RB_FIRST;

        case REDBALL_SECOND:
            return FIELD_RB_SECOND;

        case REDBALL_THIRD:
            return FIELD_RB_THIRD;

        case REDBALL_FOURTH:
            return FIELD_RB_FOURTH;

        case REDBALL_FIFTH:
            return FIELD_RB_FIFTH;

        case REDBALL_SIXTH:
            return FIELD_RB_SIXTH;

        case BLUEBALL_FIRST:
            return FIELD_BB1;

        case BLUEBALL_SECOND:
            return FIELD_BB2;

        default:
            break;
    }

    return "";
}

static Elememts RedNumber2Elememt(RedNumbers num)
{
    switch(num) {
        case RED_NUM_NINE:
        case RED_NUM_TEN:
        case RED_NUM_TWENTY_ONE:
        case RED_NUM_TWENTY_TWO:
        case RED_NUM_THIRTY_THREE:
#ifdef DLT
        case RED_NUM_THIRTY_FOUR:
#endif
            return METAL;

        case RED_NUM_THREE:
        case RED_NUM_FOUR:
        case RED_NUM_FIFTEEN:
        case RED_NUM_SIXTEEN:
        case RED_NUM_TWENTY_SEVEN:
        case RED_NUM_TWENTY_EIGHT:
            return WOOD;

        case RED_NUM_ONE:
        case RED_NUM_TWELVE:
        case RED_NUM_THIRTEEN:
        case RED_NUM_TWENTY_FOUR:
        case RED_NUM_TWENTY_FIVE:
            return WATER;

        case RED_NUM_SIX:
        case RED_NUM_SEVEN:
        case RED_NUM_EIGHTEEN:
        case RED_NUM_NINTEEN:
        case RED_NUM_THIRTY:
        case RED_NUM_THIRTY_ONE:
            return FIRE;

        case RED_NUM_TWO:
        case RED_NUM_FIVE:
        case RED_NUM_EIGHT:
        case RED_NUM_ELEVEN:
        case RED_NUM_FOURTEEN:
        case RED_NUM_SEVENTEEN:
        case RED_NUM_TWENTY:
        case RED_NUM_TWENTY_THREE:
        case RED_NUM_TWENTY_SIX:
        case RED_NUM_TWENTY_NINE:
        case RED_NUM_THIRTY_TWO:
#ifdef DLT
        case RED_NUM_THIRTY_FIVE:
#endif
            return EARTH;

        default:
            break;
    }

    return ELEMEMTS_UNKNOWN;
}

static Elememts BlueNumber2Elememt(BlueNumbers num)
{
    switch(num) {
        case BLUE_NUM_NINE:
        case BLUE_NUM_TEN:
            return METAL;

        case BLUE_NUM_THREE:
        case BLUE_NUM_FOUR:
#ifndef DLT
        case BLUE_NUM_FIFTEEN:
        case BLUE_NUM_SIXTEEN:
#endif
            return WOOD;

        case BLUE_NUM_ONE:
        case BLUE_NUM_TWELVE:
#ifndef DLT
        case BLUE_NUM_THIRTEEN:
#endif
            return WATER;

        case BLUE_NUM_SIX:
        case BLUE_NUM_SEVEN:
            return FIRE;

        case BLUE_NUM_TWO:
        case BLUE_NUM_FIVE:
        case BLUE_NUM_EIGHT:
        case BLUE_NUM_ELEVEN:
#ifndef DLT
        case BLUE_NUM_FOURTEEN:
#endif
            return EARTH;

        default:
            break;
    }

    return ELEMEMTS_UNKNOWN;
}


#endif

