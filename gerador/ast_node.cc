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
"CHARACTER"
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

#define HANDLE_WHILE() is.add_label("L" + std::to_string(label_counter));\
                       for(ast_node* n : rep.while_loop.loop) {\
                           n->generate_code(is);\
                       }\
                       is.add_label("L" + std::to_string(label_counter + 1));\
                       rep.while_loop.condition->generate_code(is);\
                       is.add_text(BNE, rep.if_else.condition->mapping, ZERO,\
                           "L" + std::to_string(label_counter));\
                       ++label_counter;

// static bool temporary[8] = {false, false, false, false, false, false, false};
// static bool saved[8] = {false, false, false, false, false, false, false};
// static bool arguments[4] = { false, false, false, false };
static unsigned long string_counter = 0,
                     label_counter = 0;

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

void gerador::ast_node::generate_code(gerador::instruction_set& is) {
    symbol* s = nullptr;
    registers chosen_reg = ZERO;
    int label1 = 0, label2 = 0, label3 = 0, label4 = 0;
    bool nested_call = false;

    switch(label) {
        case gerador::ast_node_types::PROGRAM:
            is.delete_context();
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

            if(rep.function.id == "main") {
                is.add_text(ORI, V0, ZERO, 10);
                is.add_text(SYSCALL, "exit");
            }

            is.clear_temp_reg();
            is.delete_context();
            break;
        case gerador::ast_node_types::GLOBAL_VAR:
            is.add_global_var(rep.var_or_param.id, rep.var_or_param.type, 0);
            break;
        case gerador::ast_node_types::VAR:
            is.add_variable(rep.var_or_param.id, rep.var_or_param.type);
            is.set_register(is.get_current_var(), true);
            break;
        case gerador::ast_node_types::PARAM:
            is.add_parameter(rep.var_or_param.id, gerador::ast_node_types::PARAM, 
                rep.var_or_param.type);
            is.set_register(is.get_current_param(), true);
            break;
        case gerador::ast_node_types::FOR:
            rep.for_loop.init->generate_code(is);
            rep.for_loop.condition->generate_code(is);
            rep.for_loop.increment->generate_code(is);
            for(ast_node* n : rep.for_loop.loop) {
                n->generate_code(is);
            }
            break;
        case gerador::ast_node_types::WHILE:
            is.clear_temp_reg();
            is.add_text(J, "L" + std::to_string(label_counter + 1));
            HANDLE_WHILE();
            is.clear_temp_reg();
            break;
        case gerador::ast_node_types::DO_WHILE:
            is.clear_temp_reg();
            HANDLE_WHILE();
            is.clear_temp_reg();
            break;
        case gerador::ast_node_types::IF:
            label1 = label_counter++;
            label2 = label_counter++;
            is.clear_temp_reg();
            rep.if_else.condition->generate_code(is);
            is.add_text(BEQ, rep.if_else.condition->mapping, ZERO,
                "L" + std::to_string(label1));
            for(ast_node* n : rep.if_else.then_body) {
                n->generate_code(is);
            }
            is.add_text(J, "L" + std::to_string(label2));

            is.add_label("L" + std::to_string(label1));
            for(ast_node* n : rep.if_else.else_body) {
                n->generate_code(is);
            }
            is.add_label("L" + std::to_string(label2));
            // ++label_counter;
            // is.clear_temp_reg();
            break;
        case gerador::ast_node_types::CALL:
            is.add_text(ADDI, SP, SP, -4 * 12);
            for(registers r = A0; r <= A3; r++) {
                is.add_text(SW, r, SP, (A3 - r + 8) * 4);
            }
            for(registers r = S0; r <= S7; r++) {
                is.add_text(SW, r, SP, (S7 - r) * 4);
            }
            for(ast_node* n : rep.call.params) {
                if(n->label == CALL || n->label == PRINTF || n->label == SCANF)
                    n->generate_code(is);
            }
            chosen_reg = A0;
            for(ast_node* n : rep.call.params) {
                if(n->label != CALL && n->label && PRINTF && n->label != SCANF)
                    n->generate_code(is);
                is.add_text(OR, chosen_reg++, ZERO, n->mapping);
                // is.set_register(chosen_reg++, true);
            }
            is.add_text(ADDI, SP, SP, -4);
            is.add_text(SW, RA, SP, 0);
            is.add_text(JAL, rep.call.id);
            is.add_text(LW, RA, SP, 0);
            for(registers r = S7; r >= S0; r--) {
                is.add_text(LW, r, SP, (S7 - r + 1) * 4);
            }
            for(registers r = A3; r >= A0; r--) {
                is.add_text(LW, r, SP, (A3 - r + 9) * 4);
            }
            is.add_text(ADDI, SP, SP, 4 * 13);
            mapping = is.map_register();
            is.add_text(OR, mapping, ZERO, V0);
            break;
        case gerador::ast_node_types::PRINTF:
            for(ast_node* n : rep.call.params) {
                if(n->label == CALL || n->label == PRINTF || n->label == SCANF)
                    n->generate_code(is);
            }
            chosen_reg = A0;
            for(ast_node* n : rep.call.params) {
                if(n->label != CALL && n->label && PRINTF && n->label != SCANF)
                    n->generate_code(is);
                is.add_text(OR, chosen_reg++, ZERO, n->mapping);
            }
            is.add_text(JAL, "printf");
            is.use_printf();
            break;
        case gerador::ast_node_types::SCANF:
            s = is.get_symbol(rep.call.params[1]->rep.unary.operand->rep.id_or_string.text);
            if(s->type == gerador::var_types::INT) {
                is.add_text(ORI, V0, ZERO, 5);
            } else if(s->type == gerador::var_types::CHAR) {
                is.add_text(ORI, V0, ZERO, 12);
            }
            is.add_text(SYSCALL, "scanf");
            is.add_text(OR, s->mapping.var_or_param, ZERO, V0);
            break;  
        case gerador::ast_node_types::TERNARY:
            rep.ternary.condition->generate_code(is);
            rep.ternary.then_body->generate_code(is);
            rep.ternary.else_body->generate_code(is);
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
        // case gerador::ast_node_types::BITWISE_XOR:
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
            // is.add_text(SLT, mapping, rep.binary.right->mapping, rep.binary.left->mapping);
            // is.add_text(ADDI, V1, ZERO, 1);
            // is.add_text(SUBU, mapping, V1, mapping);
            break;
        case gerador::ast_node_types::GREATER_EQUAL:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(SLT, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            is.add_text(XORI, mapping, mapping, 1);
            // is.add_text(SLT, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            // is.add_text(ADDI, V1, ZERO, 1);
            // is.add_text(SUBU, mapping, V1, mapping);
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
            is.add_text(SLL, mapping, rep.binary.left->mapping, rep.binary.right->mapping);
            break;
        case gerador::ast_node_types::ASSIGN:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(ADD, rep.binary.left->mapping, ZERO, rep.binary.right->mapping);
            is.add_text(ADD, mapping, ZERO, rep.binary.left->mapping);
            is.clear_temp_reg();
            break;
        case gerador::ast_node_types::ADD_ASSIGN:
            rep.binary.left->generate_code(is);
            rep.binary.right->generate_code(is);

            HANDLE_BINARY();
            is.add_text(ADD, rep.binary.left->mapping, rep.binary.left->mapping, 
                rep.binary.right->mapping);
            is.add_text(OR, mapping, ZERO, rep.binary.left->mapping);
            is.clear_temp_reg();
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
                if(is.get_current_label() != "main")
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
                    mapping = s->mapping.var_or_param;
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