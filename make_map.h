#pragma once
#include <unordered_map>
#include <string>
//
// Created by d1m0000n on 07.11.2019.
//

#ifndef JIT_COMPILE_MAKE_MAP_H
#define JIT_COMPILE_MAKE_MAP_H

#endif //JIT_COMPILE_MAKE_MAP_H
using std::unordered_map;
using std::string;

bool is_good_symbol(char p) {
    bool ans = false;
    if (p == 36)
        ans = true;
    if (p == 95)
        ans = true;
    if (p >= 48 && p <= 57)
        ans = true;
    if (p >= 65 && p <= 90)
        ans = true;
    if (p >= 97 && p <= 122)
        ans = true;
    return ans;
}

string get_name(int &counter, const string &exp) {
    string name;
    bool flag = false;
    while (!flag) {
        if (counter == exp.size())
            break;
        if (is_good_symbol(exp[counter]))
            name += exp[counter];
        else {
            flag = true;
            --counter;
        }
        ++counter;
    }
    --counter;
    return name;
}

unordered_map<string, int> make_map(const string &exp) {
    unordered_map<string, int> result;
    for (int i = 0; i < exp.size(); i++) {
        char p = exp[i];
        if (is_good_symbol(p)) {
            string name = get_name(i, exp);
            if (i != exp.size() - 1) {
                exp[i + 1] == '(' ? result[name] = 1 : result[name] = 0;
            } else {
                result[name] = 0;
            }
        }
    }
    return result;
}

struct info {
    int skobki_balance;
    int commas;
    string str;
    bool flag = false;

    info(int a, int b, string kek) : skobki_balance(a), commas(b), str(kek) {
    }
};
