/* Fold expressions */

#include <iostream>


/* (Subtraction) right fold: (T op ...) --> T1 op (T2 op ... op (TN op I)) */
template <typename... Ns>
constexpr auto
subr(Ns&&... ns) {
    return (std::forward<Ns>(ns) - ...); // Fold expressions must be surrounded by parentheses
}

/* (Subtraction) left fold: (... op T) --> (((I op T1) op T2) op ...) op TN */
template <typename... Ns>
constexpr auto
subl(Ns&&... ns) {
    return (... - std::forward<Ns>(ns)); // Again, fold expressions must be surrounded by parentheses
}

/* (Print) left fold */
template <typename... Ts>
void
printOutLeft(Ts&&... ts) {
    (std::cout << ... << ts) << "\n";
}

/* (Print) right fold */
template <typename... Ts>
void
printOut(Ts&&... ts) {
    auto print = [](auto t1) { std::cout << t1; };
    (print(std::forward<Ts>(ts)), ...);
    // Unfortunately, same as
    // (..., print(ts));
    // due to operator,() evaluation
    std::cout << "\n";
}

/* Also, unfortunately, only the 32 binary operations built into C++ can be used as ops for fold expr's */
// auto f = [](auto t) { ... };
// (f(ts)...); // This is not allowed --> f(t1, f(t2, f(t3, ...)))

int main() {
    static_assert(subr(1) == subl(1)); // There shouldn't be a change at all in their returns for single args

    std::cout << "Performing subtraction on 16,9,4..." << "\n";
    std::cout << "(Left) (16-9)-4: " << subl(16,9,4) << "\n";
    std::cout << "(Right) 16-(9-4): " << subr(16,9,4) << "\n";

    std::cout << "Testing print function with fold expression..." << "\n";
    printOut("Hello! ", 1234, " How ", "are ", "you?");

    std::cout << std::flush;
}
