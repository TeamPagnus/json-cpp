#include <string>
#include <map>

struct json {
    const std::string tete = "42";
    std::string ttt;

    std::string operator [](std::string) const
    {
        return tete;
    }

    std::string & operator [](std::string key)
    {
        return ttt;
    }

    static json from_string(std::string raw)
    {
        auto nnn = json();
        nnn.ttt = "value";
        return nnn;
    }
};