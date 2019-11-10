//
// Created by d1m0000n on 07.11.2019.
//
#pragma once
#ifndef JIT_COMPILE_MAKE_UNO_H
#define JIT_COMPILE_MAKE_UNO_H

#endif //JIT_COMPILE_MAKE_UNP_H
#include "helpful_functions.h"

void make_uno(string &exp) {
    bool flag = 1;
    for (int i = 0; i < exp.size(); i++) {
        if (flag && exp[i] == '-') {
            exp[i] = '#';
            continue;
        }
        if (flag && exp[i] == '+') {
            exp[i] = '$';
            continue;
        }

        if (is_operator(string(1, exp[i])) || exp[i] == '(' || exp[i] == ',')
            flag = 1;
        else
            flag = 0;
    }
}