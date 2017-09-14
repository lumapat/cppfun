/* Class template argument deduction */

#include <vector>
#include <iterator>

template <typename T = int>
class Object {
    public:
        Object() = default;

        template <typename U>
        Object(U) { }
};

template <typename T, typename U, typename V>
class ReallyTemplatedObject {
    public:
        ReallyTemplatedObject() = default;
        ReallyTemplatedObject(T, U, V) { }
};

// User-defined deduction guides
template <typename T> Object(std::vector<T>) -> Object<T>;

template <typename T, typename U, typename V>
Object(ReallyTemplatedObject<T, U, V>) -> Object<U>;

auto
main() -> int {
    // Before C++17, we would need to specify the types like these
    auto o0 = Object<int>{};
    auto r0 = ReallyTemplatedObject<int, double, std::string>{};

    // Now we can do these!
    auto o1 = Object{};
    auto r1 = ReallyTemplatedObject{1, 2.0, std::string{"Hello World!"}};

    auto o2 = Object{std::vector<long long>{}};// o2 is of type Object<long long> with the deduction guide
    auto o3 = Object{r1};                      // o3 is of type Object<double> with the deduction guide
}
