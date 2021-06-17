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

    // nested json
    test = process("{'key':{'nested-key':'nested-value'}}");
    assert(test["key"]["nested-key"] == "nested-value");
    test = process(" { 'key' : { 'nested-key'  : 'nested-value' } } ");
    assert(test["key"]["nested-key"] == "nested-value");
    test = process("{'a':{'o':{'e':'u'}}}");
    assert(test["a"]["o"]["e"] == "u");
    test = process("{'a':{'k':{'u':'a{a}a'}}}");
    assert(test["a"]["k"]["u"] == "a{a}a");

    // object with some key-values
    test = process("{'key1':'value1','key2':'value2'}");
    assert(test["key1"] == "value1");
    assert(test["key2"] == "value2");

    test = process("{'key1':'value1','key2':{'a':'k'}}");
    assert(test["key1"] == "value1");
    assert(test["key2"]["a"] == "k");

    test = process("{'a':{'1':'h','2':'e'},'b':{'1':'l','2':'l'},'greet!':'o'}");
    assert(test["a"]["1"] == "h");
    assert(test["a"]["2"] == "e");
    assert(test["b"]["1"] == "l");
    assert(test["b"]["2"] == "l");
    assert(test["greet!"] == "o");

    // object with arrays
    test = process("{'array':['a','o']}");
    assert(test["array"][0] == "a");
    assert(test["array"][1] == "o");

    test = process("{'uppercase':['{'a':'A'}}','{'o':'O'},'{'e':'E'}']}");
    assert(test["uppercase"][0]["a"] == "A");
    assert(test["uppercase"][1]["o"] == "O");
    assert(test["uppercase"][2]["e"] == "E");

    // numbers in json!

    test = process("{'number':23}");
    assert(test["number"] == 23);

    test = process("{'number':-23}");
    assert(test["number"] == -23);

    test = process("{'number':0}");
    assert(test["number"] == 0);

    test = process("{'s':0.1,'b':5.1,'n':'-23.2'}");
    assert(test["s"] < test["b"]);
    assert(test["n"] < test["s"]);
    assert(test["n"] < test["b"]);

    test = process("{'a':0.1e10,'b':51e3}");
    assert(test["a"] < test["b"]);

    // boolean & null values

    test = process("{'a':true}");
    assert(test["a"]);

    test = process("{'a':false}");
    assert(!test["a"]);

    test = process("{'e':null}");
    assert(test["e"] == nullptr);

    // some extra whitespaces

    test = process("\n{\n'key'\n:\n'value'\n}\n");
    assert(test["key"] == "value");
    test = process("\t{\t'key'\t:\t'value'\t}\t");
    assert(test["key"] == "value");
    test = process("\r{\r'key'\r:\r'value'\r}\r");
    assert(test["key"] == "value");

    test = process("  \r\n  {  \n   \r\r\r\r\r\t\t\t\t\t\n\n\n\n\n 'e'  :  \t\n 'hello' \n\t   }    \t\t   \t\n");
    assert(test["e"] == "hello");

    return 0;
}