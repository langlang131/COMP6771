# Week 2 Exercises

## 2.1. Type-Safe Scaling

C++ has a poignant emphasis on strong type-safety. To that end it offers a type-safe version of the C-style cast called `static_cast` which only allows conversion between compatible types e.g. `int` to `float`, `void *` to `int *` etc., and will not allow unrelated casts e.g. `void *` to `int`.

In this exercise we will use `static_cast` to safely scale a vector of integers by a `double` value and return a new vector of doubles.

In `src/2.1/scale.h` there is documentation for `scale()` which does this conversion.
Implement this function in `src/2.1/scale.cpp`.
You will also need to write at least **two** tests for it in `src/2.1/scale.test.cpp`.

To improve ease of use, also add a _default value_ of 0.5 for the scaling factor.
This will allow users to not have to pass a scale factor when commonly scaling a vector in half.

## 2.2. Finding a Mismatch

The **S**tandard **T**emplate **L**ibrary (aka the STL, now part of the C++ standard proper) has three fundamental concepts: containers, iterators, and algorithms. Iterators are the glue that sits between containers of data and the algorithms that operate on them. By using these three concepts together, code reuse is maximised and composition of existing code becomes very easy.

In this exercise you will be using `std::vector<int>::iterator` to implement a less general version of [std::mismatch](https://en.cppreference.com/w/cpp/algorithm/mismatch), one of the many algorithms provided by the standard library.

There is documentation for our version of `mismatch()` in `src/2.2/mismatch.cpp`. Complete this function and write at least **three** more tests to verify your code is correct. Two have already been provided for you.

## 2.3. Is It a Perumutation?

The purpose of this exercise is to get experience using different parts of the C++ Standard Library's helpful types and data structures.
In `src/2.3/permutation.h`, there is documentation for a function that, given two strings, determines if one string is a permutation of the other. In this instance, a string $s_1$ is a permuation of another string $s_2$ if:

- $s_1$ and $s_2$ contain the same number of letters
- $s_2$ contains all of the letters of $s_1$, but not necessarily in the same order.

The empty string is a permutation of itself.

You need to implement this function in `src/2.3/permutation.cpp` and write at least two tests in `src/2.3/permutation.test.cpp`.

## 2.4. Sorting Sequences

The C++ Standard Library provides many [algorithms](https://en.cppreference.com/w/cpp/header/algorithm), one very widely-used one being [std::sort](https://en.cppreference.com/w/cpp/algorithm/sort). `std::sort` accepts two iterators denoting a range and performs an optimised sort on that range.

In this exercise, we shall explore what requirements `std::sort` expects this pair of iterators to satisfy and how the [sequence containers](https://en.cppreference.com/w/cpp/container) `std::vector`, `std::list`, and `std::array` satisfy these requirements.

In `src/2.4/assortment.cpp` there are 3 overloads for a function `sort()` which accepts a vector, array, and list of integers. There are also three test cases in `src/2.4/assortment.test.cpp` for sanity checking.
Try implementing each `sort()` function using `std::sort`.

You may notice that the program will not compile.

Consider these questions:

- Where in the code is the compilation error happening?
- **Why** is this compilation error happening? (hint: the compiler error may only be a symptom, not the cause!)
- How might one resolve this error?

Modify your implementation such that now the tests pass.

## 2.5. Mixing Paint

C++ builds upon many constructs found in C. For example:

- `std::function` (and more) over raw function pointers
- `enum class` over `enum`
- `std::optional` over "magic" invalid values such as `nullptr` for an absent `T*`

In this exercise we shall implement a paint-mixing algorithm to gain familiarity with these new constructs. Namely:

- Paints will be represented by an `enum class` called `paint`.
- `sizeof(<any paint>) == 1`.
- The paint colours should be:
  - red
  - green
  - blue
  - yellow
  - cyan
  - magenta
  - brown
- Instead of baking-in which mixing strategy to use, we shall encapsulate it with a `std::function`.
- If a combination of colours doesn't exist, we will denote its absence by a `std::optional`.

In `src/2.5/mixing_paint.h`, there is documentation for a function `mix` that accepts a mixing strategy and vector of paints and mixes them according to the given strategy.
Mixing follows the left-fold algorithm, for example, if we were summing integers...:

```cpp
auto add(int x, int y) -> int { return x + y; }

auto sum(const std::vector<int> &nums, int init) -> int {
    for (auto i : nums) {
        init = add(init, i);
    }

    return init;
}
```

Here, the accumulator is on the left of the `add()` function and the next element in the list is on the right.

There is also documentation for a default mixing strategy `wacky_colour` which you will also need to implement.

Complete these functions in `src/2.5/mixer.cpp` and write at least **two tests** for `mixer` and **two tests** for `wacky_colour` in `src/2.5/mixer.test.cpp`.
