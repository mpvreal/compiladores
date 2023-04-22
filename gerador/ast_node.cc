#include <iostream>

#include "ast_node.hh"

static int node_index = 0;

static const char* const node_labels[] = {
    "PROGRAM",
"CONSTANT",
"FUNCTION",
"VAR",
"GLOBAL_VAR",
"PARAM",
"FOR",
"WHILE",
"DO_WHILE",
"IF",
"CALL",
"PRINTF",
"SCANF",
"TERNARY",
"PLUS",
"MINUS",
"MULTIPLY",
"DIVISION",
"REMAINDER",
"BITWISE_AND",
"BITWISE_OR",
"BITWISE_XOR",
"LOGICAL_AND",
"LOGICAL_OR",
"EQUAL",
"NOT_EQUAL",
"LESS_THAN",
"GREATER_THAN",
"LESS_EQUAL",
"GREATER_EQUAL",
"R_SHIFT",
"L_SHIFT",
"ASSIGN",
"ADD_ASSIGN",
"MINUS_ASSIGN",
"PRE_INC",
"PRE_DEC",
"POST_INC",
"POST_DEC",
"BITWISE_NOT",
"REFERENCE",
"DEFERENCE",
"NEGATIVE",
"POSITIVE",
"NOT",
"EXIT",
"RETURN",
"ID",
"NUMBER",
"STRING",
"CHARACTER",
"STORE",
"ADD_STORE",
"MINUS_STORE"
};

static const char* const types[] = {
    "void",
    "char",
    "int",
    "pointer"
};

#define HANDLE_BINARY() if(IS_TEMP(rep.binary.left->mapping)) {                                                                     \
                            mapping = rep.binary.left->mapping;                                                                     \
                            if(IS_TEMP(rep.binary.right->mapping))                                                                      \
                                is.set_register(rep.binary.right->mapping, false);                                                                       \
                        } else if(IS_TEMP(rep.binary.right->mapping)) {                                                                     \
                            mapping = rep.binary.right->mapping;                                                                        \
                            if(IS_TEMP(rep.binary.left->mapping))                                                                       \
                                is.set_register(rep.binary.left->mapping, false);                                                                        \
                        } else                                                                      \
                            mapping = is.map_register();

static unsigned long string_counter = 0,
                     label_counter = 0,
                     if_counter = 0,
                     while_counter = 0,
                     for_counter = 0,
                     do_while_counter = 0,
                     ternary_counter = 0;

gerador::ast_node::~ast_node() {
    switch(label) {
        case PROGRAM:
            for(ast_node* c : rep.program.commands)
                delete c;
            break;
        case CONSTANT:
            delete rep.constant.value;
            break;
        case FUNCTION:
            for(ast_node* p : rep.function.params)
                delete p;
            for(ast_node* v : rep.function.vars)
                delete v;
            for(ast_node* c : rep.function.body)
                delete c;
            break;
        case FOR:
            delete rep.for_loop.init;
            delete rep.for_loop.condition;
            delete rep.for_loop.increment;
            for(ast_node* c : rep.for_loop.loop)
                delete c;
            break;
        case WHILE:
        case DO_WHILE:
            delete rep.while_loop.condition;
            for(ast_node* c : rep.while_loop.loop)
                delete c;
            break;
        case IF:
            delete rep.if_else.condition;
            for(ast_node* c : rep.if_else.then_body)
                delete c;
            for(ast_node* c : rep.if_else.else_body)
                delete c;
            break;
        case CALL:
        case PRINTF:
        case SCANF:
            for(ast_node* a : rep.call.params)
                delete a;
            break;
        case TERNARY:
            delete rep.ternary.condition;
            delete rep.ternary.then_body;
            delete rep.ternary.else_body;
            break;
        case PLUS:
        case MINUS:
        case MULTIPLY:
        case DIVISION:
        case REMAINDER:
        case BITWISE_AND:
        case BITWISE_OR:
        case BITWISE_XOR:
        case LOGICAL_AND:
        case LOGICAL_OR:
        case EQUAL:
        case NOT_EQUAL:
        case LESS_THAN:
        case GREATER_THAN:
        case LESS_EQUAL:
        case GREATER_EQUAL:
        case R_SHIFT:
        case L_SHIFT:
        case ASSIGN:
        case ADD_ASSIGN:
        case MINUS_ASSIGN:
        case STORE:
        case ADD_STORE:
        case MINUS_STORE:
            delete rep.binary.left;
            delete rep.binary.right;
            break;
        case PRE_INC:
        case PRE_DEC:
        case POST_INC:
        case POST_DEC:
        case BITWISE_NOT:
        case REFERENCE:
        case DEFERENCE:
        case NEGATIVE:
        case POSITIVE:
        case NOT:
        case EXIT:
        case RETURN:
            delete rep.unary.operand;
            break;
        default:
            break;
    }
}

gerador::ast_node& gerador::ast_node::operator=(const ast_node& node) {
    switch(node.label) {
        case gerador::ast_node_types::PROGRAM:
            rep.program = node.rep.program;
            break;
        case gerador::ast_node_types::CONSTANT:
            rep.constant = node.rep.constant;
            break;
        case gerador::ast_node_types::FUNCTION:
            rep.function = node.rep.function;
            break;
        case gerador::ast_node_types::VAR:
            rep.var_or_param = node.rep.var_or_param;
            break;
        case gerador::ast_node_types::FOR:
            rep.for_loop = node.rep.for_loop;
            break;
        case gerador::ast_node_types::WHILE:
        case gerador::ast_node_types::DO_WHILE:
            rep.while_loop = node.rep.while_loop;
            break;
        case gerador::ast_node_types::IF:
            rep.if_else = node.rep.if_else;
            break;
        case gerador::ast_node_types::CALL:
        case gerador::ast_node_types::PRINTF:
        case gerador::ast_node_types::SCANF:
            rep.call = node.rep.call;
            break;  
        case gerador::ast_node_types::TERNARY:
            rep.ternary = node.rep.ternary;
            break;
        case gerador::ast_node_types::PLUS:
        case gerador::ast_node_types::MINUS:
        case gerador::ast_node_types::MULTIPLY:
        case gerador::ast_node_types::DIVISION:
        case gerador::ast_node_types::REMAINDER:
        case gerador::ast_node_types::BITWISE_AND:
        case gerador::ast_node_types::BITWISE_OR:
        case gerador::ast_node_types::BITWISE_XOR:
        case gerador::ast_node_types::LOGICAL_AND:
        case gerador::ast_node_types::LOGICAL_OR:
        case gerador::ast_node_types::EQUAL:
        case gerador::ast_node_types::NOT_EQUAL:
        case gerador::ast_node_types::LESS_THAN:
        case gerador::ast_node_types::GREATER_THAN:
        case gerador::ast_node_types::LESS_EQUAL:
        case gerador::ast_node_types::GREATER_EQUAL:
        case gerador::ast_node_types::R_SHIFT:
        case gerador::ast_node_types::L_SHIFT:
        case gerador::ast_node_types::ASSIGN:
        case gerador::ast_node_types::ADD_ASSIGN:
        case gerador::ast_node_types::MINUS_ASSIGN:
            rep.binary = node.rep.binary;
            break;
        case gerador::ast_node_types::PRE_INC:
        case gerador::ast_node_types::PRE_DEC:
        case gerador::ast_node_types::POST_INC:
        case gerador::ast_node_types::POST_DEC:
        case gerador::ast_node_types::BITWISE_NOT:
        case gerador::ast_node_types::REFERENCE:
        case gerador::ast_node_types::DEFERENCE:
        case gerador::ast_node_types::NEGATIVE:
        case gerador::ast_node_types::POSITIVE:
        case gerador::ast_node_types::NOT:
        case gerador::ast_node_types::EXIT:
        case gerador::ast_node_types::RETURN:
            rep.unary = node.rep.unary;
            break;
        case gerador::ast_node_types::ID:
        case gerador::ast_node_types::STRING:
            rep.id_or_string.text = node.rep.id_or_string.text;
            break;
        case gerador::ast_node_types::NUMBER:
        case gerador::ast_node_types::CHARACTER:
            rep.number.value = node.rep.number.value;
            break;
        default:
            break;
    }
    label = node.label;

    return *this;
}

void gerador::ast_node::generate_code(instruction_set& is, bool ref_global_var) {
    symbol* s = nullptr;
    registers chosen_reg = ZERO;
    int space_shift = 0, stack_pointer = 0;
    bool nested_call = false;
    int l = 0;

    switch(label) {
        case gerador::ast_node_types::PROGRAM:
            is.delete_context();
            is.new_context("__global__");
            for(ast_node* n : rep.program.commands) {
                n->generate_code(is);
            }
            break;
        case gerador::ast_node_types::FUNCTION:
            is.set_current_label(rep.function.id);
            is.add_label(rep.function.id);
            is.new_context(rep.function.id);

            for(ast_node* n : rep.function.params) {
                n->generate_code(is);
            }
            for(ast_node* n : rep.function.vars) {
                n->generate_code(is);
            }
            for(ast_node* n : rep.function.body) {
                n->generate_code(is);
            }

            if(rep.function.return_type == gerador::var_types::VOID) {
                is.add_text(JR, RA);
            }

            free_registers_from_subtree(is);
            is.delete_context();
            break;
        case gerador::ast_node_types::CONSTANT:
            is.add_const(rep.constant.id, rep.constant.value->rep.number.value);
            break;
        case gerador::ast_node_types::GLOBAL_VAR:
            is.add_global_var(rep.var_or_param.id, rep.var_or_param.type, 0); 
            break;
        case gerador::ast_node_types::VAR:
            is.add_variable(rep.var_or_param.id, rep.var_or_param.type);
            break;
        case gerador::ast_node_types::PARAM:
            is.add_parameter(rep.var_or_param.id, gerador::ast_node_types::PARAM, 
                rep.var_or_param.type);
            break;
        case gerador::ast_node_types::FOR:
            l = for_counter++;
            rep.for_loop.init->generate_code(is);

            is.add_text(J, "for_" + std::to_string(l) + "_test");

            is.add_label("for_" + std::to_string(l) + "_loop");
            for(ast_node* n : rep.for_loop.loop) {
                n->generate_code(is);
            }
            rep.for_loop.increment->generate_code(is);

            is.add_label("for_" + std::to_string(l) + "_test");
            rep.for_loop.condition->generate_code(is);
            is.add_text(BNE, rep.for_loop.condition->mapping, ZERO,
                "for_" + std::to_string(l) + "_loop");
            free_registers_from_subtree(is);
            break;
        case gerador::ast_node_types::WHILE:
            l = while_counter++;
            is.add_text(J, "while_" + std::to_string(l) + "_test");

            is.add_label("while_" + std::to_string(l) + "_loop");
            for(ast_node* n : rep.while_loop.loop) {
                n->generate_code(is);
            }

            is.add_label("while_" + std::to_string(l) + "_test");
            rep.while_loop.condition->generate_code(is);

            is.add_text(BNE, rep.if_else.condition->mapping, ZERO,
                "while_" + std::to_string(l) + "_loop");
            free_registers_from_subtree(is);
            break;
        case gerador::ast_node_types::DO_WHILE:
            l = do_while_counter++;
            is.add_label("do_while_" + std::to_string(l) + "_loop");
            for(ast_node* n : rep.while_loop.loop) {
                n->generate_code(is);
            }

            rep.while_loop.condition->generate_code(is);

            is.add_text(BNE, rep.if_else.condition->mapping, ZERO,
                "do_while_" + std::to_string(l) + "_loop");
            free_registers_from_subtree(is);
            break;
        case gerador::ast_node_types::IF:
            l = if_counter++;
            rep.if_else.condition->generate_code(is);
            is.add_text(BEQ, rep.if_else.condition->mapping, ZERO,
                "if_" + std::to_string(l) + "_else");
            for(ast_node* n : rep.if_else.then_body) {
                n->generate_code(is);
            }
            is.add_text(J, "if_" + std::to_string(l) + "_exit");

            is.add_label("if_" + std::to_string(l) + "_else");
            for(ast_node* n : rep.if_else.else_body) {
                n->generate_code(is);
            }
            is.add_label("if_" + std::to_string(l) + "_exit");
            free_registers_from_subtree(is);
            break;
        case gerador::ast_node_types::CALL:
            for(registers r = A0; r <= T9; r++) {
                if(is.get_registers()[r])
                    space_shift += 4;
            }
            is.add_text(ADDI, SP, SP, -(space_shift + 4));
            for(registers r = A0; r <= T9; r++) {
                if(is.get_registers()[r]) {
                    is.add_text(SW, r, SP, stack_pointer);
                    stack_pointer += 4;
                }
            }
            for(ast_node* n : rep.call.params) {
                    n->generate_code(is);
            }
            chosen_reg = A0;
            for(ast_node* n : rep.call.params) {
                is.add_text(OR, chosen_reg++, ZERO, n->mapping);
            }
            free_registers_from_subtree(is);
            is.add_text(SW, RA, SP, stack_pointer);
            is.add_text(JAL, rep.call.id);
            is.add_text(LW, RA, SP, stack_pointer);
            stack_pointer -= 4;
            for(registers r = T9; r >= A0; r--) {
                if(is.get_registers()[r]) {
                    is.add_text(LW, r, SP, stack_pointer);
                    stack_pointer -= 4;
                }
            }
            is.add_text(ADDI, SP, SP, space_shift + 4);
            mapping = is.map_register();
            is.add_text(OR, mapping, ZERO, V0);
            break;
        case gerador::ast_node_types::PRINTF:
            for(registers r = A0; r <= T9; r++) {
                if(is.get_registers()[r])
                    space_shift += 4;
            }
            is.add_text(ADDI, SP, SP, -(space_shift + 4));
            for(registers r = A0; r <= T9; r++) {
                if(is.get_registers()[r]) {
                    is.add_text(SW, r, SP, stack_pointer);
                    stack_pointer += 4;
                }
            }
            for(ast_node* n : rep.call.params) {
                    n->generate_code(is);
            }
            chosen_reg = A0;
            for(ast_node* n : rep.call.params) {
                is.add_text(OR, chosen_reg++, ZERO, n->mapping);
            }
            free_registers_from_subtree(is);
            is.add_text(SW, RA, SP, stack_pointer);
            is.add_text(JAL, "printf");
            is.add_text(LW, RA, SP, stack_pointer);
            stack_pointer -= 4;
            for(registers r = T9; r >= A0; r--) {
                if(is.get_registers()[r]) {
                    is.add_text(LW, r, SP, stack_pointer);
                    stack_pointer -= 4;
                }
            }
            is.add_text(ADDI, SP, SP, space_shift + 4);
            is.use_printf();
            // mapping = is.map_register();
            // is.add_text(OR, mapping, ZERO, V0);
            // break;
            break;
        case gerador::ast_node_types::SCANF:
            if(rep.call.params[1]->rep.unary.operand->get_label() == DEFERENCE)
                s = is.get_symbol(rep.call.params[1]->rep.unary.operand->rep.unary.operand->
                    rep.id_or_string.text);
            else
                s = is.get_symbol(rep.call.params[1]->rep.unary.operand->rep.id_or_string.text);
            if(s->type == gerador::var_types::INT) {
                is.add_text(ORI, V0, ZERO, 5);
            } else if(s->type == gerador::var_types::CHAR) {
                is.add_text(ORI, V0, ZERO, 12);
            }
            is.add_text(SYSCALL, "scanf");
            if(s->tag == GLOBAL_VAR) {
                is.add_text(LA, V1, rep.call.params[1]->rep.unary.operand->rep.unary.operand
                    ->rep.id_or_string.text);
                is.add_text(SW, V0, V1, 0);
            }
            else
                is.add_text(OR, s->mapping.var_or_param, ZERO, V0);
            break;  
        case gerador::ast_node_types::TERNARY:
            l = ternary_counter++;

            mapping = is.map_register();

            rep.ternary.condition->generate_code(is);
            is.add_text(BEQ, rep.ternary.condition->mapping, ZERO, "ternary_" 
                + std::to_string(l) + "_else");
            
            rep.ternary.then_body->generate_code(is);
            is.add_text(OR, mapping, ZERO, rep.ternary.then_body->mapping);
            is.add_text(J, "ternary_" + std::to_string(l) + "_exit");
            rep.ternary.then_body->free_registers_from_subtree(is);

            is.add_label("ternary_" + std::to_string(l) + "_else");
            rep.ternary.else_body->generate_code(is);
            is.add_text(OR, mapping, ZERO, rep.ternary.else_body->mapping);
            rep.ternary.then_body->free_registers_from_subtree(is);

            is.add_label("ternary_" + std::to_string(l) + "_exit");
            break;
        case gerador::ast_node_types::PLUS:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(ADD, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            break;
        case gerador::ast_node_types::MINUS:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SUB, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            break;
        case gerador::ast_node_types::MULTIPLY:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(MUL, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            break;
        case gerador::ast_node_types::DIVISION:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(DIV, rep.binary.left->mapping, rep.binary.right->mapping);
            is.add_text(MFLO, mapping);
            break;
        case gerador::ast_node_types::REMAINDER:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(DIV, rep.binary.left->mapping, rep.binary.right->mapping);
            is.add_text(MFHI, mapping);
            break;
        case gerador::ast_node_types::BITWISE_AND:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(AND, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            break;
        case gerador::ast_node_types::BITWISE_OR:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(OR, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            break;
        case gerador::ast_node_types::BITWISE_XOR:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(XOR, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            break;
        case gerador::ast_node_types::LOGICAL_AND:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SLTU, rep.binary.left->mapping, ZERO, rep.binary.left->mapping);
            is.add_text(SLTU, rep.binary.right->mapping, ZERO, rep.binary.right->mapping);
            is.add_text(AND, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            break;
        case gerador::ast_node_types::LOGICAL_OR:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SLTU, rep.binary.left->mapping, ZERO, rep.binary.left->mapping);
            is.add_text(SLTU, rep.binary.right->mapping, ZERO, rep.binary.right->mapping);
            is.add_text(OR, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            break;
        case gerador::ast_node_types::EQUAL:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SUBU, mapping, rep.binary.left->mapping, 
                rep.binary.right->mapping);
            is.add_text(SLTU, mapping, ZERO, mapping);
            is.add_text(XORI, mapping, mapping, 1);
            break;
        case gerador::ast_node_types::NOT_EQUAL:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SUBU, mapping, rep.binary.left->mapping, 
                rep.binary.right->mapping);
            is.add_text(SLTU, mapping, ZERO, mapping);
            break;
        case gerador::ast_node_types::LESS_THAN:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SLT, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            break;
        case gerador::ast_node_types::GREATER_THAN:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SLT, mapping, rep.binary.right->mapping, rep.binary.left->mapping);
            break;
        case gerador::ast_node_types::LESS_EQUAL:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SLT, mapping, rep.binary.right->mapping, rep.binary.left->mapping);
            is.add_text(XORI, mapping, mapping, 1);
            break;
        case gerador::ast_node_types::GREATER_EQUAL:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SLT, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            is.add_text(XORI, mapping, mapping, 1);
            break;
        case gerador::ast_node_types::R_SHIFT:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SRAV, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            break;
        case gerador::ast_node_types::L_SHIFT:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SLLV, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            break;
        case gerador::ast_node_types::STORE:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SW, rep.binary.right->mapping, rep.binary.left->mapping, 0);
            is.add_text(OR, mapping, ZERO, rep.binary.right->mapping);

            free_registers_from_subtree(is);
            break;
        case gerador::ast_node_types::ADD_STORE:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(LW, mapping, rep.binary.left->mapping, 0);
            is.add_text(ADD, rep.binary.right->mapping, mapping, rep.binary.right->mapping);
            is.add_text(SW, rep.binary.right->mapping, rep.binary.left->mapping, 0);
            is.add_text(OR, mapping, ZERO, rep.binary.right->mapping);

            free_registers_from_subtree(is);
            break;
        case gerador::ast_node_types::MINUS_STORE:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(LW, mapping, rep.binary.left->mapping, 0);
            is.add_text(SUB, rep.binary.right->mapping, mapping, rep.binary.right->mapping);
            is.add_text(SW, rep.binary.right->mapping, rep.binary.left->mapping, 0);
            is.add_text(OR, mapping, ZERO, rep.binary.right->mapping);

            free_registers_from_subtree(is);
            break;
        case gerador::ast_node_types::ASSIGN:
            if(rep.binary.left->label == PARAM && 
                (s = is.get_symbol(rep.binary.left->rep.var_or_param.id))) {
                rep.binary.right->generate_code(is);

                HANDLE_BINARY();
                is.add_text(OR, s->mapping.var_or_param, ZERO, rep.binary.right->mapping);
                is.add_text(OR, mapping, ZERO, s->mapping.var_or_param);
            }
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(OR, rep.binary.left->mapping, ZERO, rep.binary.right->mapping);
            is.add_text(OR, mapping, ZERO, rep.binary.left->mapping);

            free_registers_from_subtree(is);
            break;
        case gerador::ast_node_types::ADD_ASSIGN:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(ADD, rep.binary.left->mapping, rep.binary.left->mapping, 
                rep.binary.right->mapping);
            is.add_text(OR, mapping, ZERO, rep.binary.left->mapping);
            free_registers_from_subtree(is);
            break;

        case gerador::ast_node_types::MINUS_ASSIGN:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SUB, rep.binary.left->mapping, rep.binary.left->mapping, 
                rep.binary.right->mapping);
            is.add_text(OR, mapping, ZERO, rep.binary.left->mapping);
            break;
        case gerador::ast_node_types::PRE_INC:
            if(rep.unary.operand) {
                rep.unary.operand->generate_code(is);

                mapping = is.map_register();
                is.add_text(ADDI, rep.unary.operand->mapping, rep.unary.operand->mapping, 1);
                is.add_text(ADD, mapping, ZERO, rep.unary.operand->mapping);
            }
            break;
        case gerador::ast_node_types::PRE_DEC:
            if(rep.unary.operand) {
                rep.unary.operand->generate_code(is);

                mapping = is.map_register();
                is.add_text(ADDI, rep.unary.operand->mapping, rep.unary.operand->mapping, -1);
                is.add_text(ADD, mapping, ZERO, rep.unary.operand->mapping);
            }
            break;
        case gerador::ast_node_types::POST_INC:
            if(rep.unary.operand){
                rep.unary.operand->generate_code(is);

                mapping = is.map_register();
                is.add_text(ADD, mapping, ZERO, rep.unary.operand->mapping);
                is.add_text(ADDI, rep.unary.operand->mapping, rep.unary.operand->mapping, 1);
            }
            break;
        case gerador::ast_node_types::POST_DEC:
            if(rep.unary.operand){
                rep.unary.operand->generate_code(is);

                mapping = is.map_register();
                is.add_text(ADD, mapping, ZERO, rep.unary.operand->mapping);
                is.add_text(ADDI, rep.unary.operand->mapping, rep.unary.operand->mapping, -1);
            }
            break;
        case gerador::ast_node_types::BITWISE_NOT:
            if(rep.unary.operand) {
                rep.unary.operand->generate_code(is);

                if(IS_TEMP(rep.unary.operand->mapping))
                    mapping = rep.unary.operand->mapping;
                else 
                    mapping = is.map_register();
                is.add_text(NOR, mapping, rep.unary.operand->mapping, ZERO);
            }
            break;
        case gerador::ast_node_types::REFERENCE:
            if(rep.unary.operand)
                rep.unary.operand->generate_code(is);
            break;
        case gerador::ast_node_types::DEFERENCE:
            if(rep.unary.operand) {
                rep.unary.operand->generate_code(is);

                if(IS_TEMP(rep.unary.operand->mapping))
                    mapping = rep.unary.operand->mapping;
                else 
                    mapping = is.map_register();
                is.add_text(LW, mapping, rep.unary.operand->mapping, 0);
            }
            break;
        case gerador::ast_node_types::NEGATIVE:
            if(rep.unary.operand) {
                rep.unary.operand->generate_code(is);

                if(IS_TEMP(rep.unary.operand->mapping))
                    mapping = rep.unary.operand->mapping;
                else 
                    mapping = is.map_register();
                is.add_text(SUB, mapping, ZERO, rep.unary.operand->mapping);
            }
            break;
        case gerador::ast_node_types::POSITIVE:
            if(rep.unary.operand) {
                rep.unary.operand->generate_code(is);
            }
            break;
        case gerador::ast_node_types::NOT:
            if(rep.unary.operand) {
                rep.unary.operand->generate_code(is);

                if(IS_TEMP(rep.unary.operand->mapping))
                    mapping = rep.unary.operand->mapping;
                else 
                    mapping = is.map_register();
                is.add_text(SUBU, mapping, rep.unary.operand->mapping, ZERO);
                is.add_text(SLTU, mapping, ZERO, mapping);
                is.add_text(XORI, mapping, mapping, 1);
                break;
            }
        case gerador::ast_node_types::EXIT:
            if(rep.unary.operand) {
                rep.unary.operand->generate_code(is);
                is.add_text(ORI, V0, ZERO, 17);
                is.add_text(OR, A0, ZERO, rep.unary.operand->mapping);
                is.add_text(SYSCALL, "exit");
            }
            break;
        case gerador::ast_node_types::RETURN:
            if(rep.unary.operand) {
                rep.unary.operand->generate_code(is);
                is.add_text(opcode::OR, registers::V0, 
                    registers::ZERO, rep.unary.operand->mapping);
                    is.add_text(JR, RA);
            } else {
                    is.add_text(JR, RA);
            }
            break;
        case gerador::ast_node_types::NUMBER:
        case gerador::ast_node_types::CHARACTER:
            mapping = is.map_register();
            is.add_text(opcode::ORI, mapping, ZERO, rep.number.value);
            break;
        case gerador::ast_node_types::ID:
            s = is.get_symbol(rep.id_or_string.text);
            if(s != nullptr) switch(s->tag) {
                case ast_node_types::CONSTANT:
                    mapping = is.map_register();
                    is.add_text(ORI, mapping, ZERO, s->mapping.global_var_const);
                    break;
                case ast_node_types::GLOBAL_VAR:
                    mapping = is.map_register();
                    is.add_text(LA, mapping, rep.id_or_string.text);
                    break;
                case ast_node_types::VAR:
                    mapping = s->mapping.var_or_param;
                    break;
                case ast_node_types::PARAM:
                    mapping = is.map_register();
                    is.add_text(OR, mapping, ZERO, s->mapping.var_or_param);
                    break;
            }   
            break;
        case gerador::ast_node_types::STRING:
            mapping = is.map_register();
            is.add_text(opcode::LA, mapping, "str" + std::to_string(string_counter));
            is.add_data("str" + std::to_string(string_counter++), 
                gerador::global_type::ASCIIZ, rep.id_or_string.text);
            break;
        default:
            break;
    }
}

gerador::ast_node* gerador::ast_node::bypass_deference() {
    return rep.unary.operand;
}

int gerador::ast_node::get_number_value() {
    return rep.number.value;
}

int gerador::ast_node::eval_array_size() {
    switch(label) {
        case gerador::ast_node_types::DEFERENCE:
            return rep.unary.operand->eval_array_size();
        case gerador::ast_node_types::MULTIPLY:
            return rep.binary.left->eval_array_size() * rep.binary.right->eval_array_size();
        case gerador::ast_node_types::PLUS:
            return rep.binary.left->eval_array_size() + rep.binary.right->eval_array_size();
        case gerador::ast_node_types::NUMBER:
            return rep.number.value;
        default:
            return 0;
    }
}

void gerador::ast_node::visit(void (*routine)(gerador::ast_node&)) {
    routine(*this);
    switch(label) {
        case gerador::ast_node_types::PROGRAM:
            for(ast_node* n : rep.program.commands) {
                n->visit(routine);
            }
            break;
        case gerador::ast_node_types::FUNCTION:
            for(ast_node* n : rep.function.params) {
                n->visit(routine);
            }
            for(ast_node* n : rep.function.vars) {
                n->visit(routine);
            }
            for(ast_node* n : rep.function.body) {
                n->visit(routine);
            }
            break;
        case gerador::ast_node_types::CONSTANT:
                rep.constant.value->visit(routine);
            break;
        case gerador::ast_node_types::FOR:
            rep.for_loop.init->visit(routine);
            rep.for_loop.condition->visit(routine);
            rep.for_loop.increment->visit(routine);
            for(ast_node* n : rep.for_loop.loop) {
                n->visit(routine);
            }
            break;
        case gerador::ast_node_types::WHILE:
        case gerador::ast_node_types::DO_WHILE:
            rep.while_loop.condition->visit(routine);
            for(ast_node* n : rep.while_loop.loop) {
                n->visit(routine);
            }
            break;
        case gerador::ast_node_types::IF:
            rep.if_else.condition->visit(routine);

            for(ast_node* n : rep.if_else.then_body) {
                n->visit(routine);
            }
            for(ast_node* n : rep.if_else.else_body) {
                n->visit(routine);
            }
            break;
        case gerador::ast_node_types::CALL:
        case gerador::ast_node_types::PRINTF:
        case gerador::ast_node_types::SCANF:
            for(ast_node* n : rep.call.params) {
                n->visit(routine);
            }
            break;  
        case gerador::ast_node_types::TERNARY:
            rep.ternary.condition->visit(routine);
            rep.ternary.then_body->visit(routine);
            rep.ternary.else_body->visit(routine);
            break;
        case gerador::ast_node_types::PLUS:
        case gerador::ast_node_types::MINUS:
        case gerador::ast_node_types::MULTIPLY:
        case gerador::ast_node_types::DIVISION:
        case gerador::ast_node_types::REMAINDER:
        case gerador::ast_node_types::BITWISE_AND:
        case gerador::ast_node_types::BITWISE_OR:
        case gerador::ast_node_types::BITWISE_XOR:
        case gerador::ast_node_types::LOGICAL_AND:
        case gerador::ast_node_types::LOGICAL_OR:
        case gerador::ast_node_types::EQUAL:
        case gerador::ast_node_types::NOT_EQUAL:
        case gerador::ast_node_types::LESS_THAN:
        case gerador::ast_node_types::GREATER_THAN:
        case gerador::ast_node_types::LESS_EQUAL:
        case gerador::ast_node_types::GREATER_EQUAL:
        case gerador::ast_node_types::R_SHIFT:
        case gerador::ast_node_types::L_SHIFT:
        case gerador::ast_node_types::ASSIGN:
        case gerador::ast_node_types::ADD_ASSIGN:
        case gerador::ast_node_types::MINUS_ASSIGN:
        case gerador::ast_node_types::STORE:
        case gerador::ast_node_types::ADD_STORE:
        case gerador::ast_node_types::MINUS_STORE:
            rep.binary.left->visit(routine);
            rep.binary.right->visit(routine);
            break;
        case gerador::ast_node_types::PRE_INC:
        case gerador::ast_node_types::PRE_DEC:
        case gerador::ast_node_types::POST_INC:
        case gerador::ast_node_types::POST_DEC:
        case gerador::ast_node_types::BITWISE_NOT:
        case gerador::ast_node_types::REFERENCE:
        case gerador::ast_node_types::DEFERENCE:
        case gerador::ast_node_types::NEGATIVE:
        case gerador::ast_node_types::POSITIVE:
        case gerador::ast_node_types::NOT:
        case gerador::ast_node_types::EXIT:
        case gerador::ast_node_types::RETURN:
            if(rep.unary.operand)
                rep.unary.operand->visit(routine);
            break;
        default:
            break;
    }
}

inline const char* gerador::ast_node::to_string() {
    // std::cout << label << std::endl;
    return node_labels[label];
}

void gerador::ast_node::free_registers_from_subtree(gerador::instruction_set& is) {
    // do a switch case on label with ALL of the entries of ast_node_types
    // for each case, call free_registers_from_subtree on all of the children   
    // of that node
    switch(label) {
        case gerador::ast_node_types::PROGRAM:
            for(ast_node* n : rep.program.commands) {
                n->free_registers_from_subtree(is);
            }
            break;
        case gerador::ast_node_types::FUNCTION:
            for(ast_node* n : rep.function.params) {
                n->free_registers_from_subtree(is);
            }
            for(ast_node* n : rep.function.vars) {
                n->free_registers_from_subtree(is);
            }
            for(ast_node* n : rep.function.body) {
                n->free_registers_from_subtree(is);
            }
            break;
        case gerador::ast_node_types::CONSTANT:
                rep.constant.value->free_registers_from_subtree(is);
            break;
        case gerador::ast_node_types::FOR:
            rep.for_loop.init->free_registers_from_subtree(is);
            rep.for_loop.condition->free_registers_from_subtree(is);
            rep.for_loop.increment->free_registers_from_subtree(is);
            for(ast_node* n : rep.for_loop.loop) {
                n->free_registers_from_subtree(is);
            }
            break;
        case gerador::ast_node_types::WHILE:
        case gerador::ast_node_types::DO_WHILE:
            rep.while_loop.condition->free_registers_from_subtree(is);
            for(ast_node* n : rep.while_loop.loop) {
                n->free_registers_from_subtree(is);
            }
            break;
        case gerador::ast_node_types::IF:
            rep.if_else.condition->free_registers_from_subtree(is);

            for(ast_node* n : rep.if_else.then_body) {
                n->free_registers_from_subtree(is);
            }
            for(ast_node* n : rep.if_else.else_body) {
                n->free_registers_from_subtree(is);
            }
            break;
        case gerador::ast_node_types::CALL:
        case gerador::ast_node_types::PRINTF:
        case gerador::ast_node_types::SCANF:
            for(ast_node* n : rep.call.params) {
                n->free_registers_from_subtree(is);
            }
            break;  
        case gerador::ast_node_types::TERNARY:
            rep.ternary.condition->free_registers_from_subtree(is);
            rep.ternary.then_body->free_registers_from_subtree(is);
            rep.ternary.else_body->free_registers_from_subtree(is);
            break;
        case gerador::ast_node_types::PLUS:
        case gerador::ast_node_types::MINUS:
        case gerador::ast_node_types::MULTIPLY:
        case gerador::ast_node_types::DIVISION:
        case gerador::ast_node_types::REMAINDER:
        case gerador::ast_node_types::BITWISE_AND:
        case gerador::ast_node_types::BITWISE_OR:
        case gerador::ast_node_types::BITWISE_XOR:
        case gerador::ast_node_types::LOGICAL_AND:
        case gerador::ast_node_types::LOGICAL_OR:
        case gerador::ast_node_types::EQUAL:
        case gerador::ast_node_types::NOT_EQUAL:
        case gerador::ast_node_types::LESS_THAN:
        case gerador::ast_node_types::GREATER_THAN:
        case gerador::ast_node_types::LESS_EQUAL:
        case gerador::ast_node_types::GREATER_EQUAL:
        case gerador::ast_node_types::R_SHIFT:
        case gerador::ast_node_types::L_SHIFT:
        case gerador::ast_node_types::ASSIGN:
        case gerador::ast_node_types::ADD_ASSIGN:
        case gerador::ast_node_types::MINUS_ASSIGN:
            rep.binary.left->free_registers_from_subtree(is);
            rep.binary.right->free_registers_from_subtree(is);
            break;
        case gerador::ast_node_types::PRE_INC:
        case gerador::ast_node_types::PRE_DEC:
        case gerador::ast_node_types::POST_INC:
        case gerador::ast_node_types::POST_DEC:
        case gerador::ast_node_types::BITWISE_NOT:
        case gerador::ast_node_types::REFERENCE:
        case gerador::ast_node_types::DEFERENCE:
        case gerador::ast_node_types::NEGATIVE:
        case gerador::ast_node_types::POSITIVE:
        case gerador::ast_node_types::NOT:
        case gerador::ast_node_types::EXIT:
        case gerador::ast_node_types::RETURN:
            if(rep.unary.operand)
                rep.unary.operand->free_registers_from_subtree(is);
            break;
        default:
            break;
    }
    if(IS_TEMP(mapping)) {
    is.set_register(mapping, false);
    mapping = ZERO;
    }
}

void gerador::declare_node_dot(gerador::ast_node& node) {
    std::string l = "";
    if(node.get_label() == gerador::ast_node_types::ID) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << node.to_string() << ": " << node.get_rep().id_or_string.text << "\"]" 
        << std::endl;
    } else if(node.get_label() == gerador::ast_node_types::STRING) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=<" << node.get_rep().id_or_string.text << ">]" 
        << std::endl;
    } else if(node.get_label() == gerador::ast_node_types::NUMBER) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << std::to_string(node.get_rep().number.value) << "\"]" 
        << std::endl;
    } else if(node.get_label() == gerador::ast_node_types::CALL) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << "CALL: " << node.get_rep().call.id << "()" << "\"]" 
        << std::endl;
    } else if(node.get_label() == gerador::ast_node_types::VAR) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << "VAR: " << node.get_rep().var_or_param.id << "\nTYPE: " << 
        types[node.get_rep().var_or_param.type] << "\"]" 
        << std::endl;
    } else if(node.get_label() == gerador::ast_node_types::CONSTANT) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << "CONST: " << node.get_rep().var_or_param.id << "\"]" 
        << std::endl;
    } else if(node.get_label() == gerador::ast_node_types::FUNCTION) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << "FUNCTION: " << node.get_rep().function.id << "\nTYPE: " << 
        types[node.get_rep().function.return_type] << "\"]" 
        << std::endl;
    } else if(node.get_label() == gerador::ast_node_types::PARAM) {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << "PARAM: " << node.get_rep().var_or_param.id << "\nTYPE: " << 
        types[node.get_rep().var_or_param.type] << "\"]" 
        << std::endl;
    } else {
        std::cout << "    n" << std::to_string(node_index++) 
        << " [label=\"" << node.to_string() << "\"]" 
        << std::endl;
    }
}

void gerador::declare_edge_dot(ast_node& node, const std::string& edge_label) {
    std::cout << edge_label << std::endl;

    int current_node = node_index++;

    switch(node.get_label()) {
        case gerador::ast_node_types::PROGRAM:
            for(ast_node* n : node.get_rep().program.commands) {
                declare_edge_dot(*n,
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            break;
        case gerador::ast_node_types::FUNCTION:
            for(ast_node* n : node.get_rep().function.params) {
                declare_edge_dot(*n,
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            for(ast_node* n : node.get_rep().function.vars) {
                declare_edge_dot(*n,
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            for(ast_node* n : node.get_rep().function.body) {
                declare_edge_dot(*n,
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            break;
        case gerador::ast_node_types::CONSTANT:
            declare_edge_dot(*node.get_rep().constant.value, 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            break;
        case gerador::ast_node_types::FOR:
            // node.get_rep().for_loop.init->visit(routine);
            declare_edge_dot(*node.get_rep().for_loop.init, 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            declare_edge_dot(*node.get_rep().for_loop.condition, 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            declare_edge_dot(*node.get_rep().for_loop.increment, 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            for(ast_node* n : node.get_rep().for_loop.loop) {
                declare_edge_dot(*n,
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            break;
        case gerador::ast_node_types::WHILE:
        case gerador::ast_node_types::DO_WHILE:
            declare_edge_dot(*node.get_rep().while_loop.condition, 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            for(ast_node* n : node.get_rep().while_loop.loop) {
                declare_edge_dot(*n,
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            break;
        case gerador::ast_node_types::IF:
            declare_edge_dot(*node.get_rep().if_else.condition, 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));

            for(ast_node* n : node.get_rep().if_else.then_body) {
                declare_edge_dot(*n,
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            for(ast_node* n : node.get_rep().if_else.else_body) {
                declare_edge_dot(*n,
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            break;
        case gerador::ast_node_types::CALL:
        case gerador::ast_node_types::PRINTF:
        case gerador::ast_node_types::SCANF:
            for(ast_node* n : node.get_rep().call.params) {
                declare_edge_dot(*n,
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            }
            break;  
        case gerador::ast_node_types::TERNARY:
            declare_edge_dot(*node.get_rep().ternary.condition, 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            declare_edge_dot(*node.get_rep().ternary.then_body, 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            declare_edge_dot(*node.get_rep().ternary.else_body, 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            break;
        case gerador::ast_node_types::PLUS:
        case gerador::ast_node_types::MINUS:
        case gerador::ast_node_types::MULTIPLY:
        case gerador::ast_node_types::DIVISION:
        case gerador::ast_node_types::REMAINDER:
        case gerador::ast_node_types::BITWISE_AND:
        case gerador::ast_node_types::BITWISE_OR:
        case gerador::ast_node_types::BITWISE_XOR:
        case gerador::ast_node_types::LOGICAL_AND:
        case gerador::ast_node_types::LOGICAL_OR:
        case gerador::ast_node_types::EQUAL:
        case gerador::ast_node_types::NOT_EQUAL:
        case gerador::ast_node_types::LESS_THAN:
        case gerador::ast_node_types::GREATER_THAN:
        case gerador::ast_node_types::LESS_EQUAL:
        case gerador::ast_node_types::GREATER_EQUAL:
        case gerador::ast_node_types::R_SHIFT:
        case gerador::ast_node_types::L_SHIFT:
        case gerador::ast_node_types::ASSIGN:
        case gerador::ast_node_types::ADD_ASSIGN:
        case gerador::ast_node_types::MINUS_ASSIGN:
        case gerador::ast_node_types::STORE:
        case gerador::ast_node_types::ADD_STORE:
        case gerador::ast_node_types::MINUS_STORE:
            declare_edge_dot(*node.get_rep().binary.left, 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            declare_edge_dot(*node.get_rep().binary.right, 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            break;
        case gerador::ast_node_types::PRE_INC:
        case gerador::ast_node_types::PRE_DEC:
        case gerador::ast_node_types::POST_INC:
        case gerador::ast_node_types::POST_DEC:
        case gerador::ast_node_types::BITWISE_NOT:
        case gerador::ast_node_types::REFERENCE:
        case gerador::ast_node_types::DEFERENCE:
        case gerador::ast_node_types::NEGATIVE:
        case gerador::ast_node_types::POSITIVE:
        case gerador::ast_node_types::NOT:
        case gerador::ast_node_types::EXIT:
        case gerador::ast_node_types::RETURN:
            if(node.get_rep().unary.operand)
                declare_edge_dot(*node.get_rep().unary.operand, 
                    "    n" + std::to_string(current_node) + " -> n" + std::to_string(node_index));
            break;
        default:
            break;
    }
}

void gerador::reset_index() {
    node_index = 0;
}