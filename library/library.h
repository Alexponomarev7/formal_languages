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
    public:
        struct Vertex {
            bool _is_terminal;
            std::map<char, std::unordered_set<Vertex*>> nexts;

            Vertex(bool is_terminal=false);
        };
    protected:
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
        Vertex* get_start() const;
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

int get(lib::FA::Vertex* v) {
    static std::unordered_map<lib::FA::Vertex*, int> d;
    static int x = 0;

    if (d.find(v) != d.end())
        return d[v];

    d[v] = x;
    x++;

    return d[v];
}

void print(lib::FA::Vertex* v) {
    static std::unordered_set<lib::FA::Vertex*> f;

    static int x = 0;

    if (f.find(v) != f.end())
        return;

    f.insert(v);

    for (auto x : v->nexts) {
        for (auto y : x.second) {
            std::cout <<get(v) << " " << get(y) << " ";
            if (x.first == lib::EPS) {
                std::cout << "eps" << std::endl;
            } else {
                std::cout <<(char)x.first << std::endl;
            }
            print(y);
        }
    }
}

#endif //ALGO_LIBRARY_H
