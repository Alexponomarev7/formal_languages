#include <iostream>
#include <vector>
#include "library.h"

int main() {
    std::string s, p;
    std::cin >> s >> p;

    size_t n = p.length();

    lib::NFA nfa = lib::NFA(s);

    int ans = -1;
    for (size_t i = 0; i < n; ++i) {
        nfa.clear();
        if (nfa.is_terminal()) {
            ans = 0;
        }

        for (size_t j = i; j < n; ++j) {
            nfa.go(p[j]);

            if (nfa.is_terminal()) {
                ans = std::max(ans, (int)(j - i + 1));
            }
        }
    }
    if (ans == -1) {
        std::cout << "INF" << std::endl;
    } else {
        std::cout << ans << std::endl;
    }

    return 0;
}