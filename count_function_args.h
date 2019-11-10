//
// Created by d1m0000n on 07.11.2019.
//
#pragma once
#ifndef JIT_COMPILE_COUNT_FUNCTION_ARGS_H
#define JIT_COMPILE_COUNT_FUNCTION_ARGS_H

#endif //JIT_COMPILE_COUNT_FUNCTION_ARGS_H

#include "make_map.h"
#include <vector>

using std::vector;

unordered_map<string, int> count_function_args(const string &exp) {
    unordered_map<string, int> result;
    unordered_map<string, int> functions = make_map(exp);
    vector <info> args;
    for (int i = 0; i < exp.size(); i++) {
        char symbol = exp[i];
        string name;
        name.push_back(symbol);
        if (is_good_symbol(symbol)) {
            name = get_name(i, exp);
            if (args.size() != 0)
                args.back().flag = true;
        } else {
            if (args.size() == 0)
                continue;
            if (name == ",")
                args.back().commas++;
            if (name == "(")
                args.back().skobki_balance++;
            if (name == ")")
                args.back().skobki_balance--;
            if (args.back().skobki_balance == 0 && args.back().flag) {
                result[args.back().str] = args.back().commas + 1;
                args.pop_back();
                continue;
            }
            if (args.back().skobki_balance == 0 && !args.back().flag) {
                result[args.back().str] = 0;
                args.pop_back();
            }
        }
        if (functions[name] == 1) {
            args.emplace_back(0, 0, name);
        }
    }
    return result;
}