//
// Created by d1m0000n on 07.11.2019.
//
#pragma once
#ifndef JIT_COMPILE_ASSEMBLY_COMMANDS_H
#define JIT_COMPILE_ASSEMBLY_COMMANDS_H

#endif //JIT_COMPILE_ASSEMBLY_COMMANDS_H
#include "helpful_functions.h"
using std::vector;
using std::string;

enum {
    bx = 0x12fff10,
    r0 = 0,
    r1 = 1,
    r2 = 2,
    r3 = 3,
    r4 = 4,
    sp = 13,
    lr = 14,
    sub = 2,
    add = 4,
    AL = 14,
    mov = 13,
    pc = 15,
    blx = 0x12fff30
};

void const_operations(
        int OpCode,
        int Rn,
        int Rd,
        string val,
        int sign,
        int* answer,
        int& index)
{
    int result = 0;
    int value = string_to_int(val, sign);
    if (value < 0 && OpCode == sub) {
        return const_operations(add, Rn, Rd, val, 1, answer, index);
    }
    if (value < 0 && OpCode == add) {
        return const_operations(sub, Rn, Rd, val, 1, answer, index);
    }
    result |= AL << 28;
    result |= 1 << 25;
    result |= OpCode << 21;
    result |= Rn << 16;
    result |= Rd << 12;
    int Rotate = 0;
    vector<int> ans(4);
    ans[0] = result;
    for (int i = 0; i < 4; i++) {
        ans[i] = result;
        int pattern = 255 << ((32 - i * 8) % 32);
        ans[i] |= (pattern & value) >> ((32 - i * 8) % 32);
        ans[i] |= Rotate << 8;
        Rotate += 4;
    }
    for (int i = 0; i < 4; i++) {
        answer[index++] = ans[i];
    }
}

void MOV_const(int Rd, string val, int sign, int* answer, int& index)
{
    vector<int> ans;
    const_operations(mov, Rd, Rd, "0", 1, answer, index);
    int value = string_to_int(val, sign);
    if (value < 0) {
        const_operations(sub, Rd, Rd, val, 1, answer, index);
    } else {
        const_operations(add, Rd, Rd, val, 1, answer, index);
    }
}

void BX(int Rn, int* answer, int& index)
{
    int result = Rn;
    result |= bx;
    result |= AL << 28;
    answer[index++] = result;
}

void BLX(int Rn, int* answer, int& index)
{
    int result = Rn;
    result |= blx;
    result |= AL << 28;
    answer[index++] = result;
}

void non_const(int OpCode, int Rn, int Rd, int Rm, int* answer, int& index)
{
    int result = 0;
    result |= AL << 28;
    result |= OpCode << 21;
    result |= Rn << 16;
    result |= Rd << 12;
    result |= Rm;
    answer[index++] = result;
}

void MOV(int Rd, int Rm, int* answer, int& index)
{
    non_const(mov, 0, Rd, Rm, answer, index);
}

void LDR(int Rn, int Rd, int* answer, int& index)
{
    int result = 0;
    result |= AL << 28;
    result |= 1 << 26;
    result |= 1 << 20;
    result |= Rn << 16;
    result |= Rd << 12;
    answer[index++] = result;
}

void STR(int Rn, int Rd, int* answer, int& index)
{
    int result = 0;
    result |= AL << 28;
    result |= 1 << 26;
    result |= Rn << 16;
    result |= Rd << 12;
    answer[index++] = result;
}

void MUL(int Rd, int Rs, int Rm, int* answer, int& index)
{
    int result = 0;
    result |= AL << 28;
    result |= Rd << 16;
    result |= Rs << 8;
    result |= 1 << 7;
    result |= 1 << 4;
    result |= Rm;
    answer[index++] = result;
}

void PUSH(int Rd, int* answer, int& index)
{
    const_operations(sub, sp, sp, "4", 1, answer, index);
    STR(sp, Rd, answer, index);
}

void POP(int Rd, int* answer, int& index)
{
    LDR(sp, Rd, answer, index);
    const_operations(add, sp, sp, "4", 1, answer, index);
}