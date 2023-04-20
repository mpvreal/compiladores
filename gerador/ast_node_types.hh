#ifndef AST_NODE_TYPES_HH
#define AST_NODE_TYPES_HH

namespace gerador {
    enum ast_node_types { 
        PROGRAM,                 
        CONSTANT,                
        FUNCTION,                
        VAR,                     
        GLOBAL_VAR,
        PARAM,                   
        FOR,                     
        WHILE,                   
        DO_WHILE,                
        IF,                      
        CALL,                    
        PRINTF,                  
        SCANF,                   
        TERNARY,                 
        PLUS,                    
        MINUS,                   
        MULTIPLY,                
        DIVISION,                     
        REMAINDER,               
        BITWISE_AND,             
        BITWISE_OR,              
        BITWISE_XOR,             
        LOGICAL_AND,             
        LOGICAL_OR,              
        EQUAL,                   
        NOT_EQUAL,               
        LESS_THAN,               
        GREATER_THAN,            
        LESS_EQUAL,              
        GREATER_EQUAL,           
        R_SHIFT,                 
        L_SHIFT,                 
        ASSIGN,                  
        ADD_ASSIGN,              
        MINUS_ASSIGN,            
        PRE_INC,                 
        PRE_DEC,                 
        POST_INC,                
        POST_DEC,                
        BITWISE_NOT,             
        REFERENCE,               
        DEFERENCE,             
        NEGATIVE,                
        POSITIVE,                
        NOT,                     
        EXIT,                    
        RETURN,                  
        ID,                      
        NUMBER,                 
        STRING,                  
        CHARACTER                
    };
}

#endif