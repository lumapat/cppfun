/* Parameter packs/variadic templates */

#include <iostream>

template <typename T>
constexpr auto
subr(T&& t) {
    return std::forward<T>(t);
}

template <typename T, typename... Ts>
constexpr auto
subr(T&& t, Ts&&... ts) {
    return std::forward<T>(t) - subr(std::forward<Ts>(ts)...);
}

template <typename T>
constexpr auto
subl(T&& t) {
    return std::forward<T>(t);
}

template <typename T1, typename T2, typename... Ts>
constexpr auto
subl(T1&& t1, T2&& t2, Ts&&... ts) {
    return subl(std::forward<T1>(t1) - std::forward<T2>(t2), std::forward<Ts>(ts)...);
}

/* 
 * The following snippet is not allowed. This is because
 * parameter packs can only occur at the end according to the standard.
 * Otherwise, we have a non-deducible context.
*/

/*
template <typename T>
constexpr auto
subl(T&& t) {
    return std::forward<T>(t);
}

template <typename... Ts, typename T>
constexpr auto
subl(Ts&&... ts, T&& t) {
    return subl(std::forward<Ts>(ts)...) - std::forward<T>(t);
}
*/

template <typename... Ts>
constexpr auto
countTypes(Ts... ts) {
    return sizeof...(ts);
}

/* Variadic inheritance */
struct A {
    void funcA() {
        std::cout << "Called funcA!\n";
    }
};

struct B {
    void funcB() {
        std::cout << "Called funcB!\n";
    }
};

template <typename... Ts>
class C: public Ts... {

};

/* Variadic lambda captures */
template <typename... Ts>
constexpr auto
sum(Ts... ts) {
    auto sub = [ts...]() -> decltype(auto) {
        return subl(ts...);
    };

    return sub();
}

int main() {
    std::cout << "Performing subtraction on 16,9,4...\n";
    std::cout << "(Left) (16-9)-4: " << subl(16,9,4) << "\n";
    std::cout << "(Right) 16-(9-4): " << subr(16,9,4) << "\n";

    std::cout << "Number of template arguments in (1, 'c', \"string\", std::string(\"string\"), 100L): "
              << countTypes(1, 'c', "string", std::string("string")) << "\n";

    std::cout << "Instantiating variadic inherited object C<A,B>...\n";
    C<A,B> obj;
    std::cout << "Calling variadic templated derived class methods...\n";
    obj.funcA();
    obj.funcB();

    std::cout << "Subtracting: 501L - 500 - 0.50: " << sum(501L, 500, .5) << std::endl;
}
