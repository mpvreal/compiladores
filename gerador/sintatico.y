%{
#include "ast.hh"
#include "context.hh"

extern int yylex();
extern int yyparse();
extern void yyerror(char*);

gerador::ast program;

std::list<const void*> args;
void* to_access;
%}

%union {
    const char* string;
    void* ast_node;
    int number;
    int enum_type;
    char character;
    bool boolean;
}

%token VOID CHAR INT CONSTANT GLOBAL_VAR VAR TYPE FUNCTION END_FUNCTION 
    PARAMETER VALUE DO_WHILE IF WHILE FOR PRINTF SCANF EXIT RETURN 
    RETURN_TYPE PLUS MINUS MULTIPLY DIV REMAINDER BITWISE_AND 
    BITWISE_OR BITWISE_XOR LOGICAL_AND LOGICAL_OR EQUAL NOT_EQUAL 
    LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL R_SHIFT L_SHIFT 
    ASSIGN ADD_ASSIGN MINUS_ASSIGN INC DEC BITWISE_NOT NOT TERNARY 
    L_PAREN R_PAREN L_BRACKET R_BRACKET COLON SEPARATOR COMMA AST
%token<string> ID 
%token<string> STRING 
%token<number> NUMBER 
%token<character> CHARACTER

%type<ast_node> Program Declarations ConstantDeclaration GlobalVarDeclaration 
    FunctionDeclaration Literal Expression ReturnValue Arguments DeferenceLoop 
    AmbiguousOperation If While DoWhile For VariableList ElseBlock
    Variadic Printf Scanf Statement ParameterList Array StatementList 
    Return StatementListContinuation
%type<enum_type> BOP UOP Postfix TypeDeclaration PrimitiveType
%type<boolean> Pointer

%start Program

%%

Program
    : AST SEPARATOR Declarations {
        $$ = new gerador::ast_node(gerador::ast_node_types::PROGRAM, 
            *((std::list<const void*>*) $3));
        delete (std::list<const void*>*) $3;
        program.set_program((gerador::ast_node*) $$);
    }
    ;

Declarations
    : ConstantDeclaration Declarations {
        ((std::list<const void*>*) $2)->push_front($1);
        $$ = $2;
    }
    | GlobalVarDeclaration Declarations {
        ((std::list<const void*>*) $2)->push_front($1);
        $$ = $2;
    }
    | FunctionDeclaration Declarations {
        ((std::list<const void*>*) $2)->push_front($1);
        $$ = $2;
    }
    | %empty { $$ = new std::list<const void*>(); }
    ;

ConstantDeclaration
    : CONSTANT COLON ID VALUE COLON Literal SEPARATOR {
        $$ = new gerador::ast_node(
            gerador::ast_node_types::CONSTANT, std::string($3), (const void*) $6);
    }
    ;

GlobalVarDeclaration
    : GLOBAL_VAR COLON ID TYPE COLON TypeDeclaration SEPARATOR {
        $$ = new gerador::ast_node(gerador::ast_node_types::VAR, 
            std::string($3), static_cast<gerador::var_types>($6));
    }
    ;

FunctionDeclaration
    : FUNCTION COLON ID SEPARATOR RETURN_TYPE COLON TypeDeclaration SEPARATOR 
        ParameterList VariableList StatementList SEPARATOR 
        END_FUNCTION OptionalSeparator {
        $$ = new gerador::ast_node(gerador::ast_node_types::FUNCTION, 
            std::string($3), static_cast<gerador::var_types>($7), *((std::list<const void*>*) $10), 
            *((std::list<const void*>*) $11));
        delete (std::list<const void*>*) $10;
    }
    ;

Literal
    : NUMBER {
        $$ = new gerador::ast_node(gerador::ast_node_types::NUMBER, $1); 
    }
    | CHARACTER {
        $$ = new gerador::ast_node(gerador::ast_node_types::CHARACTER, $1);
    }
    | STRING {
        $$ = new gerador::ast_node(gerador::ast_node_types::STRING, 
            std::string($1));
    }
    ;

Postfix
    : INC {
        $$ = gerador::ast_node_types::POST_INC;
    }
    | DEC {
        $$ = gerador::ast_node_types::POST_DEC;
    }
    ;

BOP
    : DIV {
        $$ = gerador::ast_node_types::DIV;
    }
    | REMAINDER {
        $$ = gerador::ast_node_types::REMAINDER;
    }
    | BITWISE_OR {
        $$ = gerador::ast_node_types::BITWISE_OR;
    }
    | BITWISE_XOR {
        $$ = gerador::ast_node_types::BITWISE_XOR;
    }
    | LOGICAL_AND {
        $$ = gerador::ast_node_types::LOGICAL_AND;
    }
    | LOGICAL_OR {
        $$ = gerador::ast_node_types::LOGICAL_OR;
    }
    | EQUAL {
        $$ = gerador::ast_node_types::EQUAL;
    }
    | NOT_EQUAL {
        $$ = gerador::ast_node_types::NOT_EQUAL;
    }
    | LESS_THAN {
        $$ = gerador::ast_node_types::LESS_THAN;
    }
    | GREATER_THAN { 
        $$ = gerador::ast_node_types::GREATER_THAN;
    }
    | LESS_EQUAL {
        $$ = gerador::ast_node_types::LESS_EQUAL;
    }
    | GREATER_EQUAL {
        $$ = gerador::ast_node_types::GREATER_EQUAL;
    }
    | R_SHIFT {
        $$ = gerador::ast_node_types::R_SHIFT;
    }
    | L_SHIFT {
        $$ = gerador::ast_node_types::L_SHIFT;
    }
    | ASSIGN {
        $$ = gerador::ast_node_types::ASSIGN;
    }
    | ADD_ASSIGN {
        $$ = gerador::ast_node_types::ADD_ASSIGN;
    }
    | MINUS_ASSIGN {
        $$ = gerador::ast_node_types::MINUS_ASSIGN;
    }
    ;

UOP
    : Postfix {
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
    }
    | BITWISE_NOT {
        $$ = gerador::ast_node_types::BITWISE_NOT;
    }
    | NOT {
        $$ = gerador::ast_node_types::NOT;
    }
    | EXIT {
        $$ = gerador::ast_node_types::EXIT;
    }
    ;

Expression
    : BOP L_PAREN Expression COMMA Expression R_PAREN {
        $$ = new gerador::ast_node(static_cast<gerador::ast_node_types>($1), 
            $3, $5);
    }
    | UOP L_PAREN Expression R_PAREN {
        $$ = new gerador::ast_node(static_cast<gerador::ast_node_types>($1), $3);
    }
    | MULTIPLY L_PAREN Expression AmbiguousOperation {
        $$ = $4 == NULL
            ? new gerador::ast_node(gerador::ast_node_types::DEFERENCE, $3)
            : new gerador::ast_node(gerador::ast_node_types::MULTIPLY, $3, $4);
    }
    | MULTIPLY DeferenceLoop L_PAREN Expression R_PAREN {
        $$ = $2;
        *((gerador::ast_node*) $2) = *((gerador::ast_node*) $4);
    }
    | BITWISE_AND L_PAREN Expression AmbiguousOperation {
        $$ = $4 == NULL
            ? new gerador::ast_node(gerador::ast_node_types::REFERENCE, $3)
            : new gerador::ast_node(gerador::ast_node_types::BITWISE_AND, $3, $4);
    }
    | PLUS L_PAREN Expression AmbiguousOperation {
        $$ = $4 == NULL
            ? new gerador::ast_node(gerador::ast_node_types::POSITIVE, $3)
            : new gerador::ast_node(gerador::ast_node_types::PLUS, $3, $4);
    }
    | MINUS L_PAREN Expression AmbiguousOperation {
        $$ = $4 == NULL
            ? new gerador::ast_node(gerador::ast_node_types::NEGATIVE, $3)
            : new gerador::ast_node(gerador::ast_node_types::MINUS, $3, $4);
    }
    | L_PAREN Expression R_PAREN Postfix {
        $$ = new gerador::ast_node(static_cast<gerador::ast_node_types>($4), $2);
    }
    | TERNARY L_PAREN Expression COMMA Expression COMMA Expression R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::TERNARY, $3, $5, $7);
    }
    | ID Array {
        if($2) {
            gerador::ast_node id(gerador::ast_node_types::ID, std::string($1));
            *((gerador::ast_node*) to_access) = id;
            $$ = $2;
        } else {
            $$ = new gerador::ast_node(gerador::ast_node_types::ID, std::string($1));
        }
    }
    | ID L_PAREN Arguments R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::CALL, std::string($1), $3);
    }
    | Literal { $$ = $1; }
    ;

Arguments
    : Expression Variadic {
        ((std::list<const void*>*) $2)->push_front($1);
        $$ = $2;
    }
    | %empty {
        $$ = new std::list<const void*>();
    }
    ;

DeferenceLoop
    : DeferenceLoop MULTIPLY {
        $$ = new gerador::ast_node(gerador::ast_node_types::DEFERENCE, $1);
    }
    | MULTIPLY {
        gerador::ast_node* buf = new gerador::ast_node(
            gerador::ast_node_types::NOT, (const void*) 0); 
        to_access = buf;
        $$ = new gerador::ast_node(gerador::ast_node_types::DEFERENCE, buf);
    }
    ;

AmbiguousOperation
    : R_PAREN {
        $$ = NULL;
    }
    | COMMA Expression R_PAREN {
        $$ = $2;
    }
    ;

Array
    : L_BRACKET Expression R_BRACKET Array {
        gerador::ast_node* address;
        if($4 == NULL) {
            gerador::ast_node* id = new gerador::ast_node(
                gerador::ast_node_types::ID, std::string("BUFFER"));
            address = 
                new gerador::ast_node(gerador::ast_node_types::PLUS, id, $2);
            to_access = id;
        } else {
            address = 
                new gerador::ast_node(gerador::ast_node_types::PLUS, $4, $2);
        }

        $$ = new gerador::ast_node(gerador::ast_node_types::DEFERENCE, address);
    }
    | %empty { 
        $$ = NULL; 
    }
    ;

Pointer
    : Pointer MULTIPLY {
        $$ = true;
    }
    | %empty {
        $$ = false;
    }
    ;

PrimitiveType
    : VOID { $$ = gerador::var_types::VOID; }
    | CHAR { $$ = gerador::var_types::CHAR; }
    | INT { $$ = gerador::var_types::INT; }
    ;

TypeDeclaration
    : PrimitiveType Pointer Array {
        $$ = $2 
            ? gerador::var_types::POINTER
            : $1;
    }
    ;

ElseBlock
    : COMMA StatementList {
        $$ = $2;
    }
    | %empty { $$ = new std::list<const void*>(); }
    ;

If
    : IF L_PAREN Expression COMMA StatementList ElseBlock R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::IF, $3, 
            *((std::list<const void*>*) $5), *((std::list<const void*>*) $6));
        delete (std::list<const void*>*) $5;
        delete (std::list<const void*>*) $6;
    }
    ;

While
    : WHILE L_PAREN Expression COMMA StatementList R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::WHILE, $3,
            *((std::list<const void*>*) $5));
    }
    ;

DoWhile
    : DO_WHILE L_PAREN Expression COMMA StatementList R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::DO_WHILE, $3,
            *((std::list<const void*>*) $5));
    }
    ;

For
    : FOR L_PAREN Expression COMMA Expression COMMA Expression COMMA StatementList R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::FOR, $3, $5, $7,
            *((std::list<const void*>*) $9));
    }
    ;

Return
    : RETURN L_PAREN ReturnValue {
        $$ = new gerador::ast_node(gerador::ast_node_types::RETURN, $3);
    }
    ;

ReturnValue
    : Expression R_PAREN { $$ = $1; }
    | R_PAREN { $$ = NULL; }
    ;

Variadic
    : COMMA Expression Variadic {
        ((std::list<const void*>*) $3)->push_front($2);
        $$ = $3;
    }
    | %empty { $$ = new std::list<const void*>(); }
    ;

Printf
    : PRINTF L_PAREN STRING Variadic R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::PRINTF, 
            std::string("printf"), args);
        args.clear();
    }
    ;

Scanf
    : SCANF L_PAREN STRING Variadic R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::SCANF, 
            std::string("scanf"), args);
        args.clear();
    }
    ;

StatementList
    : StatementListContinuation Statement {
        ((std::list<const void*>*) $1)->push_front($2);
        $$ = $1;
    }
    ;

StatementListContinuation
    : StatementList SEPARATOR { $$ = $1; }
    | %empty { $$ = new std::list<const void*>(); }
    ;

Statement
    : If { $$ = $1; }
    | While { $$ = $1; }
    | DoWhile { $$ = $1; }
    | For { $$ = $1; }
    | Printf { $$ = $1; }
    | Scanf { $$ = $1; }
    | Expression { $$ = $1; }
    | Return { $$ = $1; }
    ;

ParameterList
    : PARAMETER COLON ID TYPE COLON TypeDeclaration SEPARATOR ParameterList {
        ((std::list<const void*>*) $8)->
            push_front(new gerador::ast_node(gerador::ast_node_types::PARAM, 
            std::string($3), static_cast<gerador::var_types>($6)));
        $$ = $8;
    }
    | %empty { $$ = new std::list<const void*>(); }
    ;

VariableList
    : VAR COLON ID TYPE COLON TypeDeclaration SEPARATOR VariableList {
        ((std::list<const void*>*) $8)->
            push_front(new gerador::ast_node(gerador::ast_node_types::VAR, 
            std::string($3), static_cast<gerador::var_types>($6)));
        $$ = $8;
    }
    | %empty { $$ = new std::list<const void*>; }
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