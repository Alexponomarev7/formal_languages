#include "library.h"

lib::FA::Vertex::Vertex(bool is_terminal) : _is_terminal(is_terminal) {}

lib::FA::Vertex* lib::FA::get_start() const {
    return _start;
}

void lib::FA::clear() {
    _state.clear();
    _state.insert(_start);
    push();
}

bool lib::FA::is_terminal() const {
    for (auto x : _terminals)
        if (_state.find(x) != _state.end())
            return true;
    return false;
}

void lib::FA::signal(lib::Errors error) {
    std::cerr << error << std::endl;
    std::cout << "ERROR" << std::endl;
    exit(0);
}

void lib::FA::set_terminal(lib::FA::Vertex *v) {
    _terminals.insert(v);
}

void lib::FA::push() {
    std::unordered_set<Vertex*> been;
    std::unordered_set<Vertex*> _d = _state;

    for (auto x : _d) {
        dfs(x, been);
    }
}

void lib::FA::dfs(Vertex* v, std::unordered_set<Vertex*> &been) {
    if (v == nullptr)
        return;

    if (been.find(v) != been.end())
        return;

    been.insert(v);
    _state.insert(v);

    for (auto x : v->nexts[lib::EPS]) {
        dfs(x, been);
    }
}


std::vector<lib::FA::Vertex*> lib::FA::vertexes;

lib::FA::Vertex *lib::FA::create_vertex() {
    lib::FA::vertexes.push_back(new Vertex());
    return vertexes.back();
}

lib::NFA::NFA(char x) {
    _start = create_vertex();
    Vertex *v = create_vertex();
    _start->nexts[x].insert(v);
    set_terminal(v);

    description = "";
    description.push_back(x);
}

lib::NFA::NFA(const std::string &s) {
    std::stack<NFA> st;

    for (char x : s) {
        NFA first, second;
        switch (x) {
            case '.':
                if (st.size() < 2)
                    signal(Errors::PARSING_REGULAR_EXPRESSION);

                second = st.top();
                st.pop();
                first = st.top();
                st.pop();

                first.add(second);
                st.push(first);

                break;
            case '+':
                if (st.size() < 2)
                    signal(Errors::PARSING_REGULAR_EXPRESSION);

                second = st.top();
                st.pop();
                first = st.top();
                st.pop();

                first.sums(second);
                st.push(first);

                break;
            case '*':
                if (st.size() < 1)
                    signal(Errors::PARSING_REGULAR_EXPRESSION);

                first = st.top();
                st.pop();
                first.kleene();

                st.push(first);

                break;
            default:
                if (x < 'a' || x > 'z')
                    signal(Errors::PARSING_REGULAR_EXPRESSION);
                st.push(NFA(x));
                break;
        }

        (*this) = st.top();
    }
}

void lib::NFA::add(lib::NFA &second) {
    for (auto x : _terminals) {
        x->nexts[lib::EPS].insert(second._start);
    }

    description = description + second.description;

    _terminals = second._terminals;
}


void lib::NFA::sums(lib::NFA &second) {
    Vertex *new_start = create_vertex(), *new_terminal = create_vertex();

    new_start->nexts[lib::EPS].insert(_start);
    new_start->nexts[lib::EPS].insert(second._start);

    for (auto x : _terminals) {
        x->nexts[lib::EPS].insert(new_terminal);
    }
    for (auto x : second._terminals) {
        x->nexts[lib::EPS].insert(new_terminal);
    }

    second._terminals.clear();
    _terminals.clear();
    description = "(" + description + " + " + second.description + ")";
    _start = new_start;
    set_terminal(new_terminal);
}

void lib::NFA::kleene() {
    Vertex *new_start = create_vertex(), *middle = create_vertex(),
    *new_terminal = create_vertex();

    new_start->nexts[lib::EPS].insert(middle);
    for (auto x : _terminals) {
        x->nexts[lib::EPS].insert(middle);
    }
    middle->nexts[lib::EPS].insert(_start);
    middle->nexts[lib::EPS].insert(new_terminal);

    _terminals.clear();
    description = "(" + description + ")*";
    _start = new_start;
    set_terminal(new_terminal);
}

void lib::NFA::go(char go) {
    std::unordered_set<Vertex*> new_state;

    for (auto x : _state) {
        for (auto y : x->nexts[go]) {
            new_state.insert(y);
        }
    }

    _state = new_state;
    push();
}
