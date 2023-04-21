#ifndef MIPS_HH
#define MIPS_HH

#include <map>
#include <string>
#include <vector>

#include "ast_node_types.hh"

#define IS_TEMP(a)      a >= registers::T0 && a <= registers::T7                                        \
                     || a == registers::T8                                                              \
                     || a == registers::T9

namespace gerador {
    typedef bool registers_in_use[32];

    enum opcode {
        ADD, SUB, ADDI, ADDU, SUBU, ADDIU, MUL, MULT, DIV, AND, OR, ANDI, ORI, SLLV, SRL, LW, SW, 
        LUI, MFHI, MFLO, BEQ, BNE, SLT, SLTI, J, JR, JAL, SYSCALL, LABEL, LA, NOR, SLTU, XORI, SRAV,
        XOR
    };

    enum registers {
        ZERO, AT, V0, V1, A0, A1, A2, A3, T0, T1, T2, T3, T4, T5, T6, T7, S0, S1, S2, S3, S4, S5, 
        S6, S7, T8, T9, K0, K1, GP, SP, FP, RA
    };

    registers& operator++(registers& r);
    registers operator++(registers& r, int);
    registers& operator--(registers& r);
    registers operator--(registers& r, int);

    enum global_type {
        HALF, BYTE, WORD = 4, ASCIIZ = 5, SPACE = 6
    };

    enum var_types { 
        VOID, CHAR, INT = 4, POINTER
    };

    struct symbol {
        ast_node_types tag;
        var_types type;
        union rep {
            registers var_or_param;
            int global_var_const;

            rep(registers r) : var_or_param(r) {};
            rep(int v) : global_var_const(v) {};
        } mapping;

        // symbol(symbol& s);
        symbol(ast_node_types tag, var_types t, registers r) : tag(tag), type(t), mapping(r) {};
        symbol(ast_node_types tag, var_types t, int v) : tag(tag), type(t), mapping(v) {};
    };

    class instruction_set {
        struct instruction {
            opcode op;

            virtual std::string to_string() = 0;
            
            protected:
            instruction(opcode op) : op(op) {};
            ~instruction() {};

            std::string get_operation();
        };

        struct three_reg : instruction {
            registers r1;
            registers r2;
            registers r3;

            three_reg(opcode op, registers r1, registers r2, registers r3) 
                : instruction(op), r1(r1), r2(r2), r3(r3) {};
            ~three_reg() {};
            std::string to_string();
        };

        struct two_reg_immediate : instruction {
            registers r1;
            registers r2;
            int immediate;

            two_reg_immediate(opcode op, registers r1, registers r2, int immediate) 
                : instruction(op), r1(r1), r2(r2), immediate(immediate) {};
            ~two_reg_immediate() {};
            std::string to_string();
        };

        struct one_label : instruction {
            std::string address;

            one_label(opcode op, const std::string& address) : instruction(op), address(address) {};
            ~one_label() {};
            std::string to_string();
        };

        struct two_reg_label : instruction {
            registers r1;
            registers r2;
            std::string address;

            two_reg_label(opcode op, registers r1, registers r2, const std::string& address) 
                : instruction(op), r1(r1), r2(r2), address(address) {};
            ~two_reg_label() {};
            std::string to_string();
        };

        struct two_reg_access : instruction {
            registers r1, r2;
            int offset;

            two_reg_access(opcode op, registers r1, registers r2, short offset) 
                : instruction(op), r1(r1), r2(r2), offset(offset) {};
            ~two_reg_access() {};
            std::string to_string();
        };

        struct one_reg : instruction {
            registers r1;

            one_reg(opcode op, registers r1) : instruction(op), r1(r1) {};
            ~one_reg() {};
            std::string to_string();
        };

        struct two_reg : instruction {
            registers r1, r2;

            two_reg(opcode op, registers r1, registers r2) : instruction(op), r1(r1), r2(r2) {};
            ~two_reg() {};
            std::string to_string();
        };

        struct one_reg_address : instruction {
            registers r1;
            std::string address;

            one_reg_address(opcode op, registers r1, const std::string& address) 
                : instruction(op), r1(r1), address(address) {};
            ~one_reg_address() {};
            std::string to_string();
        };

        struct global {
            std::string value;
            global_type type;
            int size;
            int offset;
        };

        struct context {
            std::map<std::string, symbol> symbols;
            bool registers[32];

            context() : symbols(), registers({ false }) {};
            ~context() {};
        };

        std::map<std::string, global> data;
        std::vector<instruction*> text;

        std::vector<context> context_stack;

        registers current_var,
                  current_param;
        std::string current_label;
        int current_offset;
        bool printf;

        public:
        instruction_set();
        ~instruction_set() {};

        symbol* get_symbol(const std::string& label);

        registers get_current_var();
        registers get_current_param();
        registers map_register(registers start = T0);
        bool* get_registers();

        void set_register(registers reg, bool status);
        void set_current_label(const std::string& label);
        const std::string& get_current_label(std::string& label);
        void clear_temp_reg();
        void use_printf();

        int get_string_offset(const std::string& str);
        int offset();

        void add_data(const std::string& label, global_type type, const std::string& value);
        void add_data(const std::string& label, global_type type, int size);

        void add_text(opcode op, registers r1, registers r2, registers r3);
        void add_text(opcode op, registers r1, registers r2, int immediate);
        void add_text(opcode op, const std::string& address);
        void add_text(opcode op, registers r1, registers r2, const std::string& address);
        void add_text(opcode op, registers r1, int immediate);
        void add_text(opcode op, registers r1);
        void add_text(opcode op, registers r1, const std::string& address);
        void add_text(opcode op, registers r1, registers r2);
        
        void add_label(const std::string& label);

        void add_variable(const std::string& name, var_types t);
        void add_global_var(const std::string& name, 
            var_types t, int v);
        void add_const(const std::string& name, int v);
        void add_parameter(const std::string& name, ast_node_types tag, var_types t);
        void new_context(const std::string& label);
        void delete_context();

        void print();

        // const std::vector<std::map<std::string, symbol>>& get_symbol_table() { return context_stack.back().symbols; };
        const std::map<std::string, global>& get_data() { return data; }; 
        const std::vector<instruction*>& get_text() { return text; };
        const std::string& get_current_label();
    };
}

#endif