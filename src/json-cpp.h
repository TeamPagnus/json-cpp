#include <string>
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define OBJECT_START '{'
#define KEY_VALUE_SEPARATOR ':'
#define OBJECT_END '}'
#define STRING_START_END '"'



std::string::iterator parse_string(const std::string raw, const std::string::iterator it_from)
{
    for (std::string::iterator it_to = it_from; it_to != raw.end(); it_to++)
    {
        if (*it_to == STRING_START_END){
            return it_to;
        }
    }
    throw "character not found";
}

std::vector<std::string> split(std::string teste, char spliter)
{
    std::stringstream test(teste);
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(test, segment, spliter))
    {
    seglist.push_back(segment);
    }

    return seglist;
}


struct json {
    std::map<std::string,std::string> keyValueMap;

    std::string operator [](std::string key) const
    {
        auto it = keyValueMap.find(key);
        if (it != keyValueMap.end())
        {
            return it->second;
        }
        throw "key not found";
    }

    std::string & operator [](std::string key)
    {
        auto it = keyValueMap.find(key);
        if (it != keyValueMap.end())
        {
            return it->second;
        }
        throw "key not found";
    }

    static json from_string(std::string raw)
    {
        auto nnn = json();
        if (*raw.begin() == OBJECT_START)
        {
            auto st = raw.begin();
            st++;
            st++;
            auto ed = parse_string(raw, st);
            auto key = std::string(st, ed);
            ed++; // avoid :
            ed++;// avoid "
            ed++;// start with the string
            auto eded = parse_string(raw, ed);
            auto value = std::string(ed, eded);
            nnn.keyValueMap[key] = value;
        }
        return nnn;
    }
};