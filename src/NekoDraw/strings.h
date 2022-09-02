#pragma once

#include "pch.h"

static inline void ltrim(std::string& s)
{
    s.erase(s.begin(), std::ranges::find_if(s, [](unsigned char ch)
    {
        return !std::isspace(ch);
    }));
}

static inline void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }).base(), s.end());
}

static inline void trim(std::string& s)
{
    ltrim(s);
    rtrim(s);
}

static inline std::string trim_c(std::string s)
{
    trim(s);
    return s;
}
