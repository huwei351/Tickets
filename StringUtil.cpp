#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <utils/Log.h>
#include <stdlib.h>
#include <string>
#include <algorithm>


#include "StringUtil.h"


using namespace android;

bool StringUtil::StringIsEmpty(std::string string)
{
    if(string.empty() || string.length() == 0)
    { return true; }
    else
    { return false; }
}


void StringUtil::StringSplit(std::vector<std::string> &strings, std::string string, const char* separator)
{
    ssize_t curIndex = 0;
    ssize_t prevCurIndex;

    while(curIndex >= 0 && (size_t) curIndex < string.size()) {
        prevCurIndex = curIndex;
        curIndex = string.find(separator, curIndex);

        if(curIndex >= 0) {
            strings.push_back(string.substr(prevCurIndex, curIndex - prevCurIndex));
            curIndex += strlen(separator);
        } else {
            strings.push_back(string.substr(prevCurIndex, string.size() - prevCurIndex));
        }
    }
}

bool StringUtil::StringStartsWith(std::string string, const char* prefix)
{
    size_t prefixSize = strlen(prefix);

    if(string.size() >= prefixSize) {
        return strncmp(string.c_str(), prefix, prefixSize) == 0;
    } else {
        return false;
    }
}

bool StringUtil::StringEndsWith(std::string string, const char* suffix)
{
    size_t suffixSize = strlen(suffix);

    if(string.size() >= suffixSize) {
        return strncmp(string.c_str() + string.size() - suffixSize, suffix, suffixSize) == 0;
    } else {
        return false;
    }
}

void StringUtil::StringFindValue(std::string string, std::string &value, std::string index)
{
    int indexBegin = string.find(index) + index.length();

    if(indexBegin != (int)std::string::npos) {
        int indexEnd = string.find(" ", indexBegin);

        if(indexEnd == (int)std::string::npos) {
            indexEnd = string.find("\n", indexBegin);
        }

        if(indexEnd == (int)std::string::npos) {
            indexEnd = string.length();
        }

        value = string.substr(indexBegin, indexEnd - indexBegin);
    }
}


