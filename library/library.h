#ifndef ALGO_LIBRARY_H
#define ALGO_LIBRARY_H

#include <iostream>
#include <unordered_map>
#include <stack>
#include <cassert>
#include <cstdlib>
#include <unordered_set>
#include <vector>
#include <map>
#include <set>

namespace lib {
    enum Errors {
        PARSING_REGULAR_EXPRESSION,
    };

    const char EPS = '\0';
    const int INF = 1e9;

    struct FA {
    protected:
        struct Vertex {
            bool _is_terminal;
            std::map<char, std::unordered_set<Vertex*>> nexts;

            Vertex(bool is_terminal=false);
        };

        static std::vector<Vertex*> vertexes;
        std::unordered_set<Vertex*> _terminals, _state;
        void set_terminal(Vertex* v);
        void dfs(Vertex* v, std::unordered_set<Vertex*> &been);
        void push();
        static Vertex* create_vertex();

        Vertex *_start;
    public:
        std::string description;

        FA() = default;
        ~FA() {

        }

        void clear();
        bool is_terminal() const;
        void signal(Errors error);
    };

    struct NFA : public FA {
        NFA() = default;

        NFA(char x);

        NFA(const std::string &s);

        ~NFA() {

        }

        void add(NFA &second);

        void sums(NFA &second);

        void kleene();

        void go(char go);
    };
};

#endif //ALGO_LIBRARY_H
