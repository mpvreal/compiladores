#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <unordered_set>
#include <string>

namespace regalloc {
    struct interference_graph {
        struct node {
            std::unordered_set<int> edges;
            int id, color = -1;
            bool visited, spilled;

            inline int degree();
            void to_dot(std::ostream& output, std::map<int, node>& node_map);
        };

        std::map<int, node> nodes;
        int title, size, k;

        static interference_graph from(std::istream& input);
        int get_best_simplify_option();
        int get_best_spill_option();
        bool allocate(int k, std::ostream& output);
        void insert(int node);
        void connect(int n1, int n2);
        void remove(int node);
        void to_dot(std::ostream& output);
    };
}

#endif