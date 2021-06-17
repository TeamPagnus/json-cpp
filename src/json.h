#ifndef JSON_H
#define JSON_H

#include <string>
#include <map>

enum json_t {
    OBJECT,
    STRING
};

class json
{
public:
    static json from_string(std::string);
    json operator[](std::string) const;
    bool operator==(std::string) const;

    std::map<std::string,json> keyValueMap;
    std::string str;
    json_t type;
};

#endif // JSON_H