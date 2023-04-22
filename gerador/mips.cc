#include <iostream>

#include "mips.hh"

static const char* const register_labels[] = {
    "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
};

static const char* const op_labels[] = {
    "add", "sub", "addi", "addu", "subu", "addiu", "mul", "mult", "div", "and", "or", "andi", "ori",
    "sllv", "srl", "lw", "sw", "lui", "mfhi", "mflo", "beq", "bne", "slt", "slti", "j", "jr", "jal", 
    "", "", "la", "nor", "sltu", "xori", "srav", "xor"
};

static const char* const printf_snippet = "printf:\n" \
                                    "	addi	$sp, $sp, -4\n" \
                                    "	sw	$a3, ($sp)\n" \
                                    "	addi	$sp, $sp, -4\n" \
                                    "	sw	$a2, ($sp)\n" \
                                    "	addi	$sp, $sp, -4\n" \
                                    "	sw	$a1, ($sp)\n" \
                                    "	add	$t9, $zero, $sp\n" \
                                    "	add	$t0, $zero, $a0\n" \
                                    "	j	teste_end___\n" \
                                    "printf_loop___:\n" \
                                    "	addi	$t1, $zero, '%'\n" \
                                    "	beq	$a0, $t1, print_arg___\n" \
                                    "	addi	$v0, $zero, 11\n" \
                                    "	syscall\n" \
                                    "	addi 	$t0, $t0, 1	\n" \
                                    "teste_end___:\n" \
                                    "	lb	$a0, ($t0)\n" \
                                    "	bne	$a0, $zero, printf_loop___\n" \
                                    "   add $sp, $sp, 12\n"\
                                    "	jr	$ra\n" \
                                    "print_arg___:\n" \
                                    "	addi	$t0, $t0, 1\n" \
                                    "	lb	$a0, ($t0)\n" \
                                    "	addi	$t1, $zero, 'c'\n" \
                                    "	bne	$a0, $t1, d___\n" \
                                    "	lw	$a0, ($t9)\n" \
                                    "	addi	$t9, $t9, 4\n" \
                                    "	addi	$v0, $zero, 11\n" \
                                    "	syscall\n" \
                                    "	addi	$t0, $t0, 1\n" \
                                    "	j 	teste_end___\n" \
                                    "d___:	addi	$t1, $zero, 'd'\n" \
                                    "	bne	$a0, $t1, s___\n" \
                                    "	lw	$a0, ($t9)\n" \
                                    "	addi	$t9, $t9, 4\n" \
                                    "	addi	$v0, $zero, 1\n" \
                                    "	syscall\n" \
                                    "	addi	$t0, $t0, 1\n" \
                                    "	j 	teste_end___\n" \
                                    "s___:	addi	$t1, $zero, 's'\n" \
                                    "	bne	$a0, $t1, l___\n" \
                                    "	lw	$a0, ($t9)\n" \
                                    "	addi	$t9, $t9, 4\n" \
                                    "	addi	$v0, $zero, 4\n" \
                                    "	syscall\n" \
                                    "	addi	$t0, $t0, 1\n" \
                                    "	j 	teste_end___\n" \
                                    "l___:\n" \
                                    "	addi	$v0, $zero, 11\n" \
                                    "	syscall\n" \
                                    "	addi	$t0, $t0, 1\n" \
                                    "	j	teste_end___";

gerador::registers& gerador::operator++(gerador::registers& r) {
    return r = static_cast<gerador::registers>(static_cast<int>(r) + 1);
}

gerador::registers gerador::operator++(gerador::registers& r, int) {
    gerador::registers s = r;
    r = static_cast<gerador::registers>(static_cast<int>(r) + 1);

    return s;
}

gerador::registers& gerador::operator--(gerador::registers& r) {
    return r = static_cast<gerador::registers>(static_cast<int>(r) - 1);
}

gerador::registers gerador::operator--(gerador::registers& r, int) {
    gerador::registers s = r;
    r = static_cast<gerador::registers>(static_cast<int>(r) - 1);

    return s;
}

gerador::instruction_set::instruction_set() : current_offset(0), current_var(registers::S0), 
        current_param(registers::A0), printf(false) { 
    context_stack.push_back(context()); 
}

gerador::instruction_set::~instruction_set() {
    for(instruction* i : text) {
        delete i;
    }
}

gerador::symbol* gerador::instruction_set::get_symbol(const std::string& label) {
    for(auto& c : context_stack) {
        auto it = c.symbols.find(label);
        if(it != c.symbols.end())
            return &it->second;
    }

    return nullptr;
}

gerador::registers gerador::instruction_set::get_current_var() {
    return current_var;
}

gerador::registers gerador::instruction_set::get_current_param() {
    return current_param;
}

gerador::registers gerador::instruction_set::map_register(registers start) {
    while(context_stack.back().registers[start])
        ++start;

    context_stack.back().registers[start] = true;
    return start;
}

bool* gerador::instruction_set::get_registers() {
    return context_stack.back().registers;
}

void gerador::instruction_set::set_register(registers reg, bool status) {
    context_stack.back().registers[reg] = status;
}

void gerador::instruction_set::set_current_label(const std::string& label) {
    current_label = label;
}

const std::string& gerador::instruction_set::get_current_label() {
    return current_label;
}

// void gerador::instruction_set::clear_temp_reg() {
//     for(registers r = T0; r <= T7; r++)
//         context_stack.back().registers[r] = false;

//     for(registers r = T8; r <= T9; r++) {
//         context_stack.back().registers[r] = false;
//     }
// }

void gerador::instruction_set::use_printf() {
    printf = true;
}

int gerador::instruction_set::get_string_offset(const std::string& str) {
    int size = 0, i = 0;

    while(i <= str.length()) {
        if(str[i] == '\\')
            ++i;
        ++size;
        ++i;
    }
}

int gerador::instruction_set::offset() {
    return current_offset;
}

void gerador::instruction_set::add_data(const std::string& label, 
        gerador::global_type t, const std::string& value) {
    data.insert({label, {value, t, 0, current_offset}});
    current_offset += value.size() - 1;
}

void gerador::instruction_set::add_data(const std::string& label, 
        gerador::global_type t, int size) {
    data.insert({label, {"0", t, size, current_offset}});
    current_offset += size;
}

void gerador::instruction_set::add_text(opcode op, registers r1, registers r2, registers r3) {
    text.push_back(new three_reg(op, r1, r2, r3));
}

void gerador::instruction_set::add_text(opcode op, registers r1, registers r2, int immediate) {
    text.push_back(new two_reg_immediate(op, r1, r2, immediate));
}

void gerador::instruction_set::add_text(opcode op, const std::string& address) {
    text.push_back(new one_label(op, address));
}

void gerador::instruction_set::add_text(opcode op, registers r1, 
        registers r2, const std::string& address) {
    text.push_back(new two_reg_label(op, r1, r2, address));
}

void gerador::instruction_set::add_text(opcode op, registers r1) {
    text.push_back(new one_reg(op, r1));
}

void gerador::instruction_set::add_text(opcode op, registers r1, registers r2) {
    text.push_back(new two_reg(op, r1, r2));
}

void gerador::instruction_set::add_text(opcode op, registers r1, const std::string& address) {
    text.push_back(new one_reg_address(op, r1, address));
}

void gerador::instruction_set::add_label(const std::string& label) {
    text.push_back(new one_label(opcode::LABEL, label));
}

void gerador::instruction_set::add_variable(const std::string& name, 
        var_types t) {
    if(current_param <= gerador::registers::S7) {
        context_stack.back().registers[current_var] = true;
        context_stack.back().symbols.insert({name, symbol(ast_node_types::VAR, t, current_var++)});
    }
}

void gerador::instruction_set::add_global_var(const std::string& name, 
        var_types t, int v) {
    // std::cerr << "Global var: " << name << "Type" << t << std::endl;
    context_stack.back().symbols.insert({name, symbol(ast_node_types::GLOBAL_VAR, t, v)});
    switch(t) {
        case var_types::INT:
        case var_types::POINTER:
            current_offset += v * 4;
            break;
        case var_types::CHAR:
            current_offset += v * 1;
            break;
        default:
            break;
    }
}

void gerador::instruction_set::add_const(const std::string& name, int v) {
    context_stack.back().symbols.insert({name, symbol(ast_node_types::CONSTANT, var_types::INT, v)});
}

void gerador::instruction_set::add_parameter(const std::string& name, 
        ast_node_types tag, var_types t) {
    if(current_param <= gerador::registers::A3) {
        context_stack.back().registers[current_param] = true;
        context_stack.back().symbols.insert({name, symbol(tag, t, current_param++)});
    }
}

void gerador::instruction_set::new_context(const std::string& label) {
    context_stack.push_back(context());
    current_label = label;
    current_var = registers::S0;
    current_param = registers::A0;
}

void gerador::instruction_set::delete_context() {
    context_stack.pop_back();
}

void gerador::instruction_set::print() {
    std::cout << ".globl main" << std::endl;
    std::cout << ".data" << std::endl;
    for(auto& d : data) {
        if(d.second.type == SPACE) {
            std::cout << '\t' << d.first << ":\t";
            std::cout << " .space" << ' ' << d.second.size << std::endl;
        }
    }
    for(auto& d : data) {
        if(d.second.type == ASCIIZ) {
            std::cout << '\t' << d.first << ":\t";
            std::cout << " .asciiz" << ' ' << d.second.value << std::endl;
        }
    }
    std::cout << ".text" << std::endl;
    for(auto& t : text) {
        std::cout << t->to_string() << std::endl;
    }

    if(printf)
        std::cout << printf_snippet << std::endl;
}

std::string gerador::instruction_set::instruction::get_operation() {
    return op_labels[op];
}

std::string gerador::instruction_set::three_reg::to_string() {
    return "\t" + get_operation() + "\t" + 
        register_labels[r1] + ", " + register_labels[r2] + ", " + register_labels[r3];
}

std::string gerador::instruction_set::two_reg_immediate::to_string() {
    return op != LW && op != SW 
        ? "\t" + get_operation() + "\t" + 
            register_labels[r1] + ", " + register_labels[r2] + ", " + std::to_string(immediate)
        : "\t" + get_operation() + "\t" + 
            register_labels[r1] + ", " + std::to_string(immediate) + "(" + register_labels[r2] 
            + ")";
}

std::string gerador::instruction_set::one_label::to_string() {
    if(op == opcode::LABEL)
        return address + ":";
    else if(op == opcode::SYSCALL)
        return "\tsyscall";
    else
        return "\t" + get_operation() + "\t" + address;
}

std::string gerador::instruction_set::two_reg_label::to_string() {
    return "\t" + get_operation() + "\t" + 
        register_labels[r1] + ", " + register_labels[r2] + ", " + address;
}

std::string gerador::instruction_set::two_reg_access::to_string() {
    return "\t" + get_operation() + "\t" + 
        register_labels[r1] + ", " + std::to_string(offset) + "(" + register_labels[r2] + ")";
}

std::string gerador::instruction_set::one_reg::to_string() {
    return "\t" + get_operation() + "\t" + register_labels[r1];
}

std::string gerador::instruction_set::two_reg::to_string() {
    return "\t" + get_operation() + "\t" + register_labels[r1] + ", " + register_labels[r2];
}

std::string gerador::instruction_set::one_reg_address::to_string() {
    return "\t" + get_operation() + "\t" + register_labels[r1] + ", " + address;
}