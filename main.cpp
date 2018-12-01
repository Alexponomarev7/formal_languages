#include <iostream>
#include <vector>
#include "library.h"

int main() {
    std::string s, p;
    std::cin >> s;

    lib::NFA nfa = lib::NFA(s);
    //std::cout << nfa.description << std::endl;

    std::cin >> p;
    size_t n = p.length();

    int ans = 0;
    for (size_t i = 0; i < n; ++i) {
        nfa.clear();

        for (size_t j = i; j < n; ++j) {
            nfa.go(p[j]);

            if (nfa.is_terminal()) {
                ans = std::max(ans, (int)(j - i + 1));
            }
        }
    }
    if (ans == lib::INF) {
        std::cout << "INF" << std::endl;
    } else {
        std::cout << ans << std::endl;
    }

    return 0;
}
