%{

#include <list>
#include <map>
#include <string>

#include "ast.hh"
    
typedef std::map<std::string, void*> scope;

extern int yylex();
extern int yyparse();
extern void yyerror(char*);

std::list<void*> buffer_list;
std::list<std::list<void*>> buffer_stack;

struct context {
    std::list<scope> ctx_stack;
};

%}

%union {
    int decimal;
    const char* string;
    char character;
    void* ast_node;
    int ast_node_type;
}

%token VOID CHAR INT CONSTANT GLOBAL_VAR VAR TYPE FUNCTION END_FUNCTION 
    PARAMETER VALUE DO_WHILE IF WHILE FOR PRINTF SCANF EXIT RETURN 
    RETURN_TYPE PLUS MINUS MULTIPLY DIV REMAINDER BITWISE_AND 
    BITWISE_OR BITWISE_XOR LOGICAL_AND LOGICAL_OR EQUAL NOT_EQUAL 
    LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL R_SHIFT L_SHIFT 
    ASSIGN ADD_ASSIGN MINUS_ASSIGN INC DEC BITWISE_NOT NOT TERNARY 
    L_PAREN R_PAREN L_BRACKET R_BRACKET COLON SEPARATOR COMMA AST
    
%token<string> ID 
%token<decimal> DECIMAL 
%token<string> STRING 
%token<character> CHARACTER

%type<ast_node> Program Declarations ConstantDeclaration GlobalVarDeclaration 
    FunctionDeclaration Atomic Expression 
    Arguments DeferenceLoop AmbiguousOperation Pointer 
    PrimitiveType TypeDeclaration If While DoWhile For Variadic Printf Scanf 
    Statement ParameterList VariableList

%type<ast_node_type> BOP UOP Postfix

%start Program

%%

Program
    : AST SEPARATOR Declarations
    ;

Declarations
    : ConstantDeclaration Declarations
    | GlobalVarDeclaration Declarations
    | FunctionDeclaration Declarations
    | %empty
    ;

ConstantDeclaration
    : CONSTANT COLON ID VALUE COLON Atomic SEPARATOR
    ;

GlobalVarDeclaration
    : GLOBAL_VAR COLON ID TYPE COLON TypeDeclaration SEPARATOR
    ;

FunctionDeclaration
    : FUNCTION COLON ID SEPARATOR RETURN_TYPE COLON TypeDeclaration SEPARATOR 
        ParameterList VariableList StatementList SEPARATOR 
        END_FUNCTION OptionalSeparator
    ;

Atomic
    : ID Array 
/*    { NÃO FAÇO IDEIA COMO TRATAR ISSO KKKKKKKKKKKKKKKKKKKKKKKKKKK
        gerador::ast_node_representation n; n._ast_id = { std::string($1), 0 };
        $$ = new gerador::ast_node(gerador::ast_node_types::ID, n); 
    }*/
    | DECIMAL 
/*    { 
        gerador::ast_node_representation n; n._ast_decimal = { $1 };
        $$ = new gerador::ast_node(gerador::ast_node_types::DECIMAL, n); 
    }*/
    | CHARACTER 
/*    {
        gerador::ast_node_representation n; n._ast_character = { $1 };
        $$ = new gerador::ast_node(gerador::ast_node_types::CHARACTER, n);
    }*/
    | STRING 
/*    {
        gerador::ast_node_representation n; n._ast_string = { std::string($1) };
        $$ = new gerador::ast_node(gerador::ast_node_types::STRING, n);
    }*/
    ;

Postfix
    : INC 
/*    {
        $$ = gerador::ast_node_types::POST_INC;
    }*/
    | DEC 
/*    {
        $$ = gerador::ast_node_types::POST_DEC;
    }*/
    ;

BOP
    : DIV 
/*    {
        $$ = gerador::ast_node_types::DIV;
    }*/
    | REMAINDER 
/*    {
        $$ = gerador::ast_node_types::REMAINDER;
    }*/
    | BITWISE_OR 
/*    {
        $$ = gerador::ast_node_types::BITWISE_OR;
    }*/
    | BITWISE_XOR 
/*    {
        $$ = gerador::ast_node_types::BITWISE_XOR;
    }*/
    | LOGICAL_AND 
/*    {
        $$ = gerador::ast_node_types::LOGICAL_AND;
    }*/
    | LOGICAL_OR 
/*    {
        $$ = gerador::ast_node_types::LOGICAL_OR;
    }*/
    | EQUAL 
/*    {
        $$ = gerador::ast_node_types::EQUAL;
    }*/
    | NOT_EQUAL 
/*    {
        $$ = gerador::ast_node_types::NOT_EQUAL;
    }*/
    | LESS_THAN 
/*    {
        $$ = gerador::ast_node_types::LESS_THAN;
    }*/
    | GREATER_THAN 
/*    { 
        $$ = gerador::ast_node_types::GREATER_THAN;
    }*/
    | LESS_EQUAL 
/*    {
        $$ = gerador::ast_node_types::LESS_EQUAL;
    }*/
    | GREATER_EQUAL 
/*    {
        $$ = gerador::ast_node_types::GREATER_EQUAL;
    }*/
    | R_SHIFT 
/*    {
        $$ = gerador::ast_node_types::R_SHIFT;
    }*/
    | L_SHIFT 
/*    {
        $$ = gerador::ast_node_types::L_SHIFT;
    }*/
    | ASSIGN 
/*    {
        $$ = gerador::ast_node_types::ASSIGN;
    }*/
    | ADD_ASSIGN 
/*    {
        $$ = gerador::ast_node_types::ADD_ASSIGN;
    }*/
    | MINUS_ASSIGN 
/*    {
        $$ = gerador::ast_node_types::MINUS_ASSIGN;
    }*/
    ;

UOP
    : Postfix 
/*    {
        switch($1) {
            case gerador::ast_node_types::POST_INC:
                $$ = gerador::ast_node_types::PRE_INC;
                break;
            case gerador::ast_node_types::POST_DEC:
                $$ = gerador::ast_node_types::PRE_DEC;
                break;
            default:
                $$ = gerador::ast_node_types::PRE_DEC;
                break;
        }
    }*/
    | BITWISE_NOT 
/*    {
        $$ = gerador::ast_node_types::BITWISE_NOT;
    }*/
    | NOT 
/*    {
        $$ = gerador::ast_node_types::NOT;
    }*/
    | EXIT 
/*    {
        $$ = gerador::ast_node_types::EXIT;
    }*/
    ;

Expression
    : BOP L_PAREN Expression COMMA Expression R_PAREN 
/*    {
        gerador::ast_node_representation n; n._ast_binary = { $3, $5 };
        $$ = new gerador::ast_node(static_cast<gerador::ast_node_types>($1), n);
    }*/
    | UOP L_PAREN Expression R_PAREN 
/*    {
        gerador::ast_node_representation n; n._ast_unary = { $3 };
        $$ = new gerador::ast_node(static_cast<gerador::ast_node_types>($1), n);
    }*/
    | MULTIPLY L_PAREN Expression AmbiguousOperation 
/*    {
        if($4 == NULL) {
            gerador::ast_node_representation n; n._ast_unary = { $3 };
            $$ = new gerador::ast_node(gerador::ast_node_types::DEFERENCE, n);
        } else {
            gerador::ast_node_representation n; n._ast_binary = { $3, $4 };
            $$ = new gerador::ast_node(gerador::ast_node_types::MULTIPLY, n);
        }
    }*/
    | MULTIPLY DeferenceLoop L_PAREN Expression R_PAREN
    | BITWISE_AND L_PAREN Expression AmbiguousOperation 
/*    {
        if($4 == NULL) {
            gerador::ast_node_representation n; n._ast_unary = { $3 };
            $$ = new gerador::ast_node(gerador::ast_node_types::REFERENCE, n);
        } else {
            gerador::ast_node_representation n; n._ast_binary = { $3, $4 };
            $$ = new gerador::ast_node(gerador::ast_node_types::BITWISE_AND, n);
        }
    }*/
    | PLUS L_PAREN Expression AmbiguousOperation 
/*    {
        if($4 == NULL) {
            gerador::ast_node_representation n; n._ast_unary = { $3 };
            $$ = new gerador::ast_node(gerador::ast_node_types::PLUS, n);
        } else {
            gerador::ast_node_representation n; n._ast_binary = { $3, $4 };
            $$ = new gerador::ast_node(gerador::ast_node_types::PLUS, n);
        }
    }*/
    | MINUS L_PAREN Expression AmbiguousOperation 
/*    {
        if($4 == NULL) {
            gerador::ast_node_representation n; n._ast_unary = { $3 };
            $$ = new gerador::ast_node(gerador::ast_node_types::NEGATIVE, n);
        } else {
            gerador::ast_node_representation n; n._ast_binary = { $3, $4 };
            $$ = new gerador::ast_node(gerador::ast_node_types::MINUS, n);
        }
    }*/
    | L_PAREN Expression R_PAREN Postfix 
/*    {
        gerador::ast_node_representation n; n._ast_unary = { $2 };
        $$ = new gerador::ast_node(static_cast<gerador::ast_node_types>($4), n);
    }*/
    | TERNARY L_PAREN Expression COMMA Expression COMMA Expression R_PAREN 
/*    {
        gerador::ast_node_representation n; n._ast_ternary = { $3, $5, $7 };
        $$ = new gerador::ast_node(gerador::ast_node_types::TERNARY, n);
    }*/
    | ID L_PAREN Arguments R_PAREN 
    | Atomic 
/*    {
        $$ = $1;
    }*/
    ;

Arguments
    : Expression Variadic
    | %empty
    ;

/* StarOperation
    : L_PAREN Expression AmbiguousOperation
    | DeferenceLoop L_PAREN Expression R_PAREN
    ; */

DeferenceLoop
    : DeferenceLoop MULTIPLY
    | MULTIPLY
    ;

AmbiguousOperation
    : R_PAREN 
/*    {
        $$ = NULL;
    }*/
    | COMMA Expression R_PAREN 
/*    {
        $$ = $2;
    }*/
    ;

Array
    : Array L_BRACKET Expression R_BRACKET
    | %empty
    ;

Pointer
    : Pointer MULTIPLY
    | %empty
    ;

PrimitiveType
    : VOID | CHAR | INT
    ;

TypeDeclaration
    : PrimitiveType Pointer Array
    ;

ThenBlock
    : COMMA StatementList
    | %empty
    ;

If
    : IF L_PAREN Expression COMMA StatementList ThenBlock R_PAREN
    ;

While
    : WHILE L_PAREN Expression COMMA StatementList R_PAREN
    ;

DoWhile
    : DO_WHILE L_PAREN Expression COMMA StatementList R_PAREN
    ;

For
    : FOR L_PAREN Expression COMMA Expression COMMA Expression COMMA StatementList R_PAREN
    ;

Return
    : RETURN L_PAREN ReturnValue
    ;

ReturnValue
    : Expression R_PAREN
    | R_PAREN
    ;

Variadic
    : COMMA Expression Variadic
    | %empty
    ;

Printf
    : PRINTF L_PAREN STRING Variadic R_PAREN
    ;

Scanf
    : SCANF L_PAREN STRING Variadic R_PAREN
    ;

StatementList
    : StatementListContinuation Statement
    ;

StatementListContinuation
    : StatementList SEPARATOR
    | %empty
    ;

Statement
    : If 
    | While 
    | DoWhile 
    | For 
    | Printf 
    | Scanf 
    | Expression
    | Return
    ;

ParameterList
    : ParameterList PARAMETER COLON ID TYPE COLON TypeDeclaration SEPARATOR
    | %empty
    ;

VariableList
    : VariableList VAR COLON ID TYPE COLON TypeDeclaration SEPARATOR
    | %empty
    ;

OptionalSeparator
    : SEPARATOR
    | %empty
    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "ERROR: %s");
}

int main(int argc, char **argv) {
    #ifdef YYDEBUG
        yydebug = 1;
    #endif

    yyparse();
 
    return 0;
}