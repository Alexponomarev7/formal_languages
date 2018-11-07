//
// Created by Alexey A. Ponomarev on 07.11.18.
//

#ifndef ALGO_LIBRARY_H
#define ALGO_LIBRARY_H

#include <iostream>
#include <unordered_map>
#include <stack>
#include <cassert>
#include <cstdlib>

namespace lib {
    enum Errors {
        PARSING_REGULAR_EXPRESSION;
    };

    struct FA {
    protected:
        struct Vertex {
            bool _is_terminal;
            std::unordered_map<char, Vertex*> nexts;

            Vertex(bool is_terminal=false);
        };

        Vertex *_start;
        Vertex *_state;
    public:
        FA() = default;

        virtual void go(char x);

        void clear();
        bool is_terminal() const;
        void signal(Errors error);
    };

    struct NFA : public FA {
        NFA(char x);

        NFA(const std::string &s);
        void go(char go) {

        }
    };
}

#endif //ALGO_LIBRARY_H
