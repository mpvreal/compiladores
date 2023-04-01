%{

#include <list>
#include <map>
#include <string>

#include "ast.hh"

extern int yylex();
extern int yyparse();
extern void yyerror(char*);
    
typedef std::map<std::string, void*> scope;

struct context {
    std::list<scope> ctx_stack;
};

std::list<void*> buffer_list;
std::list<std::list<void*>> block_stack;
// std::list<std::list<void*>> then_stack;

std::list<void*> args;
void** mamaco = NULL;

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
    FunctionDeclaration Literal Expression ReturnValue
    Arguments DeferenceLoop AmbiguousOperation Pointer 
    PrimitiveType TypeDeclaration If While DoWhile For Variadic Printf Scanf 
    Statement ParameterList VariableList Array StatementList Return ThenBlock

%type<ast_node_type> BOP UOP Postfix

%start Program

%%

Program
    : AstMarker SEPARATOR Declarations
    {
        gerador::ast_node_representation n; n._ast_program = { block_stack.back() };
        $$ = new gerador::ast_node(gerador::ast_node_types::PROGRAM, n);
        block_stack.pop_back();
    }
    ;

AstMarker
    : AST
    {
        block_stack.push_back(std::list<void*>());
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
        gerador::ast_node_representation n; n._ast_decimal = { $1 };
        $$ = new gerador::ast_node(gerador::ast_node_types::DECIMAL, n); 
    }
    | CHARACTER 
   {
        gerador::ast_node_representation n; n._ast_character = { $1 };
        $$ = new gerador::ast_node(gerador::ast_node_types::CHARACTER, n);
    }
    | STRING 
   {
        gerador::ast_node_representation n; n._ast_string = { std::string($1) };
        $$ = new gerador::ast_node(gerador::ast_node_types::STRING, n);
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
        gerador::ast_node_representation n; n._ast_binary = { $3, $5 };
        $$ = new gerador::ast_node(static_cast<gerador::ast_node_types>($1), n);
    }
    | UOP L_PAREN Expression R_PAREN 
   {
        gerador::ast_node_representation n; n._ast_unary = { $3 };
        $$ = new gerador::ast_node(static_cast<gerador::ast_node_types>($1), n);
    }
    | MULTIPLY L_PAREN Expression AmbiguousOperation 
   {
        if($4 == NULL) {
            gerador::ast_node_representation n; n._ast_unary = { $3 };
            $$ = new gerador::ast_node(gerador::ast_node_types::DEFERENCE, n);
        } else {
            gerador::ast_node_representation n; n._ast_binary = { $3, $4 };
            $$ = new gerador::ast_node(gerador::ast_node_types::MULTIPLY, n);
        }
    }
    | MULTIPLY DeferenceLoop L_PAREN Expression R_PAREN
    | BITWISE_AND L_PAREN Expression AmbiguousOperation 
   {
        if($4 == NULL) {
            gerador::ast_node_representation n; n._ast_unary = { $3 };
            $$ = new gerador::ast_node(gerador::ast_node_types::REFERENCE, n);
        } else {
            gerador::ast_node_representation n; n._ast_binary = { $3, $4 };
            $$ = new gerador::ast_node(gerador::ast_node_types::BITWISE_AND, n);
        }
    }
    | PLUS L_PAREN Expression AmbiguousOperation 
   {
        if($4 == NULL) {
            gerador::ast_node_representation n; n._ast_unary = { $3 };
            $$ = new gerador::ast_node(gerador::ast_node_types::PLUS, n);
        } else {
            gerador::ast_node_representation n; n._ast_binary = { $3, $4 };
            $$ = new gerador::ast_node(gerador::ast_node_types::PLUS, n);
        }
    }
    | MINUS L_PAREN Expression AmbiguousOperation 
   {
        if($4 == NULL) {
            gerador::ast_node_representation n; n._ast_unary = { $3 };
            $$ = new gerador::ast_node(gerador::ast_node_types::NEGATIVE, n);
        } else {
            gerador::ast_node_representation n; n._ast_binary = { $3, $4 };
            $$ = new gerador::ast_node(gerador::ast_node_types::MINUS, n);
        }
    }
    | L_PAREN Expression R_PAREN Postfix 
   {
        gerador::ast_node_representation n; n._ast_unary = { $2 };
        $$ = new gerador::ast_node(static_cast<gerador::ast_node_types>($4), n);
    }
    | TERNARY L_PAREN Expression COMMA Expression COMMA Expression R_PAREN 
   {
        gerador::ast_node_representation n; n._ast_ternary = { $3, $5, $7 };
        $$ = new gerador::ast_node(gerador::ast_node_types::TERNARY, n);
    }
    | ID Array 
    {
        if($2) {
            gerador::ast_node_representation n; n._ast_id = {};
            n._ast_id.id.assign($1);
            gerador::ast_node* buf = (gerador::ast_node*) *mamaco;
            buf->rep._ast_unary.operand 
                = new gerador::ast_node(gerador::ast_node_types::ID, n);
            $$ = $2;
        } else {
            // gerador::ast_node_representation n; n._ast_id = { $1 };
            // $$ = new gerador::ast_node(gerador::ast_node_types::ID, n);
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
        gerador::ast_node_representation n; n._ast_binary = { $2, $4 };
        void* buf = new gerador::ast_node(gerador::ast_node_types::PLUS, n);
        n._ast_unary = { buf };
        $$ = new gerador::ast_node(gerador::ast_node_types::DEFERENCE, n);
        if($4 == NULL) {
            mamaco = &$$;
        }
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

ThenBlock
    : ThenMarker StatementList
    {
        block_stack.back().push_back($2);
        $$ = (void*) 1;
    }
    | %empty
    {
        $$ = NULL;
    }
    ;

ThenMarker
    : COMMA
    {
        block_stack.push_back(std::list<void*>());
    }
    ;

If
    : IfMarker L_PAREN Expression COMMA StatementList ThenBlock R_PAREN
    {
        std::list<void*> buf = block_stack.back();
        gerador::ast_node_representation n; n._ast_if = {};

        if($6 != NULL) {
            block_stack.pop_back();
            std::list<void*> buf_2 = block_stack.back();
            n._ast_if.condition = $3;
            n._ast_if.then_body = buf; 
            n._ast_if.else_body = buf_2;
        } else {
            n._ast_if.condition = $3;
            n._ast_if.then_body = buf; 
            n._ast_if.else_body = std::list<void*>();
        }
        block_stack.pop_back();

        $$ = new gerador::ast_node(gerador::ast_node_types::IF, n);
    }
    ;

IfMarker
    : IF
    {
        block_stack.push_back(std::list<void*>());
    }
    ;

While
    : WhileMarker L_PAREN Expression COMMA StatementList R_PAREN
    {
        std::list<void*> buf = block_stack.back();
        block_stack.pop_back();

        gerador::ast_node_representation n; n._ast_while = {}; //{ $3, buf };
        n._ast_while.condition = $3;
        n._ast_while.loop = buf;

        $$ = new gerador::ast_node(gerador::ast_node_types::WHILE, n);
    }
    ;

WhileMarker
    : WHILE
    {
        block_stack.push_back(std::list<void*>());
    }
    ;

DoWhile
    : DoWhileMarker L_PAREN Expression COMMA StatementList R_PAREN
    {
        std::list<void*> buf = block_stack.back();
        block_stack.pop_back();

        gerador::ast_node_representation n; n._ast_while = {}; // = { $3, buf };
        n._ast_while.condition = $3;
        n._ast_while.loop = buf;

        $$ = new gerador::ast_node(gerador::ast_node_types::DO_WHILE, n);
    }
    ;

DoWhileMarker
    : DO_WHILE
    {
        block_stack.push_back(std::list<void*>());
    }
    ;

For
    : ForMarker L_PAREN Expression COMMA Expression COMMA Expression COMMA StatementList R_PAREN
    {
        std::list<void*> buf = block_stack.back();
        block_stack.pop_back();

        gerador::ast_node_representation n; n._ast_for = {}; //{ $3, $5, $7, buf };
        n._ast_for.init = $3;
        n._ast_for.condition = $5;
        n._ast_for.increment = $7;
        n._ast_for.loop = buf;

        $$ = new gerador::ast_node(gerador::ast_node_types::FOR, n);
    }
    ;

ForMarker
    : FOR
    {
        block_stack.push_back(std::list<void*>());
    }
    ;

Return
    : RETURN L_PAREN ReturnValue
    {
        gerador::ast_node_representation n; n._ast_unary = { $3 };
        $$ = new gerador::ast_node(gerador::ast_node_types::RETURN, n);
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
        gerador::ast_node_representation n; n._ast_variadic = { $3, std::list<void*>(args) };
        $$ = new gerador::ast_node(gerador::ast_node_types::PRINTF, n);
        args.clear();
    }
    ;

Scanf
    : SCANF L_PAREN STRING Variadic R_PAREN 
    {
        gerador::ast_node_representation n; n._ast_variadic = { std::string($3), std::list<void*>(args) };
        $$ = new gerador::ast_node(gerador::ast_node_types::SCANF, n);
        args.clear();
    }
    ;

StatementList
    : StatementListContinuation Statement
    {
        $$ = $2;
        if($2 != NULL) {
            block_stack.back().push_back($2);
        }
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