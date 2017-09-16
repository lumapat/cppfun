# C++17

## Overview

The latest draft for C++17 can be found [here](https://github.com/cplusplus/draft/blob/master/papers/n4687.pdf).

## Language Features 
(NOT COMPLETED. Once this is removed, the list is complete)

* [Class template argument deduction](#class-template-argument-deduction)
* [`constexpr` constructs](#constexpr-constructs)
* [Fold expressions](#fold-expressions)
* [Selection statements with initializer](#selection-statements-with-initializer)
* [Stuctured bindings](#structured-bindings)

## Library Features

## Language Features in Detail

### Class template argument deduction
Like functions, template arguments of a templated class can now be deduced from a constructor! In addition, C++17 provides user-defined deduction guides for deducing class template arguments. Look [here](http://en.cppreference.com/w/cpp/language/class_template_argument_deduction) for more information.

#### Syntax (for user-defined deduction guides)
```cpp
template <typename T> explicit Class(T) -> A<T>;
template <typename Iter> Class(Iter, Iter) -> A<typename std::iterator_traits<Iter>::value_type>;
```

See above cppreference page for more details.

#### Examples
```cpp
template <typename T = int>
class Object {
    public:
        Object() = default;
        Object(T) { ... }
};

// User-defined deduction guide
template <typename T> Object(std::vector<T>) -> Object<T>;

...

// Before C++17, we would need to specify the type
auto o0 = Object<int>{};
auto o1 = Object<double>{1.55};

// Now we can do these!
auto o1 = Object{}; // o1 is of type Object<int>
auto o2 = Object{100L};    // o2 is of type Object<long>
auto o3 = Object{std::vector<std::string>{}}; // o3 is of type Object<std::string> with the deduction guide
```

[examples/classdeduc.cpp](examples/classdeduc.cpp) contains more examples on class template argument deduction.

### `constexpr` constructs
[`constexpr`](http://en.cppreference.com/w/cpp/language/constexpr) is a specifier introduced in C++11 that indicates that an expression, function (including constructors), or variable be evaluated at compile time. Recently, C++17 introduced `constexpr` lambda expressions and `if` statements.

#### Syntax
```cpp
/* constexpr lambda expression (one variant) */
auto add = [](auto i, auto j) constexpr { return i + j; };

/* constexpr if */
auto smth = someValue();

if constexpr(std::is_integral<decltype(smth)>::value) {
    // do something with that integral value
}
else {
    // do something with that non-integral value
}
```

Check out cppreference on [lambdas](http://en.cppreference.com/w/cpp/language/lambda) and [`if` statements](http://en.cppreference.com/w/cpp/language/if) for more details.

#### Examples
[examples/constexpr.cpp](examples/constexpr.cpp) contains examples on these `constexpr` constructs.

### Fold expressions
This extends the capabilities already established by C++11's parameter packing. Fold expressions are seen (and are integral to) languages like Haskell, and it has come to C++! 

#### Syntax
```cpp
/* Unary right and left fold */
(pack op ...)
(... op pack)

/* Binary right and left fold */
(pack op ... op init)
(init op ... op pack)

```
Check out [cppreference](http://en.cppreference.com/w/cpp/language/fold) for more details.

#### Examples
[examples/foldexpr.cpp](examples/foldexpr.cpp) contains examples on fold expression usage.

### Selection statements with initializer
`if` statements and `switch` statements can now contain initializer expressions before boolean expressions. Consider the following as scenarios improved upon by these features:

```cpp
/* Mutex RAII in an if-statement */
std::mutex mx;

{
    std::lock_guard<std::mutex> lk(mx);
    if(var.something()) var.somethingElse();
}

...

/* Members required from newly instantiated objects */
Object o{args};

switch(o.someProperty()) {
    ...
}
```

#### Syntax
```cpp
/* if-initializer */
if(initializer-expr; boolean-expr) {
    ...
}

/* switch-initializer */
switch(initializer-expr; value-expr) {
    ...
}
```

Check out cppreference for more details on [if-initializers](http://en.cppreference.com/w/cpp/language/if#If_Statements_with_Initializer) and [switch-initializers](http://en.cppreference.com/w/cpp/language/switch).

#### Examples
```cpp
std::mutex mx;

/* if-initializer */
if(std::lock_guard<std::mutex> lk(mx); var.something()) {
    ...
    var.somethingElse();
    ...
}

...

/* switch-initializer */
switch(Object o{args}; o.getProperty()) {
    ...
}
```


### Structured bindings
Syntactic sugar for unpacking tuples and other structures. Consider the following:

```cpp
auto tuple = std::make_tuple(1, "string", 500L, 'c');

/* Declaring variables for unpacking */
int i;
std::string s;
long l;
char c;

/* Unpacking the tuple */
std::tie(i, s, l, c) = tuple;

...
```
Not only is this verbose, but this also forces default construction of non-POD types which is often undesirable. Thus, the following [proposal](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0144r0.pdf) was introduced.  

#### Syntax
```cpp
auto [identifier-list] = expression;
```

Check out [cppreference](http://en.cppreference.com/w/cpp/language/structured_binding) for more details.

#### Examples
[examples/strucbind.cpp](examples/strucbind.cpp) contains examples on structured bindings usage.
