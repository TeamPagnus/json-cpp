#include <string>
#include <map>

class json
{
public:
    static json from_string(std::string);
    static json empty();
    std::string operator [](std::string) const;
    std::string & operator [](std::string);
private:
    std::map<std::string,std::string> keyValueMap;
};