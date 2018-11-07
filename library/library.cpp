//
// Created by Alexey A. Ponomarev on 07.11.18.
//

#include "library.h"

lib::FA::Vertex::Vertex(bool is_terminal) : _is_terminal(is_terminal) {}

void lib::FA::clear() {
    _state = _start;
}

bool lib::FA::is_terminal() const {
    return _state->_is_terminal;
}

void lib::FA::signal(lib::Errors error) {
    std::cerr << error << std::endl;
    std::cout << "ERROR" << std::endl;
    exit(0);
}

lib::NFA::NFA(char x) {
    _start = new Vertex();
    _start->nexts[x] = new Vertex(true);
}

lib::NFA::NFA(const std::string &s) {
    std::stack<NFA> st;

    for (char x : s) {
        switch (x) {
            case '.':
                assert(st.size() >= 2);
                NFA first = st.top();
                st.pop();
                NFA second = st.top();
                st.pop();

                if (first.is_string() && second.is_string()) {
                    first.add(second);
                } else {
                    signal(Errors::PARSING_REGULAR_EXPRESSION);
                }
                st.push(first);
                break;
            case '+':

                break;
            case '*':

                break;
            default:
                if (x < 'a' || x > 'z')

                    break;
        }
    }
}
