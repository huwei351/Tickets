#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <vector>
//#include <utils/Singleton.h>
//#include <utils/Mutex.h>
//#include <utils/String8.h>


class StringUtil
{
    public:
        static bool StringIsEmpty(std::string string);
        static void StringSplit(std::vector<std::string> &strings, std::string string, const char* separator);
        static bool StringStartsWith(std::string string, const char* prefix);
        static bool StringEndsWith(std::string string, const char* prefix);
        static void StringFindValue(std::string string, std::string &value, std::string index);
};

#endif
