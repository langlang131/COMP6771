# Week 3 Exercises

## Q3.1. Plug-and-Play STL

There are many ready-made components in the STL that make common programming tasks extremely easy.
When it comes to using containers like `std::vector` and algorithms like `std::sort`, many useful things can be found in the `<functional>` header.

Your task is to complete the `sort_descending()` function in `src/3.1/sort_descending.cpp`.
You can find its documentation in `src/sort_descending.h`.

You also need to write at least **two** tests in `src/3.1/sort_descending.test.cpp` to make sure your code is correct!

## Q3.2. Vowel Sort

A powerful aspect of `std::sort` is being able to change the meaning of "sorted" by supplying a different comparator to the sort.

In olden times, this would be done by crafting a separate function each time and supplying a function pointer.
As of C++11, this is now all doable inline with `lambda` functions.

How might we use a lambda function to sort a vector of strings by the number of vowels in each string?
Furthermore, if the number of vowels are equal, then the strings should be lexicographically sorted.

In `src/3.2/vowel_sort.cpp`, there is a stub for a function that accepts a vector of strings and sorts it in ascending order according to the above rules.

You need to implement this function using a lambda as the custom comparator.
You should also write at least **two** tests to verify that your code is correct.

## Q3.3. Statistically Marking

In `src/3.3/marks.txt` there is a newline separated file of anonymous marks from a previous offering of this course!
To show off your budding C++ prowess, you have decided to calculate the median, average, highest, and lowest mark from this newline-separated list using nothing but the C++ Standard Library. In particular:

- std::ifstream
- std::vector
- std::algorithms

In your enthusiasm, you decided to code your program in a modular style. So, in addition to a `calculate_stats()` function, you also made a separate function that loads in the marks from a file!

In reflection, you remembered your old Professor's words, and decided to write at least **two** tests overall to make sure your code is correct.

Both functions should be coded in `src/3.3/stats.cpp`, but more documentation is in `src/stats.h`. Your tests should be implemented in `src/3.3/stats.test.cpp`.

## Q3.4. Inverse Mappings

`std::map` is one of the Standard Library's most widely used types (owing mainly to the fact that the need for an associative array appears in many places).

One not-so-common but still vitally important operation on a map is to invert its keys and values.
For example,

```cpp
auto m = std::map<std::string, int>{{"hi", 42}, {"bob", 6771}};
```

the inversion of `m` would be

```cpp
auto n = std::map<int, std::string>{{42, "hi"}, {6771, "bob"}};
```

As you can see, the keys have been swapped with their values and vice-versa.

Your task is to implement the `invert()` operation for a map of `std::string` to `int`, namely `std::map<std::string, int>`.

However, rather than a simple inversion, there is an added constraint.

If, after inversion, the same key appears more than once (which can happen due to values having different keys in the original map), only the key/value pair with the longest string should ultimately be in the resulting map.
For example, for the map `m`,

```cpp
auto m = std::map<std::string, int> {
    {"a", 6771},
    {"ab", 6771},
    {"abc", 6771},
    {"xyz", 6772},
};
```

it's inversion should be:

```cpp
auto n = std::map<int, std::string> {
    {6771, "abc"},
    {6772, "xyz"},
};
```

In `src/3.4/invert.cpp`, implement the `invert` operation and in `src/3.4/invert.test.cpp`, write at least **three** tests to ensure your code is correct!

## Q3.5. Namespacing Out

In `src/3.5/namespaced.cpp`, we have provided the below `main()` function:

```cpp
int main() {
    namespace spaceland = comp6771;

    // should be an alias for std::vector.
    auto v = spaceland::vector{6771};
    
    // name: earth, position from sun: 3
    // a planet is a kind of 
    auto earth = spaceland::planet{"earth", 3};

    // should produce an object with the same type as the "earth" variable above.
    auto old_earth = spaceland::planets::terrestrial{"earth", 3};

    std::cout << v[0] << std::endl;
    std::cout << earth.name << std::endl;
    std::cout << old_earth.pos << std::endl;
}
```

In `src/3.5/namespaced.h`, implement the rest of the missing namespace functionality such that this code compiles and produces this output (note the newline at the end):

```txt
6771
earth
3
```

There is a plain-old-data struct in `src/3.5/namespaced.h` that may be used as a `planet` type.

**Note**: you are not allowed to modify `src/3.5/namespaced.cpp`.

**Hint**: it does not matter how you implement the namespaces in the header file -- if your code compiles and produces the above output, then it is correct.

## Q3.6. What a Dictionary

This task focuses on using standard algorithms to read a list of newline-seperated words from a file (try `/usr/share/dict/words` or `/usr/dict/words`) into a vector (hint: see std::istream_iterator).

There are two functions for you to implement in `src/3.6/dict.cpp`. Remember to add some tests in `src/3.6/dict.test.cpp`!

- Complete the function `to_word_list` that takes in the word list as a stream, and outputs a vector of strings that are the words.
- Complete the function `print_valid_words` that uses standard algorithms to split the string into words, filtered to only words that are in the word dict, and reconstruct this into a string (hint: see `std::copy_if`).

Consider the implications on this program if the list is extremely large and the words themselves were long as well. Is there any improvements we can make?
