#ifndef CONTEXT_HH
#define CONTEXT_HH

#include <list>
#include <map>
#include <string>

namespace gerador {
    class context {
        struct scope {
            std::map<const std::string, const void*> ids;
            std::list<const void*> statements;
        };

        std::list<scope> ctx_stack;

        public:
        context& operator++(int) {
            ctx_stack.push_back(scope());
            return *this;
        }

        context& operator--(int) {
            ctx_stack.pop_back();
            return *this;
        }

        inline scope& current_scope() {
            return ctx_stack.back();
        }

        inline std::map<const std::string, const void*>& ids() {
            return ctx_stack.back().ids;
        }

        inline std::list<const void*>& statements() {
            return ctx_stack.back().statements;
        }

        void add_id(const std::string& id, const void* n) {
            ctx_stack.back().ids.insert({ id, n });
        }

        void add_statement(const void* statement) {
            ctx_stack.back().statements.push_back(statement);
        }
    };
}

#endif