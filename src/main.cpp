#include "json.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <cassert>

inline json process(std::string s)
{
    std::replace(s.begin(), s.end(), '\'', '\"');
    return json::from_string(s);
}

int main()
{
    json test;

    // some simple json tests
    test = process("{'key':'value'}");
    assert(test["key"] == "value");
    test = process("{'aka':'value'}");
    assert(test["aka"] == "value");
    test = process("{'key':'eee'}");
    assert(test["key"] == "eee");

    // json with spaces
    test = process(" { 'key' : 'value' } ");
    assert(test["key"] == "value");
    test = process("  {  'key'  :  'value'  }  ");
    assert(test["key"] == "value");
    test = process("{          'key'          :     'value'    }     ");
    assert(test["key"] == "value");
    test = process(" { '  key  '   : '  value  ' } ");
    assert(test["  key  "] == "  value  ");

    return 0;
}