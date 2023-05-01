#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

#include "graph.h"

#define MEETS_SIMPLIFY_CRITERIA(a, b) b.degree() < a.degree() ||                                    \
                                      (b.degree() == a.degree() && b.id < a.id)
#define MEETS_SPILL_CRITERIA(a, b) b.degree() > a.degree() ||                                       \
                                   (b.degree() == a.degree() && b.id < a.id)

regalloc::interference_graph regalloc::interference_graph::from(std::istream& input) {
    interference_graph g;
    std::string line;
    int node;

    std::getline(input, line);
    std::istringstream iss(line);
    iss >> line >> g.title;

    std::getline(input, line);
    g.k = std::stoi(line.substr(2));

    while(std::getline(input, line)) {
        std::istringstream iss(line);
        iss >> node;
        
        if(g.nodes.find(node) == g.nodes.end()) {
            g.nodes.insert({node, {}});
        }

        interference_graph::node& n = g.nodes[node];
        n.id = node;
        if(node < g.k) n.color = node;

        iss >> line;
        
        while(iss >> node) {
            n.edges.insert(node);
            
            if(g.nodes.find(node) == g.nodes.end()) {
                g.nodes.insert({node, {}});
            }

            interference_graph::node& e = g.nodes[node];
            e.id = node;
            if(node < g.k) e.color = node;
            e.edges.insert(n.id);
        }
    }

    return g;
}

int regalloc::interference_graph::get_best_simplify_option() {
    int candidate = -1;

    for(auto& n : nodes) {
        if(n.second.id >= k) {
            if(candidate == -1)
                candidate = n.first;
            else if(MEETS_SIMPLIFY_CRITERIA(nodes[candidate], n.second))
                candidate = n.first;
        }
    }

    return candidate;
}

int regalloc::interference_graph::get_best_spill_option() {
    int candidate = -1;

    for(auto& n : nodes) {
        if(n.second.degree() < k) {
            if(candidate == -1)
                candidate = n.first;
            else if(MEETS_SPILL_CRITERIA(nodes[candidate], n.second))
                candidate = n.first;
        }
    }

    return candidate;
}

bool regalloc::interference_graph::allocate(int k, std::ostream& output) {
    regalloc::interference_graph copy = *this;
    std::stack<node> select_stack;
    int choice;

    output << "----------------------------------------\nK = " << k << std::endl << std::endl;

    while(choice != -1) {
        choice = get_best_simplify_option();

        if(choice > 0) if(nodes[choice].degree() < k) {
            output << "Push: " << choice << std::endl;
            select_stack.push(copy.nodes[choice]);
            remove(choice);
        } else {
            choice = get_best_spill_option();
            output << "Push: " << choice << " *" << std::endl;
            select_stack.push(copy.nodes[choice]);
            remove(choice);
        }
    }

    while(!select_stack.empty()) {
        node& n = select_stack.top();
        bool used_colors[this->k] = { false };

        insert(n.id);
        
        for(auto& e : n.edges) {
            connect(n.id, e);
            if(copy.nodes.find(e) != copy.nodes.end()) {
                if(nodes[e].color != -1)
                    used_colors[nodes[e].color] = true;
            }
        }

        do {
            if(++nodes[n.id].color >= k) {
                output << "Pop: " << n.id << " -> NO COLOR AVAILABLE" << std::endl;
                return false;
            }
        } while(used_colors[nodes[n.id].color]);

        output << "Pop: " << n.id << " -> " << nodes[n.id].color << std::endl;
        select_stack.pop();
    }

    return true;
}

void regalloc::interference_graph::insert(int node) {
    if(nodes.find(node) == nodes.end()) {
        nodes.insert({node, {}}).first->second.id = node;
        if(node < k) nodes[node].color = node;
    }
}

void regalloc::interference_graph::connect(int n1, int n2) {
    if(nodes.find(n1) != nodes.end() && nodes.find(n2) != nodes.end()) {
        nodes[n1].edges.insert(n2);
        nodes[n2].edges.insert(n1);
    }
}

void regalloc::interference_graph::remove(int node) {
    nodes.erase(node);

    for(auto& n : nodes) {
        n.second.edges.erase(node);
    }
}

void regalloc::interference_graph::to_dot(std::ostream& output) {
    output << "strict graph grafo" << " {" << std::endl;
    output << "    node [shape=circle];" << std::endl;

    for(auto& n : nodes) {
        n.second.to_dot(output, nodes);
    }

    output << "}" << std::endl;
}

inline int regalloc::interference_graph::node::degree() {
    return edges.size();
}

void regalloc::interference_graph::node::to_dot(std::ostream& output, std::map<int, node>& node_map) {
    if(visited) {
        return;
    }

    visited = true;
    output << "    n" << id << " [label=\"" << id << "\"];" << std::endl;

    for(auto& e : edges) {
        node_map.find(e)->second.to_dot(output, node_map);
        output << "    " << 'n' << id << " -- " << 'n' << e << ";" << std::endl;
    }
}