/* New attributes in C++17 */

#include <iostream>
#include <random>
#include <string>
#include <vector>

static std::mt19937_64 rand_eng{std::random_device{}()};
static std::uniform_int_distribution<int> dist{0, 5};

/* Example use of [[nodiscard]]

   [[nodiscard]] indicates to the compiler that the following value should not be
   used in a discarded-value context/expression. The compiler will issue a warning
   if it finds the value in such a state.
*/
template <typename T>
[[nodiscard]] constexpr auto
no_discard_function(T&& t) {
    return std::to_string(std::forward<T>(t));
}

/* Example use of [[maybe_unused]]

  [[maybe_unused]] suppresses unused warnings for variables left unused.
*/
template <typename T>
constexpr auto
maybe_unused_function(T&& t) {
    [[maybe_unused]] auto i = 5;
    [[maybe_unused]] auto j = 5.999;
    return 6;
}

auto
generate_random_char() -> char {
    return 'a' + dist(rand_eng);
}

int main() {
    no_discard_function(123); /* This will emit a compiler warning*/

    /* Suppressing [[nodiscard]] with [[maybe_unused]] */
    [[maybe_unused]] auto&& str = no_discard_function(456L);

    auto result = 0;

    /* Example use of [[fallthrough]]
    
       [[fallthrough]] suppresses compiler warnings on switch fallthrough
       (i.e. moving to the next case label in the absence of a break)
    */
    switch(generate_random_char()) {
        case 'a': result += 5;
                  [[fallthrough]];
        case 'b': result = (result + 1) * 2;
                  [[fallthrough]];
        case 'c': result -= 3;
                  [[fallthrough]];
        case 'd': result *= 20;
                  [[fallthrough]];
        default:  std::cout << result << std::endl;
    }
}
