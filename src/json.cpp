#include "json.h"

#include "parser.h"

#include <cassert>

json json::operator [](std::string key) const
{
    assert(type == json_t::OBJECT);
    auto it = keyValueMap.find(key);
    if (it != keyValueMap.end())
    {
        return it->second;
    }
    assert(0); // key not found
}

bool json::operator== (std::string comparision) const
{
    assert(type == json_t::STRING);
    return comparision == str;
}

json json::from_string(std::string raw)
{
    parser p = parser(raw);
    return p.consume_object();
}
