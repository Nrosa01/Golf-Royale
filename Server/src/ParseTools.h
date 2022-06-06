#ifndef PARSE_TOOLS_H
#define PARSE_TOOLS_H

#include <iostream>
#include <algorithm>

namespace ParseTool
{

    inline bool is_number(const std::string &s)
    {
        return !s.empty() && std::find_if(s.begin(),
                                          s.end(), [](char c)
                                          { return !std::isdigit(c); }) == s.end();
    }

    inline bool is_address(const std::string &address)
    {
        return address.find_first_not_of("0123456789.") == std::string::npos;
    }

}
#endif