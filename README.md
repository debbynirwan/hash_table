# hash_table
Simple implementation of Hash Table in C++. It's mainly intended to show how hash tables are implemented by libraries like STL.

# How to build and install the library
It is a header-only library. You can copy it directly into your repository or build and install it as follows:
```cmake
> mkdir build && cd build
> cmake ..
> make
> make install
```

To build the example you have to set the BUILD_EXAMPLE option ON. By default it is not built.
```cmake
> cmake -DBUILD_EXAMPLE=ON ..
```
# Examples
To use the library simply include and use it. 
```cpp
#include "hash_table.hpp"

HashTable<int, int> table;

table.Insert(1, 5);
auto val = table.At(1);
table.Remove(1);

```
see [example](example/main.cpp) for more.

# Documentation
If you're interested in understanding the details you can read my blog post [here]().

# Issues
Please report issues if you found bugs or raise a Pull Request.
