//
// Created by d1m0000n on 07.11.2019.
//
#pragma once
#ifndef JIT_COMPILE_ASSEMBLY_CODE_GENERATION_H
#define JIT_COMPILE_ASSEMBLY_CODE_GENERATION_H

#endif //JIT_COMPILE_ASSEMBLY_CODE_GENERATION_H
#include <unordered_map>
#include <vector>
#include "assembly_commands.h"
#include "make_map.h"
#include "make_uno.h"
#include "load_references.h"
#include "count_function_args.h"
#include "symbol_t.h"
#include "make_rpn.h"


using std::unordered_map;
using std::vector;

void assembly_code_generation(
        const char* expression,
        const symbol_t* externs,
        void* out_buffer)
{

    string result;
    char p = '\n';
    int ind = 0;
    while (true) {
        p = expression[ind++];
        if (p == '\0')
            break;
        if (p != ' ')
            result += p;
    }

    unordered_map<string, int> function_names = make_map(result);
    make_uno(result);
    vector<string> rpn = make_rpn(result);
    unordered_map<string, int> function_args = count_function_args(result);
    unordered_map<string, void*> vars_names = load_references(externs);

    int* answer = static_cast<int*>(out_buffer);

    int index = 0;
    PUSH(lr, answer, index);
    PUSH(r4, answer, index);

    for (int i = 0; i < rpn.size(); i++) {
        string token = rpn[i];
        if (is_operator(token)) {
            if (token[0] == '$')
                continue;
            if (token[0] == '#') {
                LDR(sp, r0, answer, index);
                MOV_const(r1, "1", -1, answer, index);
                MUL(r0, r0, r1, answer, index);
                STR(sp, r0, answer, index);
            }
            if (token[0] == '-') {
                POP(r1, answer, index);
                POP(r0, answer, index);
                non_const(sub, r0, r0, r1, answer, index);
                PUSH(r0, answer, index);
            }
            if (token[0] == '+') {
                POP(r0, answer, index);
                POP(r1, answer, index);
                non_const(add, r0, r0, r1, answer, index);
                PUSH(r0, answer, index);
            }
            if (token[0] == '*') {
                POP(r0, answer, index);
                POP(r1, answer, index);
                MUL(r0, r0, r1, answer, index);
                PUSH(r0, answer, index);
            }
            continue;
        }

        if (function_names[token]) {
            int args_cnt = function_args[token];
            for (int j = args_cnt - 1; j >= 0; j--) {
                POP(j, answer, index);
            }
            MOV_const(
                    r4,
                    std::to_string((int)((long long)vars_names[token])),
                    1,
                    answer,
                    index);
            BLX(r4, answer, index);
            PUSH(r0, answer, index);
            continue;
        }

        if (Is_const(token)) {
            MOV_const(r0, token, 1, answer, index);
            PUSH(r0, answer, index);
            continue;
        }

        MOV_const(
                r1,
                std::to_string((int)((long long)vars_names[token])),
                1,
                answer,
                index);
        LDR(r1, r0, answer, index);
        PUSH(r0, answer, index);
    }

    POP(r0, answer, index);
    POP(r4, answer, index);
    POP(lr, answer, index);
    BX(lr, answer, index);
}