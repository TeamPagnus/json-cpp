#include "parser.h"

#include <cassert>

#define OBJECT_START '{'
#define OBJECT_MIDDLE ':'
#define OBJECT_END '}'
#define STRING_START_END '"'

typedef std::string::iterator str_it;

void parser::next()
{
    it++;
    i++;
}

parser::parser(std::string&str) : raw(str)
{
    it = raw.begin();
    i = 0;
}

bool parser::is_whitespace()
{
    return *it == ' ';
}

json_t parser::get_type()
{
    if (*it == STRING_START_END)
    {
        return STRING;
    } else if (*it == OBJECT_START)
    {
        return OBJECT;
    }
    assert(0); // BAD JSON
}

void parser::consume_whitespace()
{
    for (;is_whitespace() && it != raw.end(); next());
}

std::string parser::parse_string()
{
    consume_whitespace();
    assert(*it == STRING_START_END);
    next();
    str_it start = it;
    for (;*it != STRING_START_END && it != raw.end(); next());
    assert(it != raw.end());
    assert(*it == STRING_START_END);
    auto string_end = it;
    next();
    return std::string(start, string_end);
}

void parser::consume_object_start()
{
    consume_whitespace();
    assert(*it == OBJECT_START);
    next();
}

void parser::consume_object_middle()
{
    consume_whitespace();
    assert(*it == OBJECT_MIDDLE);
    next();
    consume_whitespace();
}

void parser::consume_object_end()
{
    consume_whitespace();
    assert(*it == OBJECT_END);
    next();
}

json parser::consume_object()
{
    consume_object_start();
    std::string key = parse_string();
    consume_object_middle();
    json value;
    if (get_type() == STRING)
    {
        value.type = STRING;
        value.str = parse_string();
    } else if (get_type() == OBJECT) {
        value.type = OBJECT;
        value = consume_object();
    }
    consume_object_end();

    json result;
    result.type = OBJECT;
    result.keyValueMap[key] = value;
    return result;
}
