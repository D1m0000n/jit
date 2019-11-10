//
// Created by d1m0000n on 07.11.2019.
//
#pragma once
#ifndef JIT_COMPILE_LOAD_REFERENCES_H
#define JIT_COMPILE_LOAD_REFERENCES_H

#endif //JIT_COMPILE_LOAD_REFERENCES_H
#include "symbol_t.h"
using std::unordered_map;


unordered_map<string, void*> load_references(const symbol_t* externs)
{
    int ind = 0;
    unordered_map<string, void*> vars;
    while (externs[ind].pointer != nullptr) {
        string result;
        char p = '\n';
        int counter = 0;
        while (true) {
            p = externs[ind].name[counter++];
            if (p == '\0')
                break;
            result += p;
        }
        vars[result] = externs[ind++].pointer;
    }
    return vars;
}