# C++17

## Overview

The latest draft for C++17 can be found [here](https://github.com/cplusplus/draft/blob/master/papers/n4687.pdf).

## Features 
(NOT COMPLETED. Once this is removed, the list is complete)

* [`constexpr` constructs](#constexpr-constructs)
* [Fold expressions](#fold-expressions)
* [Selection statements with initializer](#selection-statements-with-initializer)
* [Stuctured bindings](#structured-bindings)

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
