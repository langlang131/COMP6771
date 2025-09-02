# Week 1 Exercises

## Q1.1. Your first C++ Program (compared to your first C program)

Through university, whether having taken COMP1511 or COMP9024, you have written code in C and should know how to read in numbers with `scanf`. In C++, we use `std::cin` from `<iostream>` to read character input instead! Here is an example of how `std::cin` can be used:

```cpp
auto i = 0;
if (not (std::cin >> i)) {
  std::cerr << "Something went wrong while reading an integer, bailing...\n";
  return 1;
}

std::cout << "Value of i: " << i << '\n';
```

Write a program in `src/1.1/add_numbers.cpp` that reads in two integers and prints out their sum.

Build your program before you run it.

1. Press _Ctrl+Shift+P_, type `CMake: Build Target`, and press Enter.
2. You should see a blank textbox. Type `add_numbers` and press Enter.
3. An output window should appear, detailing the process.

Open the terminal tab (it's next to the output tab) on the window that just detailed the output above.

Type the following commands, and the behaviour should follow. Alternatively, The VSCode extension or similar can have functionality to make and run the program as well.

```sh
$ ./build/add_numbers
Please enter two numbers: 2 3
Sum: 5
```

```sh
$ ./build/add_numbers
Please enter two numbers: 2 x
Something went wrong while reading an integer, bailing...
```

## Q1.2. Constant Referencing

The `const` keywords and `&` reference are powerful components of the C++ language, and understanding how to use them effectively will be a great asset for your assignments.

Are there any errors in the following blocks of code? If so what are they?

```cpp
auto i = 3;
i = 4;
```

```cpp
const auto j = 5;
--j;
```

```cpp
auto age = 18;
auto& my_age = age;
++my_age;
```

```cpp
auto age = 21;
const auto &my_age = age;
--my_age;
```

## Q1.3. Using and Testing `std::vector`

One powerful feature that C++ holds over C is the Standard Library. These are a collection of useful containers, algorithms and functionality that well extends beyond what the standard C libraries offer, and are the foundation for what makes modern C++ programming.

One of the most widely used containers from the C++ Standard Library is `std::vector`. A vector is a dynamic array that looks after its own memory and allows elements to be inserted, retrieved, compared for equality, etc.

Alot can be done with a vector and the purpose of this exercise is to gain familiarity with its various operations (called _member functions_ or _methods_).

In `src/1.3/fib_vector.cpp`, there is an incomplete implementation of a function that calculates all of the [Fibonacci numbers](https://en.wikipedia.org/wiki/Fibonacci_number) and returns them in a `std::vector<int>` as well as a few failing tests.

Write a proper implementation of `fibonacci()` and more tests so that you more become familiar and confident with using a vector (and also with testing!).

Hint: some of the most widely used methods on vectors are:

- `push_back(elem)`: adds an elements to the vector at the end
- `size()`: returns how many elements are currently in the vector
- `empty()`: returns true if and only if `size() == 0` (**N.B.** this does not `clear()` the vector!)
- `at(n)`: get the nth element from the vector. Can also use `[]`.

A full description of these methods can be found [here](https://en.cppreference.com/w/cpp/container/vector).

## Q1.4. Introduction to Testing using a Set Difference

In `src/1.4/setdiff.h` there is a documentation for a function that removes elements in one vector from another. In the provided test stub in `src/1.4/setdiff.test.cpp`, write **three** or more _unit tests_ for this function. Considerations include:

- a test for invalid input
- a test for an _edge_ case
- a test for the average use case

When you are happy with the tests, implement the function in `src/1.4/setdiff.cpp` so that your tests pass.

Some questions to consider as you write these additional tests:

- What is a `TEST_CASE`?
- What is a `CHECK`? How is it different to an `assert`?
- What is a `REQUIRE`? How is this different to an `assert`?
- What are `SECTION` blocks in Catch2, and how do they make testing easier?

## Q1.5. Gotta Sort It Out

Write a function, called `sort3` in `src/1.5/sort3.cpp`, which takes three `int` references and sorts them in ascending order.

Then, write **two** test cases in `src/1.5/sort3.test.cpp` to confirm that `sort3` is correct.

You should then write an overload for `sort3` so that it also sorts three `std::string` references. Don't forget to write at least **two** more test cases!
