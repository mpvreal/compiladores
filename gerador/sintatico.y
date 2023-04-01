%{

#include <list>
#include <map>
#include <string>

#include "ast.hh"
#include "context.hh"

extern int yylex();
extern int yyparse();
extern void yyerror(char*);

gerador::context ctx;

std::list<const void*> args;

void* to_access;

%}

%union {
    int decimal;
    const char* string;
    char character;
    void* ast_node;
    int ast_node_type;
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
%token<decimal> DECIMAL 
%token<string> STRING 
%token<character> CHARACTER

%type<ast_node> Program Declarations ConstantDeclaration GlobalVarDeclaration 
    FunctionDeclaration Literal Expression ReturnValue
    Arguments DeferenceLoop AmbiguousOperation Pointer 
    PrimitiveType TypeDeclaration If While DoWhile For Variadic Printf Scanf 
    Statement ParameterList VariableList Array StatementList Return

%type<boolean> ElseBlock

%type<ast_node_type> BOP UOP Postfix

%start Program

%%

Program
    : AstMarker SEPARATOR Declarations
    {
        $$ = new gerador::ast_node(gerador::ast_node_types::PROGRAM, 
            ctx.statements());
        ctx--;
    }
    ;

AstMarker
    : AST
    {
        ctx++;
    }
    ;

Declarations
    : ConstantDeclaration Declarations
    | GlobalVarDeclaration Declarations
    | FunctionDeclaration Declarations
    | %empty
    ;

ConstantDeclaration
    : CONSTANT COLON ID VALUE COLON Literal SEPARATOR
    ;

GlobalVarDeclaration
    : GLOBAL_VAR COLON ID TYPE COLON TypeDeclaration SEPARATOR
    ;

FunctionDeclaration
    : FUNCTION COLON ID SEPARATOR RETURN_TYPE COLON TypeDeclaration SEPARATOR 
        ParameterList VariableList StatementList SEPARATOR 
        END_FUNCTION OptionalSeparator
    ;

Literal
    : DECIMAL 
    {
        $$ = new gerador::ast_node(gerador::ast_node_types::DECIMAL, $1); 
    }
    | CHARACTER 
    {
        $$ = new gerador::ast_node(gerador::ast_node_types::CHARACTER, $1);
    }
    | STRING 
    {
        $$ = new gerador::ast_node(gerador::ast_node_types::STRING, std::string($1));
    }
    ;

Postfix
    : INC 
    {
        $$ = gerador::ast_node_types::POST_INC;
    }
    | DEC 
    {
        $$ = gerador::ast_node_types::POST_DEC;
    }
    ;

BOP
    : DIV 
    {
        $$ = gerador::ast_node_types::DIV;
    }
    | REMAINDER 
    {
        $$ = gerador::ast_node_types::REMAINDER;
    }
    | BITWISE_OR 
    {
        $$ = gerador::ast_node_types::BITWISE_OR;
    }
    | BITWISE_XOR 
    {
        $$ = gerador::ast_node_types::BITWISE_XOR;
    }
    | LOGICAL_AND 
    {
        $$ = gerador::ast_node_types::LOGICAL_AND;
    }
    | LOGICAL_OR 
    {
        $$ = gerador::ast_node_types::LOGICAL_OR;
    }
    | EQUAL 
    {
        $$ = gerador::ast_node_types::EQUAL;
    }
    | NOT_EQUAL 
    {
        $$ = gerador::ast_node_types::NOT_EQUAL;
    }
    | LESS_THAN 
    {
        $$ = gerador::ast_node_types::LESS_THAN;
    }
    | GREATER_THAN 
    { 
        $$ = gerador::ast_node_types::GREATER_THAN;
    }
    | LESS_EQUAL 
    {
        $$ = gerador::ast_node_types::LESS_EQUAL;
    }
    | GREATER_EQUAL 
    {
        $$ = gerador::ast_node_types::GREATER_EQUAL;
    }
    | R_SHIFT 
    {
        $$ = gerador::ast_node_types::R_SHIFT;
    }
    | L_SHIFT 
    {
        $$ = gerador::ast_node_types::L_SHIFT;
    }
    | ASSIGN 
    {
        $$ = gerador::ast_node_types::ASSIGN;
    }
    | ADD_ASSIGN 
    {
        $$ = gerador::ast_node_types::ADD_ASSIGN;
    }
    | MINUS_ASSIGN 
    {
        $$ = gerador::ast_node_types::MINUS_ASSIGN;
    }
    ;

UOP
    : Postfix 
    {
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
    | BITWISE_NOT 
    {
        $$ = gerador::ast_node_types::BITWISE_NOT;
    }
    | NOT 
    {
        $$ = gerador::ast_node_types::NOT;
    }
    | EXIT 
    {
        $$ = gerador::ast_node_types::EXIT;
    }
    ;

Expression
    : BOP L_PAREN Expression COMMA Expression R_PAREN 
    {
        $$ = new gerador::ast_node(static_cast<gerador::ast_node_types>($1), 
            $3, $5);
    }
    | UOP L_PAREN Expression R_PAREN 
    {
        $$ = new gerador::ast_node(static_cast<gerador::ast_node_types>($1), $3);
    }
    | MULTIPLY L_PAREN Expression AmbiguousOperation 
    {
        $$ = $4 == NULL
            ? new gerador::ast_node(gerador::ast_node_types::DEFERENCE, $3)
            : new gerador::ast_node(gerador::ast_node_types::MULTIPLY, $3, $4);
    }
    | MULTIPLY DeferenceLoop L_PAREN Expression R_PAREN
    | BITWISE_AND L_PAREN Expression AmbiguousOperation 
    {
        $$ = $4 == NULL
            ? new gerador::ast_node(gerador::ast_node_types::REFERENCE, $3)
            : new gerador::ast_node(gerador::ast_node_types::BITWISE_AND, $3, $4);
    }
    | PLUS L_PAREN Expression AmbiguousOperation 
    {
        $$ = $4 == NULL
            ? new gerador::ast_node(gerador::ast_node_types::POSITIVE, $3)
            : new gerador::ast_node(gerador::ast_node_types::PLUS, $3, $4);
    }
    | MINUS L_PAREN Expression AmbiguousOperation 
    {
        $$ = $4 == NULL
            ? new gerador::ast_node(gerador::ast_node_types::NEGATIVE, $3)
            : new gerador::ast_node(gerador::ast_node_types::MINUS, $3, $4);
    }
    | L_PAREN Expression R_PAREN Postfix 
    {
        $$ = new gerador::ast_node(static_cast<gerador::ast_node_types>($4), $2);
    }
    | TERNARY L_PAREN Expression COMMA Expression COMMA Expression R_PAREN 
    {
        $$ = new gerador::ast_node(gerador::ast_node_types::TERNARY, $3, $5, $7);
    }
    | ID Array 
    {
        if($2) {
            gerador::ast_node id(gerador::ast_node_types::ID, std::string($1));
            *((gerador::ast_node*) to_access) = id;
            $$ = $2;
        } else {
            $$ = new gerador::ast_node(gerador::ast_node_types::ID, std::string($1));
        }
    }
    | ID L_PAREN Arguments R_PAREN
    | Literal 
    {
        $$ = $1;
    }
    ;

Arguments
    : Expression Variadic
    | %empty
    ;

DeferenceLoop
    : DeferenceLoop MULTIPLY
    | MULTIPLY
    ;

AmbiguousOperation
    : R_PAREN 
    {
        $$ = NULL;
    }
    | COMMA Expression R_PAREN 
    {
        $$ = $2;
    }
    ;

Array
    : L_BRACKET Expression R_BRACKET Array
    {
        gerador::ast_node* address;
        if($4 == NULL) {
            gerador::ast_node* id = 
                new gerador::ast_node(gerador::ast_node_types::ID, std::string("BUFFER"));
            address = 
                new gerador::ast_node(gerador::ast_node_types::PLUS, id, $2);
            to_access = id;
        } else {
            address = 
                new gerador::ast_node(gerador::ast_node_types::PLUS, $4, $2);
        }

        $$ = new gerador::ast_node(gerador::ast_node_types::DEFERENCE, address);
    }
    | %empty 
    { 
        $$ = NULL; 
    }
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

ElseBlock
    : ElseMarker StatementList
    {
        ctx.statements().push_back($2);
        $$ = true;
    }
    | %empty
    {
        $$ = false;
    }
    ;

ElseMarker
    : COMMA
    {
        ctx++;
    }
    ;

If
    : IfMarker L_PAREN Expression COMMA StatementList ElseBlock R_PAREN
    {
        if($6) {
            std::list<const void*> buf = ctx.statements();
            ctx--;
            $$ = new gerador::ast_node(gerador::ast_node_types::IF, 
                $3, ctx.statements(), buf);
        } else {
            $$ = new gerador::ast_node(gerador::ast_node_types::IF, 
                $3, ctx.statements(), std::list<const void*>());
        }

        ctx--;
    }
    ;

IfMarker
    : IF
    {
        ctx++;
    }
    ;

While
    : WhileMarker L_PAREN Expression COMMA StatementList R_PAREN
    {
        $$ = new gerador::ast_node(gerador::ast_node_types::WHILE, $3,
            ctx.statements());
    }
    ;

WhileMarker
    : WHILE
    {
        ctx++;
    }
    ;

DoWhile
    : DoWhileMarker L_PAREN Expression COMMA StatementList R_PAREN
    {
        $$ = new gerador::ast_node(gerador::ast_node_types::DO_WHILE, $3,
            ctx.statements());
    }
    ;

DoWhileMarker
    : DO_WHILE
    {
        ctx++;
    }
    ;

For
    : ForMarker L_PAREN Expression COMMA Expression COMMA Expression COMMA StatementList R_PAREN
    {
        $$ = new gerador::ast_node(gerador::ast_node_types::FOR, $3, $5, $7,
            ctx.statements());
    }
    ;

ForMarker
    : FOR
    {
        ctx++;
    }
    ;

Return
    : RETURN L_PAREN ReturnValue
    {
        $$ = new gerador::ast_node(gerador::ast_node_types::RETURN, $3);
    }
    ;

ReturnValue
    : Expression R_PAREN { $$ = $1; }
    | R_PAREN { $$ = NULL; }
    ;

Variadic
    : COMMA Expression Variadic
    {
        args.push_back($2);
    }
    | %empty
    ;

Printf
    : PRINTF L_PAREN STRING Variadic R_PAREN
    {
        $$ = new gerador::ast_node(gerador::ast_node_types::PRINTF, 
            std::string("printf"), args);
        args.clear();
    }
    ;

Scanf
    : SCANF L_PAREN STRING Variadic R_PAREN 
    {
        $$ = new gerador::ast_node(gerador::ast_node_types::SCANF, std::string("scanf"), 
            args);
        args.clear();
    }
    ;

StatementList
    : StatementListContinuation Statement
    {
        ctx.statements().push_back($2);
    }
    ;

StatementListContinuation
    : StatementList SEPARATOR
    | %empty
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