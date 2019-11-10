//
// Created by d1m0000n on 07.11.2019.
//
#pragma once
#ifndef JIT_COMPILE_HELPFUL_FUNCTIONS_H
#define JIT_COMPILE_HELPFUL_FUNCTIONS_H

#endif //JIT_COMPILE_HELPFUL_FUNCTIONS_H
using std::string;

bool is_operator(const string& str)
{
    if (str.size() == 1) {
        return str[0] == '*' || str[0] == '+' || str[0] == '-' ||
               str[0] == '#' || str[0] == '$';
    } else
        return false;
}

int get_priority(const string& p)
{
    if (p == "+" || p == "-")
        return 1;
    if (p == "*")
        return 2;
    if (p == "#" || p == "$")
        return 3;
}

bool Is_const(const string& val)
{
    bool ans = 1;
    for (int i = 0; i < val.size(); i++) {
        if (val[i] < '0' || val[i] > '9')
            ans = 0;
    }
    return ans;
}

int string_to_int(const string& str, int sign)
{
    int result = std::stoi(str);
    return result * sign;
}