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
    json operator[](size_t) const;
    bool operator==(std::string) const;
    bool operator==(int) const;
    bool operator<(json) const;
    explicit operator bool()const;

    std::map<std::string,json> keyValueMap;
    std::string str;
    json_t type;
};

#endif // JSON_H