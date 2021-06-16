#include "json-cpp.h"

#include <iostream>
#include <string>

int main()
{
    {
        auto first = json::from_string("{\"key\":\"value\"}");
        if (first["key"] != "value") {std::cout<<"ERROR"<<std::endl;}
    }
    return 0;
}
