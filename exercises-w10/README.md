# Week 10 Exercises - Exam Preparation

This week's exercises are designed to help you prepare for the final exam by reviewing key concepts covered throughout the course. The exercises focus on theoretical understanding and practical application of C++ concepts.

You can ask any questions that are COMP6771 related, your tutor will be happy to answer them! 

## Q10.1. Theory Questions

For each of the following topics, write a detailed explanation and provide examples where appropriate:

1. C++ Basics and STL
   - Compare and contrast `std::vector`, `std::list`, and `std::deque`. When would you use each?
   - Explain the difference between `push_back()` and `emplace_back()` in STL containers.
   - What are the advantages and disadvantages of using range-based for loops?

2. Class Types
   - Explain the difference between composition and inheritance. When would you use each?
   - What is the purpose of virtual destructors? When are they necessary?

3. Operator Overloading
   - What are the key principles and best practices for operator overloading in C++?
   - Explain the difference between member and non-member operator overloads.

4. Custom Iterators
   - How do you implement custom iterators in C++? What are the essential iterator concepts?
   - Explain the iterator categories (eg. Forward Iterator, Bidirectional) and their requirements.

5. Exception Handling
   - What is exception handling, why do we need it? and give an usage example.
   - When should you use exceptions versus error codes?
   - What is the purpose of the `noexcept` specifier?

6. Resource Management and Smart Pointers
   - Explain RAII and its importance in C++.
   - Compare `std::unique_ptr`, `std::shared_ptr`, and `std::weak_ptr`.
   - What are the benefits of using smart pointers over raw pointers?
   - Explain the RAII (Resource Acquisition Is Initialization) pattern in detail. How does it relate to object lifetime management?
   - What are the main advantages of using smart pointers over raw pointers? Explain how they prevent memory leaks.

7. Polymorphism
   - Compare and contrast static and dynamic polymorphism.
   - What is the difference between static and dynamic polymorphism? Explain when each is resolved and provide examples.

8. Metaprogramming
   - What is metaprogramming and what are the benefit of using it in C++? (Give at least three benefits)
   - What are type traits in C++? Give an example of how they are used to write generic code.
   - How do type traits work in C++? Explain their role in compile-time type checking and provide examples.

## Q10.2. Sample Exam Question
**Note:** This is designed as a comprehensive practical exam question that cannot be completed within a 1-hour tutorial session. Students are encouraged to work on this exercise at home and bring specific questions to the tutorial for discussion and clarification.
### Q10.2.1 Practice Implementation
Implement a template class `SmartContainer` in `src/10.2/smart_container.h` that demonstrates your understanding of modern C++ concepts. Your implementation must follow the specification below:

### Required Private Internal Representation

| Name      | Type                        | Description                                                      |
| --------- | --------------------------- | ---------------------------------------------------------------- |
| data_     | `std::unique_ptr<T[]>`      | A unique pointer to a heap-allocated array of elements of type T. |
| size_     | `std::size_t`               | The number of elements currently stored in the container.         |
| capacity_ | `std::size_t`               | The current capacity of the container.                            |

### Constructors

```cpp
/* 1 */ SmartContainer();
/* 2 */ SmartContainer(std::initializer_list<T> ilist);
/* 3 */ SmartContainer(const SmartContainer& other);
/* 4 */ SmartContainer(SmartContainer&& other) noexcept;
```

1. **Default constructor**
   - Constructs an empty container with zero size and capacity.

2. **Initializer list constructor**
   - Constructs a container with elements from the initializer list.
   - The size and capacity are set to the number of elements in the list.

3. **Copy constructor**
   - Constructs a container by deep-copying another container.
   - After construction, `*this == other` should be true.

4. **Move constructor**
   - Constructs a container by stealing the internals of `other`.
   - After construction, `other.size() == 0` and `other.data_ == nullptr` should be true.

### Operator Overloads

```cpp
SmartContainer& operator=(const SmartContainer& other);
SmartContainer& operator=(SmartContainer&& other) noexcept;
T& operator[](std::size_t pos);
const T& operator[](std::size_t pos) const;
bool operator==(const SmartContainer& rhs) const noexcept;
```

- **Copy assignment**: Deep-copies the contents of another container.
- **Move assignment**: Steals the internals of another container.
- **Element access**: Returns a reference to the element at the given position. No bounds checking.
- **Equality**: Returns true if both containers have the same size and all elements are equal.

### Member Functions

```cpp
void push_back(const T& value);
void push_back(T&& value);
template<typename... Args>
void emplace_back(Args&&... args);
void clear() noexcept;
bool empty() const noexcept;
std::size_t size() const noexcept;
T& at(std::size_t pos);
const T& at(std::size_t pos) const;
```

- **push_back**: Adds an element to the end of the container, reallocating if necessary.
- **emplace_back**: Constructs an element in-place at the end of the container.
- **clear**: Removes all elements from the container.
- **empty**: Returns true if the container is empty.
- **size**: Returns the number of elements in the container.
- **at**: Returns a reference to the element at the given position, throws `std::out_of_range` if out of bounds.

### Iterator Support

- Implement custom iterator and const_iterator classes to support range-based for loops and standard iterator operations.
- Provide `begin()`, `end()`, `cbegin()`, and `cend()` member functions.

### Exception Safety

- All operations must provide strong exception safety where possible.
- Accessing out-of-bounds elements with `at()` must throw `std::out_of_range`.

### Other Notes

- You are not allowed to add, remove, or modify the specification above.
- Your implementation should demonstrate:
  - Proper use of templates
  - Resource management (RAII)
  - Exception safety
  - Iterator concepts
  - Modern C++ features

A `main.cpp` file is provided in `src/10.2/` to show the expected result when your implementation is complete.

Write tests in `src/10.2/smart_container.test.cpp` to verify all functionality.

Your implementation should demonstrate:
- Understanding of memory management
- Proper use of templates
- Exception safety
- Iterator concepts
- Modern C++ features

### 10.2.2 Theory Questions

Answer the following questions in your solution file. Each question is worth 2 marks.

1. Explain the benefits and pitfalls of operator overloading for domain-specific containers like `SmartContainer`. What considerations should be taken when designing such operators? (2 marks)

2. How does a custom iterator improve the flexibility of the `SmartContainer` class? What requirements must it satisfy to work with range-based for loops? (2 marks)

3. Why is defining a custom copy constructor important for containers that use raw memory? What could go wrong if we relied on the default copy constructor? (2 marks)

4. Describe a scenario where not throwing an exception in out-of-bounds access could lead to a critical bug in a container system. (2 marks)

5. What are the memory management risks in building your own container class, and how does RAII help mitigate these risks? (2 marks)

Total: 10 marks

Note: Your answers should be concise but complete. Focus on demonstrating your understanding of the key concepts rather than writing lengthy explanations. 