#include "json.h"

#include <cassert>

#define OBJECT_START '{'
#define OBJECT_MIDDLE ':'
#define OBJECT_END '}'
#define STRING_START_END '"'

typedef std::string::iterator str_it;

bool is_whitespace(const str_it &it)
{
    return *it == ' ';
}

void consume_whitespace(const std::string raw, str_it &it)
{
    for (;is_whitespace(it) && it != raw.end(); it++);
}

std::string parse_string(const std::string raw, str_it &it)
{
    consume_whitespace(raw, it);
    assert(*it == STRING_START_END);
    it++;
    str_it start = it;
    for (;*it != STRING_START_END && it != raw.end(); it++);
    assert(it != raw.end());
    assert(*it == STRING_START_END);
    return std::string(start, it++);
}

void consume_object_start(const std::string raw, str_it &it)
{
    consume_whitespace(raw, it);
    assert(*it == OBJECT_START);
    it++;
}

void consume_object_middle(const std::string raw, str_it &it)
{
    consume_whitespace(raw, it);
    assert(*it == OBJECT_MIDDLE);
    it++;
}

std::string json::operator [](std::string key) const
{
    auto it = keyValueMap.find(key);
    if (it != keyValueMap.end())
    {
        return it->second;
    }
    assert(0); // key not found
}

std::string & json::operator [](std::string key)
{
    auto it = keyValueMap.find(key);
    if (it != keyValueMap.end())
    {
        return it->second;
    }
    assert(0); // key not found
}

json json::from_string(std::string raw)
{
    auto nnn = json();

    str_it it = raw.begin();
    consume_object_start(raw, it);
    std::string key = parse_string(raw, it);
    consume_object_middle(raw, it);
    std::string value = parse_string(raw, it);
    nnn.keyValueMap[key] = value;

    return nnn;
}