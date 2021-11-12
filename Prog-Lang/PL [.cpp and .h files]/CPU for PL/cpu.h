#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

#define _CRT_SECURE_NO_WARNINGS

#include "cpu_info.h"
#include "stack.h"
#include "Commands.h"

typedef int ERROR_STATE;

auto get_byte(int digit, int number_of_bit) -> bool;

//auto get_bytecode(FILE* text, Bytecode* byte_struct) -> void;

//auto CPU(Bytecode* byte_struct, Stack* stk, Stack* stk_call) -> void;

//auto determine_status(Bytecode* byte_struct, Stack* stk) -> void;

//auto bytecode_destruct(Bytecode* byte_struct) -> void;

auto print_for_user(Stack* stk) -> void;

auto ignore_spaces(char** buffer) -> void;

auto print_good(FILE* error) -> void;

auto print_error(FILE* error, int error_bit) -> void;

auto get_number(char** buffer) -> double;

auto set_time(struct tm *time) -> char*;

auto define_date() -> char*;

auto is_equal(double a, double b) -> bool;

//auto get_byte(int digit, int number_of_bit) -> bool;

//auto cmd_push_exe(int command, int i, Stack* stk, Rix *rix_struct, Bytecode* byte_struct, char *OP) -> ERROR_STATE;

//auto cmd_pop_exe(int command, int i, Stack* stk, Rix *rix_struct, Bytecode* byte_struct, char *OP) -> ERROR_STATE;

//auto cmd_compair_exe(int command, Stack* stk, Bytecode* byte_struct, int *i) -> ERROR_STATE;

#endif // CPU_H_INCLUDED
