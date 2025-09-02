## 1. Overview of repository

There is a lot going on in this repository, so let's first understand the key components.
* `lib` folder: This is where we can include external libraries (ones that are not part of C++ core and also that we did not write). Right now the only library we have included is `Catch2` which is a testing library part of all of your repos. We will see an example of it's usage below.
* `src` folder: This is the folder you write all of your C++ `.h` and `.cpp` files!
* `build` folder: This is where the compiled binaries from the `src` folder will be written. This folder does not yet exists.
* `.clang-format`: This is a configuration file to tell the `clang-format` command (a linting command) how exactly to lint the code.
* `.gitignore`: This is a configuration file for `git` so it knows what files to ignore. This is particularly useful for the `build` folder as we do not want to commit build binaries to git.
* `CMakeLists.txt`: This is the configuration file for the CMake build system. It requires setup for each project so that the `cmake` command knows how to build the project.

## 2. Setting up a project with CMake

CMake is a build system. We configure CMake, then it goes and generates a delegate build system (with `make`). Basically, it provides a useful interface for us to build more primitive build systems.

Any time the CMakeLists.txt is modified, the buildsystem must be regenerated.

### 2.1. Understanding what is happening

In short, we use the `cmake` program to write a `Makefile` for us so that we can easily compile our programs with `make`. The instructions that `cmake` uses in order to build a `Makefile` is defined in `CMakeLists.txt`.

### 2.2. Using CMake to build a Makefile when we add/remove files

Every time we clone the repo, or whenever we add a new file or remove a file from our project (including subsequent modifications to `CMakeLists.txt`) we need to run this command from the main repo directory:

```sh
$ cmake -B build
```

This tells `cmake` to look in the current project for the `CMakeLists.txt` file (that tells it where the code is) as well as to use an `build` folder to output all the build (compile) files todo.

## 3. Compiling & Running our a program

### 3.1. Compiling your code when you make changes to code

First we navigate to the build directory:
```sh
$ cd build
```

Then we can run and compile our code any time by going:
```sh
$ make main
```

`main` refers to the name of the file containing the main function. This is defined in `CMakeLists.txt` which you can optionally read up on.

This will build all of the "targets" (i.e. 'main files') defined in `CMakeLists.txt`.

In this case, this will build the `main.cpp` file in `src/main.cpp` and it will create a binary in the `build` folder:

### 3.2. Running our code

Whilst still in the `build` folder we can now run our binary:
```sh
$ ./main
```

## 4. Compiling and running the tests

### 4.1. Running a single test

First we navigate to the build directory:
```sh
$ cd build
```

Then we can run and compile a single test (particular test target defined in `CMakeLists.txt`):
```sh
$ make test_sum1
```

Then we can run the binary:
```sh
$ ./test_sum1
```

### 4.1. Running all tests

First we navigate to the build directory

```sh
$ cd build
```

Then we can run and compile all of the targets:
```sh
$ make
```

Then we can run all the binaries:
```sh
$ ctest
```

## 5. Other helpful commands

### 5.1. Linting our code

Because we have a `.clang-format` configuration, we can auto-lint-fix our code at any time by running the command:

```sh
find . -iname "*.h" -o -iname "*.cpp" | xargs clang-format -i
```

### 5.1. Debug V Release

Release builds run quicker than debug builds. That is because debug builds include a large amount of other information compiled into the binary so that debuggers and programs like `gdb` are able to easily navigate and debug the program.

Generally speaking you use a debug build whilst developing, but when the course builds your code it will build a release build. This is because debug builds are quite slow. So if you're doing performance benchmarking on some code you're writing, make sure you test it's speed as a release build.

You can set the debug or release build easily by one of the commands below. Once you run this it will apply for all subsequent builds.
```sh
$ cmake -DCMAKE_BUILD_TYPE=Debug
$ cmake -DCMAKE_BUILD_TYPE=Release
```

## 6. Understanding and working with CMakeLists.txt

### 6.1. The basics

Every repo you have in this course will have a `CMakeLists.txt` file. In this file will always be the same top bits of code:
```txt
# ------------------------------------------------------------ #
# -------------- DO NOT TOUCH BELOW THIS LINE ---------------- #
# ------------------------------------------------------------ #

# this must be the first line of a CMake script.
# sets the lowerbound on what CMake version can be used.
cmake_minimum_required(VERSION 3.0)

# the name of this CMake project and what language it uses
# we could list more languages if we were using more.
project(COMP6771_LAB_001 LANGUAGES CXX)

# we use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# this is helpful for editors like VS Code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# helpful compiler flags for gcc/clang
# the descriptions for these flags can be found on the GNU Compiler Collection's webpage.
add_compile_options(
  -Wall
  -Wextra
  -Werror
  -pedantic-errors
  -Wconversion
  -Wsign-conversion
  -Wdouble-promotion
  -Wcast-align
  -Wformat=2
  -Wuninitialized
  -Wnull-dereference
  -Wnon-virtual-dtor
  -Woverloaded-virtual
  -Wdeprecated-copy-dtor
  -Wold-style-cast
  -Wzero-as-null-pointer-constant
  -Wsuggest-override
  -fstack-protector-strong
)

# debug builds should be compiled with sanitizers
# sanitizers are small libraries that check things like buffer overrun with minimal runtime overhead.
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_EXE_LINKER_FLAGS_DEBUG_INIT "-fsanitize=address,undefined")
set(CMAKE_CXX_EXE_LINKER_FLAGS_RELWITHDEBINFO_INIT "-fsanitize=address,undefined")


# add the testing library Catch2
enable_testing()
add_library(catch2_main lib/catch2_main.cpp)
target_include_directories(catch2_main PUBLIC lib)
# link the library so that other programs can get it
link_libraries(catch2_main)

# ------------------------------------------------------------ #
# -------------- DO NOT MODIFY ABOVE THIS LINE --------------- #
# ------------------------------------------------------------ #
```

From here, we start adding things ourselves! There are really only 3 things that we end up adding to the bottom of this. Typically we will add them in the following order that they are described.

### 6.2. "Library" files

Library files are `.cpp` files that have no main function, and are not test functions. They typically have functions in them that are _used by_ main or test files.

Whenever we add a library file we do the following. 

```txt
add_library(sum src/sum.cpp)
link_libraries(sum)
```

In this case we are saying that for CMake purposes the file `src/sum.cpp` can be referred to as "sum" and then we are linking it so that other `.cpp` files are able to use the contents of that file.

### 6.3. "Main" files

Main files are `.cpp` files with an `int main` in them.

Whenever we add a main file we do the following. 

```txt
add_executable(main src/main.cpp)
```

In this case we are saying that for CMake purposes the file `src/main.cpp` has a main function can be referred to as `main`.

Because it is an executable this also means that we can build and run this particular file via going to the `build` folder:
```sh
$ make main
$ ./main
```

### 6.4. "Test" files

Test files are `.cpp` files with a CATCH2 `TEST_CASE` function in them.

Whenever we add a test file we do the following. 

```txt
add_executable(test_sum1 src/sum1.test.cpp)
add_test(test_sum1 test_sum1)
```

The first line does the same thing as the main function. It allows us to build and run that particular test by running:
```sh
$ make test_sum1
$ ./test_sum1
```

The second line simply means that when we run `ctest` that particular executable picks it up.

### 6.5. Final Reminder

Don't forget that every time we make a modification to `CMakeLists.txt` we need to run in the repo directory:
```sh
$ cmake -B build
```





