#include "json-cpp.h"

#include <iostream>
#include <string>

int main()
{
    {
        auto first = json::from_string("{\"key\":\"value\"}");
        if (first["key"] != "value") {std::cout<<"ERROR " << first["key"] << " value"<<std::endl;}
    }
    {
        const auto first = json::from_string("{\"xx\":\"value\"}");
        if (first["xx"] != "value") {std::cout<<"ERROR " << first["key"] << " value"<<std::endl;}    }
    {
        auto first = json::from_string("{\"key\":\"value3\"}");
        if (first["key"] != "value3") {std::cout<<"ERROR " << first["key"] << " value3"<<std::endl;}
    }
    {
        const auto first = json::from_string("{\"ee\":\"value3\"}");
        if (first["ee"] != "value3") {std::cout<<"ERROR " << first["key"] << " value3"<<std::endl;}
    }
    return 0;
}
