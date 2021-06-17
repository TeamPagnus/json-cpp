#ifndef PARSER_H
#define PARSER_H

#include "json.h"

#include <string>

class parser
{
public:
    parser(std::string&);
    bool is_whitespace();
    void consume_whitespace();
    std::string parse_string();
    void consume_object_start();
    void consume_object_middle();
    void consume_object_end();
    json consume_object();
private:
    std::string raw;
    std::string::iterator it;
    json_t get_type();
    uint64_t i;
    void next();
};

#endif // PARSER_H
