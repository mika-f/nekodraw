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

static inline std::vector<std::string> split(std::string str, std::string separator)
{
    if (separator.empty())
    {
        return std::vector{str};
    }

    std::vector<std::string> result;
    std::string a = str + separator;
    const auto l1 = a.length();
    const auto l2 = separator.length();

    std::string::size_type pos = 0, prev = 0;

    for (; pos < l1 && (pos = a.find(separator, pos)) != std::string::npos; prev = (pos += l2))
    {
        result.emplace_back(a, prev, pos - prev);
    }

    return result;
}
