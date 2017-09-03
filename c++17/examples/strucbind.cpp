/* Structured bindings */

#include <array>
#include <tuple>
#include <iostream>

/* Non-POD class */
class NonPOD {
    public:
        int i, j;
        std::string k;

        NonPOD(): i(1), j(4), k("Hello!") {
           // User defined
        }

        NonPOD(int i, int j, const std::string& k): i(i), j(j), k(k) {
            // User defined explicit constructor
        }

        virtual auto virtfunc() const -> void {
            auto ij = i*j;
            std::cout << "This is a dummy virtual function for disqualifying the class from the standard layout: " << ij << "\n";
        }
};

auto
main() -> int {
    using std::cout;

    /* Bindings with arrays */
    {
        auto printIterable = [](auto iterable) {
            for(auto& i: iterable) std::cout << i << " ";
            cout << "\n";
        };

        auto arr = std::array<int,3>{1,4,9};
        cout << "Here's the array before any modifications: ";
        printIterable(arr);

        /* Bindings */
        auto  [val0, val1, val2] = arr;
        auto& [rvl0, rvl1, rvl2] = arr;

        rvl0 -= val0;
        rvl1 -= val1; 
        rvl2 -= rvl2;
        cout << "Here's the array after modifications: ";
        printIterable(arr);
    }

    /* Bindings with tuples */
    {
        const auto tup = std::tuple<double, int, std::string>{3.14, 69, "C++ #1!"};
        std::cout << "Binding values from tuple...\n";

        /* Binding */
        const auto& [d, i, s] = tup;
        auto&& [str, ch] = std::tuple<std::string, char>{"Hiho!", 'c'};

        /* Way better than:
         * const double& d; const int& i; const std::string& s;
         * std::tie(d, i, s) = tup;
         */

        cout << "Here are the values!: " << d << ", " << i << ", " << s << "\n";
        cout << "Here are more values!: " << str << ", " << ch << "\n";
    }

    /* Bindings with classes/structs on their public data members */
    {
        auto n = NonPOD{}; /* If this can be illustrated with a non-POD type, then PODs can also be bound */
        cout << "Binding values from class...\n";


        /* Binding */
        auto& [i, j, k] = n;

        cout << "Here are the values!: " << i << ", " << j << ", " << k << "\n";

    }

    /* Other bindings (non-exhaustive list)*/
    {
        auto arr = std::array<NonPOD, 3>{{{1, 2, "One"}, {3, 4, "Two"}, {5, 6, "Three"}}};
        cout << "Structured bindings with for-each...\n";

        /* for-each binding */
        for(const auto& [i, j, k]: arr) {
            cout << "Here are the values!: " << i << ", " << j << ", " << k << "\n";
        }

        cout << "Structured bindings with if-initializer...\n";

        /* if-initializer binding */
        if (const auto& [i, j, k] = arr[1]; i+j == 7) cout << "Here's a value: " << k << "\n";

        /* Other ways to bind */
        {
            [[maybe_unused]] const auto& [i, j, k]{arr[0]}; // brace-enclosed expression
            [[maybe_unused]] const auto& [l, m, n](arr[2]); // parenthesized expression
        }
    }
}

