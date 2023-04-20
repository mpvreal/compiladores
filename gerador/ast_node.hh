#ifndef AST_NODE_HH
#define AST_NODE_HH

#include <vector>
#include <list>
#include <string>

#include "mips.hh"

namespace gerador {
    class ast_node { 
        union ast_node_representation {
            struct ast_program { 
                std::vector<ast_node*> commands; 

                ast_program(const std::vector<ast_node*>& c) : commands(c) {};
                ~ast_program() {};
            } program;

            struct ast_constant { 
                std::string id;
                ast_node* value;

                ast_constant(const std::string& s, ast_node* v) 
                    : id(s), value(v) {};
                ~ast_constant() {};
            } constant;

            struct ast_function { 
                std::string id; 
                gerador::var_types return_type;
                std::vector<ast_node*> params;
                std::vector<ast_node*> vars;
                std::vector<ast_node*> body;  
            
                ast_function(const std::string& s, gerador::var_types r, 
                    const std::vector<ast_node*>& p, const std::vector<ast_node*> v, const std::vector<ast_node*>& b)
                    : id(s), return_type(r), params(p), vars(v), body(b) {};
                ~ast_function() {};
            } function;

            struct ast_var { 
                std::string id; 
                gerador::var_types type; 
                
                ast_var(const std::string& s, gerador::var_types t) : id(s), type(t) {};
                ~ast_var() {};
            } var_or_param;

            
            struct ast_for { 
                ast_node* init; 
                ast_node* condition; 
                ast_node* increment; 
                std::vector<ast_node*> loop; 

                ast_for(ast_node* i, ast_node* c, ast_node* inc, const std::vector<ast_node*>& l) 
                    : init(i), condition(c), increment(inc), loop(l) {};
                ~ast_for() {};
            } for_loop;

            struct ast_while { 
                ast_node* condition; 
                std::vector<ast_node*> loop; 

                ast_while(ast_node* c, const std::vector<ast_node*>& l) : condition(c), loop(l) {};
                ~ast_while() {};
            } while_loop;

            struct ast_if { 
                ast_node* condition; 
                std::vector<ast_node*> then_body; 
                std::vector<ast_node*> else_body; 

                ast_if(ast_node* c, const std::vector<ast_node*>& t, const std::vector<ast_node*>& e) 
                    : condition(c), then_body(t), else_body(e) {};    
                ~ast_if() {};
            } if_else;

            struct ast_call { 
                std::string id; 
                std::vector<ast_node*> params; 
                
                ast_call(const std::string& s, const std::vector<ast_node*>& p) : id(s), params(p) {};
                ~ast_call() {};
            } call;
   
            struct ast_ternary { 
                ast_node* condition; 
                ast_node* then_body; 
                ast_node* else_body; 

                ast_ternary(ast_node* c, ast_node* t, ast_node* e) : condition(c), then_body(t), else_body(e) {};
                ~ast_ternary() {};
            } ternary;

            struct ast_binary { 
                ast_node* left; 
                ast_node* right; 
                
                ast_binary(ast_node* l, ast_node* r) : left(l), right(r) {};
                ~ast_binary() {};
            } binary;

            struct ast_unary { 
                ast_node* operand; 

                ast_unary(ast_node* o) : operand(o) {};
                ~ast_unary() {};
            } unary;
            
            struct ast_id_or_string { 
                std::string text;

                ast_id_or_string(const std::string& s) : text(s) {};
                ~ast_id_or_string() {};
            } id_or_string;

            struct ast_number { 
                int value; 

                ast_number(int v) : value(v) {};
                ~ast_number() {};
            } number;

            ast_node_representation(const std::vector<ast_node*>& commands) : program(commands) {};
            ast_node_representation(const std::string& s, ast_node* v) : constant(s, v) {};
            ast_node_representation(const std::string& s, gerador::var_types r, const std::vector<ast_node*>& p, 
                const std::vector<ast_node*>& v, const std::vector<ast_node*>& b) : function(s, r, p, v, b) {};
            ast_node_representation(const std::string& s, gerador::var_types t) : var_or_param(s, t) {};
            ast_node_representation(ast_node* i, ast_node* c, ast_node* inc, const std::vector<ast_node*>& l) 
                : for_loop(i, c, inc, l) {};
            ast_node_representation(ast_node* c, const std::vector<ast_node*>& l) : while_loop(c, l) {};
            ast_node_representation(ast_node* c, const std::vector<ast_node*>& t, const std::vector<ast_node*>& e) 
                : if_else(c, t, e) {};
            ast_node_representation(const std::string& s, const std::vector<ast_node*>& p) 
                : call(s, p) {};
            ast_node_representation(ast_node* c, ast_node* t, ast_node* e) : ternary(c, t, e) {};
            ast_node_representation(ast_node* l, ast_node* r) : binary(l, r) {};
            ast_node_representation(ast_node* o) : unary(o) {};
            ast_node_representation(const std::string& s) : id_or_string(s) {};
            ast_node_representation(int v) : number(v) {};
            ~ast_node_representation() {};
        } rep;
        ast_node_types label;
        registers mapping;

        public:
        ast_node(gerador::ast_node_types node_type, const std::vector<ast_node*>& commands) 
            : rep(commands), label(node_type), mapping(registers::ZERO) {};
        ast_node(gerador::ast_node_types node_type, const std::string& s, ast_node* v) 
            : rep(s, v), label(node_type), mapping(registers::ZERO) {};
        ast_node(gerador::ast_node_types node_type, const std::string& s, gerador::var_types r, 
            const std::vector<ast_node*>& p, const std::vector<ast_node*> v, const std::vector<ast_node*>& b) 
            : rep(s, r, p, v, b), label(node_type), mapping(registers::ZERO) {};
        ast_node(gerador::ast_node_types node_type, const std::string& s, gerador::var_types t) 
            : rep(s, t), label(node_type), mapping(registers::ZERO) {};
        ast_node(gerador::ast_node_types node_type, ast_node* i, ast_node* c, ast_node* inc, 
            const std::vector<ast_node*>& l) 
            : rep(i, c, inc, l), label(node_type), mapping(registers::ZERO) {};
        ast_node(gerador::ast_node_types node_type, ast_node* c, const std::vector<ast_node*>& l) 
            : rep(c, l), label(node_type), mapping(registers::ZERO) {};
        ast_node(gerador::ast_node_types node_type, ast_node* c, const std::vector<ast_node*>& t, 
            const std::vector<ast_node*>& e) 
            : rep(c, t, e), label(node_type), mapping(registers::ZERO) {};
        ast_node(gerador::ast_node_types node_type, const std::string& s, const std::vector<ast_node*>& p) 
            : rep(s, p), label(node_type), mapping(registers::ZERO) {};
        ast_node(gerador::ast_node_types node_type, ast_node* c, ast_node* t, ast_node* e) 
            : rep(c, t, e), label(node_type), mapping(registers::ZERO) {};
        ast_node(gerador::ast_node_types node_type, ast_node* l, ast_node* r) 
            : rep(l, r), label(node_type), mapping(registers::ZERO) {};
        ast_node(gerador::ast_node_types node_type, ast_node* o) 
            : rep(o), label(node_type), mapping(registers::ZERO) {};
        ast_node(gerador::ast_node_types node_type, const std::string& s) 
            : rep(s), label(node_type), mapping(registers::ZERO) {};
        ast_node(gerador::ast_node_types node_type, int v) 
            : rep(v), label(node_type), mapping(registers::ZERO) {};
        ~ast_node() {};

        ast_node& operator=(const ast_node& node);

        const ast_node_representation& get_rep() { return rep; };

        const ast_node_types get_label() { return label; };

        int get_number_value();

        int eval_array_size();

        void generate_code(gerador::instruction_set& is);
        
        inline const char* to_string();

        void visit(void (*routine)(gerador::ast_node&));

    };

    void declare_node_dot(gerador::ast_node& node);

    void declare_edge_dot(ast_node& node, const std::string& edge_label);

    void reset_index();
}

#endif