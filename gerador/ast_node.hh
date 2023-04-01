#ifndef AST_NODE_HH
#define AST_NODE_HH

#include <list>
#include <string>

namespace gerador {
    typedef void* param;
    
    enum var_type { VOID, CHAR, INT, CHAR_PTR, ARRAY_INT, ARRAY_CHAR_PTR };
    
    enum ast_node_types { 
        PROGRAM,                 /* PROGRAM  */
        /* DECLARATIONS */
        CONSTANT,                /* CONSTANT  */
        FUNCTION,                /* FUNCTION  */
        VAR,                     /* VAR  */

        /* CONTROL STRUCTURES */
        FOR,                     /* FOR  */
        WHILE,                   /* WHILE  */
        DO_WHILE,                /* DO_WHILE  */
        IF,                      /* IF  */

        /* VARIADIC OPERATORS */
        CALL,                    /* CALL  */
        PRINTF,                  /* PRINTF  */
        SCANF,                   /* SCANF  */
        
        /* TERNARY OPERATORS */
        TERNARY,                 
        
        /* BINARY OPERATORS */
        PLUS,                    /* PLUS  */
        MINUS,                   /* MINUS  */
        MULTIPLY,                /* MULTIPLY  */
        DIV,                     /* DIV  */
        REMAINDER,               /* REMAINDER  */
        BITWISE_AND,             /* BITWISE_AND  */
        BITWISE_OR,              /* BITWISE_OR  */
        BITWISE_XOR,             /* BITWISE_XOR  */
        LOGICAL_AND,             /* LOGICAL_AND  */
        LOGICAL_OR,              /* LOGICAL_OR  */
        EQUAL,                   /* EQUAL  */
        NOT_EQUAL,               /* NOT_EQUAL  */
        LESS_THAN,               /* LESS_THAN  */
        GREATER_THAN,            /* GREATER_THAN  */
        LESS_EQUAL,              /* LESS_EQUAL  */
        GREATER_EQUAL,           /* GREATER_EQUAL  */
        R_SHIFT,                 /* R_SHIFT  */
        L_SHIFT,                 /* L_SHIFT  */
        ASSIGN,                  /* ASSIGN  */
        ADD_ASSIGN,              /* ADD_ASSIGN  */
        MINUS_ASSIGN,            /* MINUS_ASSIGN  */

        /* UNARY OPERATORS */
        PRE_INC,                 /* INC  */
        PRE_DEC,                 /* DEC  */
        POST_INC,                /* PRE-INC  */
        POST_DEC,                /* POST-DEC  */
        BITWISE_NOT,             /* BITWISE_NOT  */
        REFERENCE,               /* REFERENCE  */
        DEFERENCE,             /* DEREFERENCE  */
        NEGATIVE,                /* NEGATIVE  */
        POSITIVE,                /* POSITIVE  */
        NOT,                     /* NOT  */
        EXIT,                    /* EXIT  */
        RETURN,                  /* RETURN  */

        /* ATOMIC */
        ID,                      /* ID  */
        DECIMAL,                 /* DECIMAL  */
        STRING,                  /* STRING  */
        CHARACTER                /* CHARACTER  */
    };

    struct ast_program { 
        std::list<param> commands; 

        ast_program(const std::list<param>& c) : commands(c) {};
        ~ast_program() {};
    };

    struct ast_constant { 
        std::string id; 
        gerador::var_type type;
        int value;

        ast_constant(const std::string& s, gerador::var_type t, int v) : id(s), type(t), value(v) {};
        ~ast_constant() {};
    };

    struct ast_function { 
        std::string id; 
        gerador::var_type return_type;
        std::list<param> params; 
        std::list<param> body;  
    
        ast_function(const std::string& s, gerador::var_type r, 
            std::list<param>& p, const std::list<param>& b)
            : id(s), return_type(r), params(p), body(b) {};
        ~ast_function() {};
    };

    struct ast_var { 
        std::string id; 
        gerador::var_type type; 
        
        ast_var(const std::string& s, gerador::var_type t) : id(s), type(t) {};
        ~ast_var() {};
    };

    /* ~ESTRUTURAS DE CONTROLE~ */
    struct ast_for { 
        param init; 
        param condition; 
        param increment; 
        std::list<param> loop; 

        ast_for(param i, param c, param inc, const std::list<param>& l) 
            : init(i), condition(c), increment(inc), loop(l) {};
        ~ast_for() {};
    };

    struct ast_while { 
        param condition; 
        std::list<param> loop; 

        ast_while(param c, const std::list<param>& l) : condition(c), loop(l) {};
        ~ast_while() {};
    };

    struct ast_if { 
        param condition; 
        std::list<param> then_body; 
        std::list<param> else_body; 

        ast_if(param c, const std::list<param>& t, const std::list<param>& e) 
            : condition(c), then_body(t), else_body(e) {};    
        ~ast_if() {};
    };

    /* ~OPERADORES VARIÁDICOS~ */
    struct ast_call { 
        std::string id; 
        std::list<param> params; 
        
        ast_call(const std::string& s, const std::list<param>& p) : id(s), params(p) {};
        ~ast_call() {};
    };

    /* ~OPERADORES TERNÁRIOS, BINÁRIOS E UNÁRIOS~ */
    struct ast_ternary { 
        param condition; 
        param then_body; 
        param else_body; 

        ast_ternary(param c, param t, param e) : condition(c), then_body(t), else_body(e) {};
        ~ast_ternary() {};
    };

    struct ast_binary { 
        param left; 
        param right; 
        
        ast_binary(param l, param r) : left(l), right(r) {};
        ~ast_binary() {};
    };

    struct ast_unary { 
        param operand; 

        ast_unary(param o) : operand(o) {};
        ~ast_unary() {};
    };

    /* ~ATÔMICOS~ */
    struct ast_text { 
        std::string id;

        ast_text(const std::string& s) : id(s) {};
        ~ast_text() {};
    };

    struct ast_decimal { 
        int value; 

        ast_decimal(int v) : value(v) {};
        ~ast_decimal() {};
    };

    struct ast_character { 
        char ch; 

        ast_character(char c) : ch(c) {};
        ~ast_character() {};
    };

    union ast_node_representation {
        ast_program _ast_program;

        /* ~DECLARAÇÕES~ */
        ast_constant _ast_constant;
        ast_function _ast_function;
        ast_var _ast_var;

        /* _~ESTRUTURAS DE CONTROLE~ */
        ast_for _ast_for;
        ast_while _ast_while;
        ast_if _ast_if;

        /* _~OPERADORES VARIÁDICOS~ */
        ast_call _ast_call;

        /* _~OPERADORES TERNÁRIOS, BINÁRIOS E UNÁRIOS~ */
        ast_ternary _ast_ternary;
        ast_binary _ast_binary;
        ast_unary _ast_unary;

        /* _~ATÔMICOS~ */
        ast_text _ast_text;
        ast_decimal _ast_decimal;
        ast_character _ast_character;

        ast_node_representation(const std::list<param>& commands) : _ast_program(commands) {};
        ast_node_representation(const std::string& s, gerador::var_type t, int v) : _ast_constant(s, t, v) {};
        ast_node_representation(const std::string& s, gerador::var_type r, 
            std::list<param>& p, const std::list<param>& b) : _ast_function(s, r, p, b) {};
        ast_node_representation(const std::string& s, gerador::var_type t) : _ast_var(s, t) {};
        ast_node_representation(param i, param c, param inc, const std::list<param>& l) : _ast_for(i, c, inc, l) {};
        ast_node_representation(param c, const std::list<param>& l) : _ast_while(c, l) {};
        ast_node_representation(param c, const std::list<param>& t, const std::list<param>& e) : _ast_if(c, t, e) {};
        ast_node_representation(const std::string& s, const std::list<param> p) : _ast_call(s, p) {};
        ast_node_representation(param c, param t, param e) : _ast_ternary(c, t, e) {};
        ast_node_representation(param l, param r) : _ast_binary(l, r) {};
        ast_node_representation(param o) : _ast_unary(o) {};
        ast_node_representation(const std::string& s) : _ast_text(s) {};
        ast_node_representation(int v) : _ast_decimal(v) {};
        ast_node_representation(char ch) : _ast_character(ch) {};
        ~ast_node_representation() {};
    };

    class ast_node { 
        ast_node_types label;
        ast_node_representation rep;

        public:
        ast_node(gerador::ast_node_types node_type, std::list<param>& commands) : rep(commands) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, std::string& s, 
            gerador::var_type t, int v) : rep(s, t, v) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, std::string& s, gerador::var_type r, 
            std::list<param>& p, const std::list<param>& b) : rep(s, r, p, b) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, const std::string& s, 
            gerador::var_type t) : rep(s, t) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, param i, param c, param inc, 
            const std::list<param>& l) : rep(i, c, inc, l) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, param c, const std::list<param>& l) : rep(c, l) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, param c, const std::list<param>& t, 
            const std::list<param>& e) : rep(c, t, e) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, const std::string& s, 
            const std::list<param>& p) : rep(s, p) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, param c, param t, param e) : rep(c, t, e) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, param l, param r) : rep(l, r) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, param o) : rep(o) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, const std::string& s) : rep(s) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, int v) : rep(v) {
            label = node_type;
        };
        ast_node(gerador::ast_node_types node_type, char ch) : rep(ch) {
            label = node_type;
        };
        ~ast_node() {};
    };
}

#endif