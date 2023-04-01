#include <iostream>
#include <list>
#include <map>
#include <string>

struct scope {
    std::map<const std::string, void*> ids;
    std::list<void*> statements;
};

struct context {
    std::list<scope> ctx_stack;

    context& operator++(int) {
        ctx_stack.push_back(scope());
        return *this;
    }

    context& operator--(int) {
        ctx_stack.pop_back();
        return *this;
    }

    scope& current_scope() {
        return ctx_stack.back();
    }
} ctx;

int main() {
    ctx++;
    
    ctx.current_scope().ids.insert({ "teste", NULL });
    ctx.current_scope().statements.push_back(NULL);

    if(ctx.current_scope().ids["teste"] == NULL)
        std::cout << "Passou no teste" << std::endl;

    ctx--;
    return 0;
}