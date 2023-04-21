%{
#include <cstring>
#include <iostream>

#include "ast.hh"

extern int yylex();
extern int yyparse();
extern void yyerror(char*);

gerador::ast program;
gerador::instruction_set is;

static std::map<std::string, std::vector<int>> array_map;
static std::vector<gerador::ast_node*>* current_array;
static gerador::ast_node* to_access;
static int current_type_size = 1;
static int array_size = 1;
%}

%union {
    std::vector<gerador::ast_node*>* ast_node_list;
    gerador::ast_node* ast_node;
    gerador::var_types var_type;
    gerador::ast_node_types ast_node_type;
    char string[256];
    char character;
    int number;
    bool boolean;
}

%token VOID CHAR INT CONSTANT GLOBAL_VAR VAR TYPE FUNCTION END_FUNCTION 
    PARAMETER VALUE DO_WHILE IF WHILE FOR EXIT RETURN 
    RETURN_TYPE PLUS MINUS MULTIPLY DIV REMAINDER BITWISE_AND 
    BITWISE_OR BITWISE_XOR LOGICAL_AND LOGICAL_OR EQUAL NOT_EQUAL 
    LESS_THAN GREATER_THAN LESS_EQUAL GREATER_EQUAL R_SHIFT L_SHIFT 
    ASSIGN ADD_ASSIGN MINUS_ASSIGN INC DEC BITWISE_NOT NOT TERNARY 
    L_PAREN R_PAREN L_BRACKET R_BRACKET COLON SEPARATOR COMMA AST
%token<string> ID 
%token<string> STRING 
%token<number> NUMBER 
%token<character> CHARACTER

%type<ast_node_list> Declarations Arguments ElseBlock Variadic StatementListContinuation
    ParameterList VariableList StatementList Array
%type<ast_node> Program ConstantDeclaration GlobalVarDeclaration FunctionDeclaration Return
    Literal Expression ReturnValue DeferenceLoop AmbiguousOperation If While DoWhile For Statement    
%type<ast_node_type> Postfix BOP UOP
/* %type<string> IdAccess */
%type<var_type> TypeDeclaration PrimitiveType
%type<boolean> Pointer

%start Program

%%

Program
    : AST SEPARATOR Declarations {
        $$ = new gerador::ast_node(gerador::ast_node_types::PROGRAM, *$3);
        delete $3;
        program.set_program($$);
    }
    ;

Declarations
    : Declarations ConstantDeclaration {
        $1->push_back($2);
        $$ = $1;
    }
    | Declarations GlobalVarDeclaration {
        $1->push_back($2);
        $$ = $1;
    }
    | Declarations FunctionDeclaration {
        $1->push_back($2);
        $$ = $1;
    }
    | %empty { $$ = new std::vector<gerador::ast_node*>(); }
    ;

ConstantDeclaration
    : CONSTANT COLON ID VALUE COLON Literal SEPARATOR {
        $$ = new gerador::ast_node(
            gerador::ast_node_types::CONSTANT, std::string($3), $6);

        // is.add_const($3, $6->get_number_value());

        // delete $6;
    }
    ;

GlobalVarDeclaration
    : GLOBAL_VAR COLON ID TYPE COLON TypeDeclaration SEPARATOR {
        int size = 1;
        if(current_array != nullptr) {    
            std::vector<int> dimension_products;
            int product = 1;
            
            for(int k = 0; k < current_array->size(); k++) {
                for(int l = k + 1; l < current_array->size(); l++) {
                    product *= (*current_array)[l]->get_number_value();
                }
                size *= (*current_array)[k]->get_number_value();
                dimension_products.push_back(product);
                product = 1;
            }

            // std::cout << "dimension_products = " << std::endl;
            // for(auto& i : dimension_products) {
            //     std::cout << i << ' ';
            // }

            array_map.insert({std::string($3), dimension_products});
        }
        $$ = new gerador::ast_node(gerador::ast_node_types::GLOBAL_VAR, 
            std::string($3), $6);
        is.add_global_var($3, $6, is.offset());
        is.add_data($3, gerador::global_type::SPACE, 
            size * 4);
    }
    ;

FunctionDeclaration
    : FUNCTION COLON ID SEPARATOR RETURN_TYPE COLON TypeDeclaration SEPARATOR 
        ParameterList VariableList StatementList SEPARATOR 
        END_FUNCTION OptionalSeparator {
        $$ = new gerador::ast_node(gerador::ast_node_types::FUNCTION, 
            std::string($3), $7, *$9, 
            *$10, *$11);
        delete $10;
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
        $$ = gerador::ast_node_types::DIVISION;
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
        if($1 >= gerador::ast_node_types::ASSIGN && $1 <= gerador::ast_node_types::MINUS_ASSIGN) {
            if($3->get_label() == gerador::ast_node_types::DEFERENCE) {
                $1 = static_cast<gerador::ast_node_types>(static_cast<int>($1) + static_cast<int>(gerador::ast_node_types::STORE) - static_cast<int>(gerador::ast_node_types::ASSIGN));
                $3 = $3->bypass_deference();
            }
        }
        $$ = new gerador::ast_node($1, $3, $5);
    }
    | UOP L_PAREN Expression R_PAREN {
        $$ = new gerador::ast_node($1, $3);
    }
    | MULTIPLY L_PAREN Expression AmbiguousOperation {
        $$ = $4 == NULL
            ? new gerador::ast_node(gerador::ast_node_types::DEFERENCE, $3)
            : new gerador::ast_node(gerador::ast_node_types::MULTIPLY, $3, $4);
    }
    | MULTIPLY DeferenceLoop L_PAREN Expression R_PAREN {
        $$ = $2;
        $2 = $4;
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
        $$ = new gerador::ast_node($4, $2);
    }
    | TERNARY L_PAREN Expression COMMA Expression COMMA Expression R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::TERNARY, $3, $5, $7);
    }
    | ID Array {
        gerador::symbol* s = is.get_symbol($1);
        if(!$2->empty()) {
            std::vector<int>& products = array_map.find($1)->second;
            if(s != nullptr) switch(s->type) {
                case gerador::var_types::INT:
                case gerador::var_types::POINTER:
                    current_type_size = 4;
                    break;
                case gerador::var_types::CHAR:
                    current_type_size = 1;
                    break;
                default:
                    break;
            }
            
            gerador::ast_node* n = new gerador::ast_node(gerador::ast_node_types::NUMBER, 0);

            for(int i = 0; i < products.size(); i++) {
                n = new gerador::ast_node(gerador::ast_node_types::PLUS, n, 
                        new gerador::ast_node(gerador::ast_node_types::MULTIPLY, 
                        new gerador::ast_node(gerador::ast_node_types::MULTIPLY, 
                        new gerador::ast_node(gerador::ast_node_types::NUMBER, products[i]), 
                        new gerador::ast_node(gerador::ast_node_types::NUMBER, 4)), (*$2)[i]));
            }

            $$ = new gerador::ast_node(gerador::ast_node_types::DEFERENCE, 
                new gerador::ast_node(gerador::ast_node_types::PLUS, n,
                    new gerador::ast_node(gerador::ast_node_types::ID, std::string($1))));
        } else {
            if(s != nullptr && s->tag == gerador::ast_node_types::GLOBAL_VAR)
                $$ = new gerador::ast_node(gerador::ast_node_types::DEFERENCE, 
                    new gerador::ast_node(gerador::ast_node_types::ID, std::string($1)));
            else
                $$ = new gerador::ast_node(gerador::ast_node_types::ID, std::string($1));
        }
    }
    | ID L_PAREN Arguments R_PAREN {
        auto to_upper_case = [](char (&str)[256]) -> std::string {
            std::string ret = "";
            int i = 0;
            while(str[i] != '\0') ret += toupper(str[i++]);    
            return ret;
        };

        if(to_upper_case($1) == "PRINTF") {
            $$ = new gerador::ast_node(gerador::ast_node_types::PRINTF, std::string($1), *$3);
        } else if(to_upper_case($1) == "SCANF") {
            $$ = new gerador::ast_node(gerador::ast_node_types::SCANF, std::string($1), *$3);
        } else
            $$ = new gerador::ast_node(gerador::ast_node_types::CALL, std::string($1), *$3);
    }
    | Literal { $$ = $1; }
    ;

/* IdAccess
    : ID { 
        strcpy($$, $1);
        gerador::symbol* s = is.get_symbol($1);
        if(s != nullptr) switch(s->type) {
            case gerador::var_types::INT:
            case gerador::var_types::POINTER:
                current_type_size = 4;
                break;
            case gerador::var_types::CHAR:
                current_type_size = 1;
                break;
            default:
                break;
        }
    }
    ; */

Arguments
    : Expression Variadic {
        $2->insert($2->begin(), $1);
        $$ = $2;
    }
    | %empty {
        $$ = new std::vector<gerador::ast_node*>();
    }
    ;

DeferenceLoop
    : DeferenceLoop MULTIPLY {
        $$ = new gerador::ast_node(gerador::ast_node_types::DEFERENCE, $1);
    }
    | MULTIPLY {
        gerador::ast_node* buf = new gerador::ast_node(
            gerador::ast_node_types::NOT, nullptr); 
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
    : Array L_BRACKET Expression R_BRACKET {
        $1->push_back($3);
        $$ = $1;
    }
    | %empty { 
        $$ = new std::vector<gerador::ast_node*>();
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

        if(! $3->empty())
            current_array = $3;
        else
            current_array = nullptr;
    }
    ;

ElseBlock
    : COMMA StatementList {
        $$ = $2;
    }
    | %empty { $$ = new std::vector<gerador::ast_node*>(); }
    ;

If
    : IF L_PAREN Expression COMMA StatementList ElseBlock R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::IF, $3, 
            *$5, *$6);
        delete $5;
        delete $6;
    }
    ;

While
    : WHILE L_PAREN Expression COMMA StatementList R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::WHILE, $3,
            *$5);
    }
    ;

DoWhile
    : DO_WHILE L_PAREN Expression COMMA StatementList R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::DO_WHILE, $3,
            *$5);
    }
    ;

For
    : FOR L_PAREN Expression COMMA Expression COMMA Expression COMMA StatementList R_PAREN {
        $$ = new gerador::ast_node(gerador::ast_node_types::FOR, $3, $5, $7,
            *$9);
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
    : Variadic COMMA Expression {
        $1->push_back($3);
        $$ = $1;
    }
    | %empty { $$ = new std::vector<gerador::ast_node*>(); }
    ;

StatementList
    : StatementListContinuation Statement {
        $1->push_back($2);
        $$ = $1;
    }
    ;

StatementListContinuation
    : StatementList SEPARATOR { $$ = $1; }
    | %empty { $$ = new std::vector<gerador::ast_node*>(); }
    ;

Statement
    : If { $$ = $1; }
    | While { $$ = $1; }
    | DoWhile { $$ = $1; }
    | For { $$ = $1; }
    | Expression { $$ = $1; }
    | Return { $$ = $1; }
    ;

ParameterList
    : ParameterList PARAMETER COLON ID TYPE COLON TypeDeclaration SEPARATOR {
        if(current_array != nullptr) {    
            std::vector<int> dimension_products;
            int product = 1,
                size = 1;
            
            for(int k = 0; k < current_array->size(); k++) {
                for(int l = k + 1; l < current_array->size(); l++) {
                    product *= (*current_array)[l]->get_number_value();
                }
                size *= (*current_array)[k]->get_number_value();
                dimension_products.push_back(product);
                product = 1;
            }

            // std::cout << "dimension_products = " << std::endl;
            // for(auto& i : dimension_products) {
            //     std::cout << i << ' ';
            // }

            array_map.insert({std::string($4), dimension_products});
        }
        is.add_parameter($4, gerador::ast_node_types::PARAM, $7);
        $1->push_back(new gerador::ast_node(gerador::ast_node_types::PARAM, 
            std::string($4), $7));
        $$ = $1;
    }
    | %empty { $$ = new std::vector<gerador::ast_node*>(); }
    ;

VariableList
    : VariableList VAR COLON ID TYPE COLON TypeDeclaration SEPARATOR {
        if(current_array != nullptr) {    
            std::vector<int> dimension_products;
            int product = 1,
                size = 1;
            
            for(int k = 0; k < current_array->size(); k++) {
                for(int l = k + 1; l < current_array->size(); l++) {
                    product *= (*current_array)[l]->get_number_value();
                }
                size *= (*current_array)[k]->get_number_value();
                dimension_products.push_back(product);
                product = 1;
            }

            // std::cout << "dimension_products = " << std::endl;
            // for(auto& i : dimension_products) {
            //     std::cout << i << ' ';
            // }

            array_map.insert({std::string($4), dimension_products});
        }
        is.add_variable(std::string($4), $7);
        $1->push_back(new gerador::ast_node(gerador::ast_node_types::VAR, std::string($4), $7));
        $$ = $1;
    }
    | %empty { $$ = new std::vector<gerador::ast_node*>; }
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
    /* #ifdef YYDEBUG
        yydebug = 1;
    #endif */

    yyparse();

    program.compile(is);

    is.print();

    /* program.draw(); */
 
    return 0;
}