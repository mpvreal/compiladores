#ifndef AST_NODE_HH
#define AST_NODE_HH

#include <list>
#include <string>

namespace gerador {
    typedef void* param;
    
    enum var_type { VOID, CHAR, INT, CHAR_PTR, ARRAY_INT, ARRAY_CHAR_PTR };
    
    enum ast_node_types { 
        /* DECLARATIONS */
        CONSTANT,                /* CONSTANT  */
        GLOBAL_VAR,              /* GLOBAL_VAR  */
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

    struct ast_constant { std::string id; int value; };
    struct ast_global_var { std::string id; int value; };
    struct ast_function { std::string id; gerador::var_type return_type;
        std::list<param> params; std::list<param> body;  };
    struct ast_var { std::string id; gerador::var_type type; };

    /* ~ESTRUTURAS DE CONTROLE~ */
    struct ast_for { param init; param condition; param increment; 
        std::list<param> loop; };
    struct ast_while { param condition; std::list<param> loop; };
    struct ast_if { param condition; std::list<param> then_body; 
        std::list<param> else_body; };

    /* ~OPERADORES VARIÁDICOS~ */
    struct ast_call { std::string id; std::list<param> params; };
    struct ast_variadic { param format; std::list<param> params; };

    /* ~OPERADORES TERNÁRIOS, BINÁRIOS E UNÁRIOS~ */
    struct ast_ternary { param condition; param then_body; param else_body; };
    struct ast_binary { param left; param right; };
    struct ast_unary { param operand; };

    /* ~ATÔMICOS~ */
    struct ast_id { std::string id; int ptr_level; };
    struct ast_decimal { int value; };
    struct ast_string { std::string value; };
    struct ast_character { char value; };

    union ast_node_representation {
        /* ~DECLARAÇÕES~ */
        ast_constant _ast_constant;
        ast_global_var _ast_global_var;
        ast_function _ast_function;
        ast_var _ast_var;

        /* _~ESTRUTURAS DE CONTROLE~ */
        ast_for _ast_for;
        ast_while _ast_while;
        ast_if _ast_if;

        /* _~OPERADORES VARIÁDICOS~ */
        ast_call _ast_call;
        ast_variadic _ast_variadic;

        /* _~OPERADORES TERNÁRIOS, BINÁRIOS E UNÁRIOS~ */
        ast_ternary _ast_ternary;
        ast_binary _ast_binary;
        ast_unary _ast_unary;

        /* _~ATÔMICOS~ */
        ast_id _ast_id;
        ast_decimal _ast_decimal;
        ast_string _ast_string;
        ast_character _ast_character;

        ast_node_representation() {};
        ~ast_node_representation() {};
    };

    class ast_node { 
        ast_node_types label;
        ast_node_representation rep;

        public:
        ast_node(ast_node_types label, ast_node_representation& rep);
    };
}

#endif