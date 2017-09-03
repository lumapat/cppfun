# C++17

## Overview

The latest draft for C++17 can be found [here](https://github.com/cplusplus/draft/blob/master/papers/n4687.pdf).

## Features 
(NOT COMPLETED. Once this is removed, the list is complete)

* [Fold expressions](#fold-expressions)
* [Stuctured bindings](#structured-bindings)

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
More details can be found on [cppreference](http://en.cppreference.com/w/cpp/language/fold). Example code [here](examples/foldexpr.cpp).

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

The full details on this feature can be found on [cppreference](http://en.cppreference.com/w/cpp/language/structured_binding). Example code [here](examples/strucbind.cpp).

