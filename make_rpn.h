//
// Created by d1m0000n on 07.11.2019.
//
#pragma once
#ifndef JIT_COMPILE_MAKE_RPN_H
#define JIT_COMPILE_MAKE_RPN_H

#endif //JIT_COMPILE_MAKE_RPN_H
#include "make_map.h"
#include <stack>
#include <vector>
#include "helpful_functions.h"

using std::vector;
using std::stack;

vector<string> make_rpn(string expression)
{

    string exp = std::move(expression);
    vector<string> result;

    unordered_map<string, int> variables = make_map(exp);
    stack<string> operations;

    for (int i = 0; i < exp.size(); i++) {
        char symbol = exp[i];

        if (symbol == '(') {
            operations.push("(");
            continue;
        }

        if (symbol == ')') {
            while (operations.top() != "(") {
                result.push_back(operations.top());
                operations.pop();
            }
            operations.pop();
            if (!operations.empty()) {
                string name = operations.top();
                if (variables[name] == 1) {
                    result.push_back(name);
                    operations.pop();
                }
            }
            continue;
        }

        if (is_good_symbol(exp[i])) {
            string name = get_name(i, exp);
            if (variables.find(name) != variables.end()) {
                if (variables[name] == 1)
                    operations.push(name);
                else
                    result.push_back(name);
            }
            continue;
        }

        if (symbol == ',') {
            while (operations.top() != "(") {
                result.push_back(operations.top());
                operations.pop();
            }
            continue;
        }

        if (!operations.empty()) {
            while (get_priority(operations.top()) >=
                   get_priority(string(1, symbol)) &&
                   operations.top() != "(") {
                result.push_back(operations.top());
                operations.pop();
                if (operations.empty())
                    break;
            }
        }
        operations.push(string(1, symbol));
    }

    while (!operations.empty()) {
        result.push_back(operations.top());
        operations.pop();
    }

    return result;
}