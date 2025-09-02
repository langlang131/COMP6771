# Week 4 Exercises

Q4.`[abc]`. are extra questions.  
These are useful for your theoretical understanding of C++ and can be done independently.

## Q4.1. The `xector`

For all parts of Q4.1, refer, refer to the following spec:

The `xector` \(pronounced "ex-tor\) is a special `std::vector<std::string>`.  
Although it can store any `std::string`, it only considers strings that contain at least one `'x'` character in lower case - we will call this **the criteria**.  
Here is a brief test case to understand how the `xector` works.

```cpp
TEST_CASE("xector demo") {
    auto xec = xector{"apple", "extreme"};
    CHECK(xex.size() == 1);
    xec.push_back("jon");
    CHECK(*xec.last() == "extreme");
}
```

This question is a code review so you don't need to consider whether the code is logically correct - you can assume it all works.

The full interface for the `xector` can be found in `src/x_vector.h`.

### Q4.1.1. Implementation Code Review

You have been asked to review the implementation of an `xector` against the course's C++ best practices style guide.  
It is located in `src/4.1/x_vector.cpp`.  
Try go through each outlined point in the marking criteria.

- 2.1. Miscellaneous
- 2.2. Comments
- 2.3. Custom Containers
- 2.4. Avoiding C-style
- 2.5. Using Modern C++

### Q4.1.2. Test Code Review

You have also been asked to review the tests written to accompany the implementation.  
The tests are in `src/4.1/x_vector.test.cpp`.  
Conduct a code review and suggest what improvements can be made.  
As a guide, here are the outlined points from the assigment testing marking critera.

- Correctness
- Coverage
- Brittleness
- Clarity
- Simplicity

## Q4.2. Constructor and Destructor Order

Refer to this struct for Q4.2.

```cpp
#include <list>

struct object {
    object() {
        std::cout << "ctor\n";
    }

    object(const object &) {
        std::cout << "copy-ctor\n";
    }

    ~object() {
        std::cout << "dtor\n";
    }
};
```

### Q4.2.1.

This is the output of a program using a `struct object.`

```txt
ctor
dtor
```

Go through each line in its `main` \(including the comment `// end of scope`\) and explain what:

- it does in relation to constructing and destructing objects;
- output it is responsible for.

```cpp
auto main(void) -> int {
    std::list<object *> l;
    object x;
    l.push_back(&x);
    // end of scope
}
```

### Q4.2.2.

The program has now been changed so that this is the output.

```txt
ctor
copy-ctor
dtor
dtor
```

Follow the same process for its new `main` function.

```cpp
auto main(void) -> int {
    std::list<object> l;
    object x;
    l.push_back(x);
    // end of scope
}
```

## Q4.3. Construction Confusion

Write the alternative which most accurately answers the questions below.

1. Consider the below code snippet:

```cpp
std::vector<int> a(1, 2);
```

What is this line doing?

- a) Default construction.
- b) Construction via Direct Initialisation.
- c) Function declaration.
- d) From C++11 onwards, this is invalid syntax; won't compile.

2. Consider the below code snippet:

```cpp
std::vector<int> a{1, 2};
```

What is this line doing?

- a) From C++11 onwards, this is invalid syntax; won't compile.
- b) Function declaration.
- c) Construction via Aggregate Initialisation.
- d) Construction using an Initialiser List.

3. Consider the below code snippet:

```cpp
std::vector<int> b = {1, 2};
```

What is this line doing?

- a) Construction via Copy Initialisation.
- b) Construction by Assignment Initialisation.
- c) Construction using an Initialiser List.
- d) Construction via Direct Initialisation.

4. Consider the below code snippet:

```cpp
std::vector<int> a{1, 2};
std::vector<int> c = a;
```

What is line 2 doing?

- a) Construction via Copy Initialisation
- b) Copy assignment of `a` to `c`.
- c) Construction via Assignment Initialisation
- d) `c` is "stealing" the data members of `a` to construct itself.

5. Consider the below code:

```cpp
std::vector<int> a{1, 2};
std::vector<int> c;
c = a;
```

What is line 3 doing?

- a) Reconstruction of `c` from `a`.
- b) Construction via Copy Initialisation.
- c) Copy assignment of `a` to `c`.
- d) Aggregate assignment of `a` to `c`.

## Q4.4. Ferrari++

Implement the following class specification in `src/4.4/ferrari.h` and/or `src/4.4/ferrari.cpp`.

| Method                                           | Description                                                                                                                                                                                                                                         |
| ------------------------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `ferrari(const std::string &owner, int modelno)` | This constructor should initialise the object state to keep track of the owner name and model number. Speed is initially 0.                                                                                                                         |
| `ferrari()`                                      | This constructor should default-initialise the object's state so that its owner name is "unknown" and its model number is `6771`. Speed is initially 0.                                                                                             |
| `std::pair<std::string, int> get_details()`.     | Returns this Ferrari's owner and model number.                                                                                                                                                                                                      |
| `void drive(int spd)`.                           | Start driving at speed `spd`. If no speed is given, it should default to `88`.                                                                                                                                                                      |
| `std::string vroom()`.                           | Returns a string depending on how fast this Ferrari is currently moving. If the speed is strictly less than 20, it should return the empty string. If `20 <= speed < 80`, it should return "vroom!!". Otherwise, it should return "VROOOOOOOOM!!!". |

**Note**: You need to ensure your code is const-correct. Which methods should be const-qualified has intentionally been left out.

When implementing this class, you should ensure you are using modern C++ best practices, such as member initialiser lists, delegating constructors, etc. You should check with your tutor to make sure that your style aligns with modern practices.

In `src/4.4/ferrari.test.cpp`, you will also need to write at least **five** tests to make sure your code is correct.

---

## Q4.a. Defaults & Deletes

Write the alternative which most accurately answers the questions below.

1. Consider the below code:

```cpp
struct point2i {
    int x;
    int y;
};
```

Is this class-type default-constructible and why?

- a) No: We need to opt-in to a default aggregate initialiser.
- b) Yes: default aggreggate-initialisation would leave `x` and `y` uninitialised.
- c) No: This is a C-style struct; it has no default constructor.
- d) Yes: default aggregate-initialisation would set `x` and `y` to `0`.

2. Consider the below code:

```cpp
class employee {
public:
    employee(int employeeno);

private:
    int employeeno;
};
```

Is this class-type default-constructible and why?

- a) Yes: the compiler can automatically synthesise the default constructor if we don't provide one.
- b) No: a user-provided constructor prevents automatic synthesis of a default constructor.
- c) No: we have not provided an in-class member initialiser.
- d) Yes: `int` itself has a default constructor, so `employee`'s default constructor simply delegates to `int`'s one.

3. Consider the below code:

```cpp
struct point2i {
    point2i() = default;
    point2i(int x = 42, int y = 6771);

    int x;
    int y;
};
```

Is this class-type default-constructible and why?

- a) No: the two provided constructors are ambiguous when called with 0 arguments, so this code won't compile.
- b) Yes: we have explicitly defaulted the default constructor.
- c) Yes: Though both constructors can be called with 0 arguments, the compiler prefers the explicitly defaulted default-constructor.
- d) Yes: Though both constructors can be called with 0 arguments, in overload resolution the second constructor has higher priority, so it will be called.

4. Consider the below code:

```cpp
struct point2i {
    point2i() = default;
    point2i(const point2i &) = delete;
    point2i(point2i &&) = delete;
};

point2i get_point() { return point2i{}; }

point2i p = get_point();
```

Will this code compile and why?

- a) Yes: the default constructor will be called for `p`'s initialisation
- b) No: `point2i(point2i &&)` is invalid syntax.
- c) No: `point2i` is not copyable at all, so `p` cannot be initialised.
- d) Yes: `point2i` has no data members, so even though the copy and move constructors are deleted, the compiler knows that those constructors would have had no effect anyway.

5. Consider the below code:

```cpp
struct guard {
    guard() = default;
    guard(const guard &) = delete;
    guard(guard &&) = delete;
};

struct outer {
    guard g;
};
```

Is the `outer` class-type default-constructible or copyable and why?

- a) Neither default-constructible nor copyable: we have not explicitly told the compiler that we want `outer` to have the default constructor and copy/move constructors generated for us.
- b) Default-constructible but not copyable: `guard`'s explicitly deleted copy/move constructor prevents the implicitly generated copy/move constructors for `outer`. For a similar reason, `guard` does allow for the implicitly generated default constructor.
- c) Won't compile: `guard` prevents the implicit copy/move constructors for `outer` to be generated, as well the default constructor. Therefore, this class cannot be constructed, which is a compiler error.
- d) Default-constructible and copyable: `guard` has no effect on the implicitly generated default, copy, and move constructors for `outer` since it is a `struct`. If `outer` were a `class`, it would only be default-constructible, however.

## Q4.b. Value-centric C++ (1/2)

C++ has value semantics by default (rather than reference semantics like other languages, such as Java). Classes allow developers to write their own value-types that act, look, and feel like the regular built-in types like `int` or `double`.

In this exercise we begin to create our own value-type representing a rational number. Rational numbers are any number that can be represented as a fraction with integer numerator and denominator. Note that `x/0` for any `x` is not a rational number.

In `src/4.7/rational.cpp` and associated files, implement the `rational_number` class and write at least **three** tests for it.

The class should have:

- a static public data member `null`, which represents "no" rational number. This should be implemented as an empty `std::optional<rational_number>`.
- a public static member function `auto make_rational(int num, int denom) -> std::optional<rational_number>` that returns either a rational number or the above static data member if `denom == 0`.
- a private constructor, so that a user cannot accidentally create an invalid rational number (all creation must use `make_rational`).
- the four arithmetic operations `add(), sub(), mul(), div()` as friend functions so that, for `r1` and `r2` which have type `rational_number`, one may write: `add(r1, r2)`, etc.. The return type for `add(), sub(), mul()` should be `rational_number`, but for `div()` it should be `std::optional<rational_number>`.
- the two equality operations `eq` and `ne` so that, for `r1` and `r2` which have type `rational_number`, one may write `if (eq(r1, r2)) { ... }`. The return type for both of these functions should be `bool`.
  - **Hint**: equality for fractions doesn't necesarily mean the numerators and denominators are equal! E.g., 1/2 == 2/4...
- a public method `auto value() -> double` which returns the quotient of the numerator and the denominator as a `double`.

The size of every instance of your class should be no bigger than `16 bytes`.

## Q4.c. GLSL++

The Open**GL** **S**hader **L**anguage (GLSL) is a C/C++-like language used to write shader programs that can run on GPUs.

One convenient feature of the GLSL built-in type `vec3` is that you can access its components by various names. For example:

- `v.x`: access the 1st component in `v` as a spatial dimension.
- `v.r`: access the 1st component in `v` as a colour dimension.
- `v.s`: access the 1st component in `v` as a texture dimension.

In all, there are three sets of syntactic sugar:

- `x`, `y`, `z`: for 1st, 2nd, and 3rd componenets of a `vec3`.
- `r`, `g`, `b`: for 1st, 2nd, and 3rd componenets of a `vec3`.
- `s`, `t`, `p`: for 1st, 2nd, and 3rd componenets of a `vec3`.

In `src/4.c/vec3.h` and/or `src/4.c/vec3.cpp`, complete the below specification.
When you are done, write at least **three** tests in `src/4.c/vec3.test.cpp`.

### Public Data Members

| Data Member               | Type     |
| ------------------------- | -------- |
| `v.x`<br/>`v.r`<br/>`v.s` | `double` |
| `v.y`<br/>`v.g`<br/>`v.t` | `double` |
| `v.z`<br/>`v.b`<br/>`v.p` | `double` |

`x`, `r`, and `s` should refer to the same data member.
Likewise, `y`, `g`, and `t` should refer to the same data member.
Similarly, `z`, `b`, and `p` should refer to the same data member.

Therefore, `sizeof(vec3) == 3 * sizeof(double)` should be true.

**Hint**: you may find [this page on unions](https://en.cppreference.com/w/cpp/language/union) useful. Particularly, anonymous unions inside of class-types.

### Constructors

```cpp
/* 1 */ vec3();
/* 2 */ vec3(double c);
/* 3 */ vec3(double a, double b, double c);
```

1. Default constructor.

- Initialise this vector to contain 0 in each component.

2. Broadcast Component Constructor.

- Initialise this vector, setting all components to `c`.

**Note**: you must ensure the below code snippet cannot happen:

```cpp
// should fail to compile.
vec3 foo() { return 1.0; }
vec3 v = foo();
```

3. All Component Constructor.

- Initialise this vector so the first component is `a`, the second is `b`, and the third is `c`.

### Copy-control

Your class should be copyable and destructible.

### Member Functions.

None.

Aside from the constructors, `vec3` is intended to be a plain data struct, so it is OK to access its data members directly.
