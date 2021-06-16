#include "json.h"

#include <string>
#include <iostream>

int main()
{
    json test = json::from_string("{\"key\":\"value\"}");
    if (test["key"] == "value")
    {
        std::cout << "OK" << std::endl;
    }
    return 0;
}