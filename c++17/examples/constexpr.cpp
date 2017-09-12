/* Constexpr constructs */

#include <iostream>
#include <type_traits>

template<typename T>
constexpr auto
divide(T i, T j) {
    // constexpr return types will coerce this lambda to be constexpr
    return [](T a, T b) { return a / b; }(i, j);
}

auto
main() -> int {

    /* Constexpr lambdas */
    constexpr auto add = [](auto i, auto j) { return i + j; };

    constexpr auto i = 10;
    constexpr auto j = 9;
    auto subtract = [=]() constexpr { return i - j; };

    /* Checking to make sure this is @ compile time with static_assert */
    static_assert(3 == add(1,2));
    static_assert(1 == subtract());
    static_assert(2/1 == divide(2,1));

    /* Constexpr if-statement */
    if constexpr(std::is_integral<decltype(add(1,2))>::value) {
        std::cout << "We have attained constexpr status!" << std::endl;
    }
    else {
        std::cout << "It seems that we have lost all hope in attaining constexpr" << std::endl;
    }
}
