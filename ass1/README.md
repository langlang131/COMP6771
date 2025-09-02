# Assignment 1 - Word Break

**Please `git pull` frequently to get the latest changes.**

Please run ./util/setup.sh in your terminal before you begin. This will set up some checks in relation to the "Git Commit Requirements".

## Change Log

- 05/06: Added clarification for the order in which sentences should be returned.

[toc]

## 1. Overview

In Week 2 we are learning about C++ libraries and this assignment is your chance to practise those
skills.

Now that you’ve been introduced to the C++ Standard Library, it’s time to put that knowledge to use. In the role of client, the low-level details have already been dealt with, and you can focus your attention on solving more pressing problems. Having a library of thoroughly tested and reviewed types designed by field experts vastly broadens the kinds of tasks you can “easily” tackle. In this first assignment, you’ll write the back-end for a program that heavily leverages the Standard Library to do nifty things. It might sound a little daunting at first; but given the power tools in your arsenal, you can focus on solving the problem at hand, instead of worrying about how to implement everything from scratch. Let’s hear it for well-designed code!

This assignment has several purposes:

1. To explore C++’s value semantics.
2. To stress the notion of modularity as a mechanism for managing data and providing functionality without revealing the implementation.
3. To become more familiar with C++'s type system.
4. To gain familiarity with the C++ Standard Library.

Leveraging `std::vector` and `std::unordered_set` are critical for solving this challenge. Naturally, in english, we seperate words using spaces to indicate when one word ends and another word starts. However, pretend for a moment there was no such thing as whitespace to seperate words (this is commonly seen in other languages such as Chinese or Japanese, and even in older languages like Ancient Greek. It is often a feature of cryptography too.) For example, you might have the following sentence.

```txt
THISISANINTERESTINGWAYOFWRITINGASENTENCEIWONDERIFITWOULDMAKEANINTERESTINGASSIGNMENT
```

It may take a couple of moments to work out where the spaces should go, but of course, sometimes the spelling of words may become jumbled without these spaces. For example, here are some ways to split up the string of characters `DOGSANDRAGONFLY`:

```txt
DOGS AND RAG ON FLY
DOG SAND RAG ON FLY
DOGS AN DRAGONFLY
DOGS AN DRAGON FLY
DOGS AN DRAG ON FLY
```

For this particular challenge, we want you to find all ways of splitting up the text such that the number of words is minimised. In the example above, that would only leave `DOGS AN DRAGONFLY`. The back-end that you will write takes a string to be broken up into words, and a lexicon, and returns a vector of valid word sentences with the spaces. Note that the sentence doesn't have to make sense, only that the words the sentence is split up into are valid words in the lexicon.

Finally, if there are multiple sentences with the least number of words, then you can return them in any order.

## 2. Understanding a Word Break Implementation

A few of these tasks deserve a bit more explanation. For example, you'll need to be breaking up the string into valid words only. You might try determining what substrings of the larger string are actually valid words. You could try looping through, seeing what is a valid word and saving it, or you may try something more targeted. Either way, you must ensure your returned answers are only made of valid words from the lexicon.

Another issue is the minimising of the number of words in the final sentences. To optimise for this, you may want to consider if you're exploring down one branch whether there is a path you have already explored that gets to the same spot in fewer words. For example, if you have one branch that contains the word `ONTO` and another branch uses those same characters in the same positions as `ON TO`, it will always be better to use fewer words (assuming the split isn't prefixes and suffixes of other words). Remember that because C++ has value semantics, you’re able to copy vectors via copy construction (e.g. `auto sentence_clone = sentence;`) and copy assignment (e.g. `sentence_clone = sentence`).

## 3. The Task

This generator might seem like it’s a panacea, but it still benefits from a step-by-step development plan to keep things moving along.

- **Task 1** --- _Familiarise yourself with the libraries available._ You don’t need to deep-dive, but it would be a smart idea to read up on `std::vector` and `std::unordered_set`, from the standard library. You shouldn’t worry about their implementation details: focus on the interfaces, and how you use them in practice.
- **Task 2** --- _Test design._ We’ve provided you with a very simple test case to show you how to use the test library. You should add more `TEST_CASE`s underneath, so you have a suite of checks to make sure you catch any logic errors in your generator. We adopt Google’s Beyoncé rule in this class: “if you liked it, you should have put a test on it”. Test words that are short (one or two letters) and test words that are longer.
- **Task 3** --- _Design your algorithm._ Be sure you understand the backtracking algorithm on paper, and what types you will need to use.
- **Task 4** --- _Lexicon handling._ Set up an `std::unordered_set` object with the large lexicon, read from a data file. There’s a utility function called `word_break::read_lexicon` that you will also need to implement. If you find yourself struggling to write `word_break::word_break()`, it may be helpful to take a break by implementing an easier function.
- **Task 5** --- _Write `word_break`._ With your design in hand from Task 3, you can rough out an implementation of `word_break()` and progressively improve it as you understand the problem and optimise more and more.

### 3.1. Assumptions

- You can assume that the `string_to_break` will only be made up of lowercase english letters.
- You can assume that `word_break::word_break` will always be given path to a valid file in the correct format
- You can **NOT** assume that there will always be a way of breaking up the string into valid words.

### 3.2. Implementation hints

Again, it’s all about leveraging the libraries at your disposal --- you’ll find your job is just to coordinate the activities of your objects to do the search.

- [`std::vector`][vector] maintains a contiguous sequence of elements, and has random access. Benchmarks have shown that its contiguous storage makes it the fastest and smallest container in many situations (even when computer science theory tells us that a linked list would be better!).
- [`std::unordered_set`][us] (note 1) is the hash-set that we use for the input lexicon, and is recommended for any internal lexicons you might use.
- [Algorithms] are powerful tools for describing what you want your program to do.

## 4. Getting Started

If you haven't done so already, clone this repository.

```sh
$ git clone gitlab@nw-syd-gitlab.cseunsw.tech:COMP6771/25T2/students/z0000000/ass1.git
...
```

(Note: Replace z0000000 with your zid)

Most of the files here will be quite familiar to you. But there are key files in the `src` directory:

- `english.txt`: The file where the lexicon is.
- `main.cpp`: The file where a main function exists for debugging.
- `word_break.cpp`: The library file that has the word break generator function.
- `word_break.h`: The header file for the word break generator library file.
- `word_break.test.cpp`: The test file where you can write tests to help debug your code.
- `word_break_benchmark.test.cpp`: A test file to help you understand how you're performing with the hardest test.

### 4.1. Setup

Remember, since we just cloned, we will need to run `cmake -B build` to configure the makefile.

### 4.2. Running the tests

Now that we've configured cmake, we can navigate to `build` and run:

```sh
$ make
...
$ ctest
...
```

This will show you the output from your tests.

### 4.3. Adding more tests

Part of your assignment mark will come from the quality and extensiveness of tests that you write.

You can add more tests to `src/word_break.test.cpp`. You are not allowed to add any new files.

You should consider the order of how your tests are run: they are executed in order from the top of the file to the bottom. Likewise, it doesn't make sense to test properties of your algorithm that logically rely on prior testable facts to be true. E.g., it makes more sense to test your code does the right thing for when there's no valid sentences versus one or more.

### 4.4. Measuring your performance

There is a **12 second time limit** per test that we will enforce when marking your assignment. For the average student, this means that some of the hardest test cases may not run fast enough with your algorithm and you may fail the latter tests due to timeout.

We have provided the hardest test case we will test against in `src/word_break_benchmark.test.cpp`. If you can successfully pass this test within 12 seconds **ON THE CSE MACHINES** then we are providing you a guarantee that you will not fail those tests from a timeout. If you exceed 12 seconds for that test, you may still get the marks, but it's just something we can't guarantee.

Please note: This benchmark test is VERY difficult. If your code takes an hour to run this test that's not something that should make you panic. It's quite easy to fall in the time limit for most of the tests. Don't stress and just make sure earlier tests fall in the 12 second time limit on CSE machines.

To measure your performance:

1. Make sure you change CMake to build in `[Release]` mode by running `cmake -DCMAKE_BUILD_TYPE=Release -B build` in the project directory. This will remove debug symbols and other things, which will mean your code runs faster, but is near impossible to debug for mere mortals. This is usually what is done when you're finished developing and ready for release.

2. In the `build` folder, build with `make word_break_benchmark_exe` and run `time ./word_break_benchmark_exe` to run the benchmark. It will output something like this below. The time you should measure yourself against is the "user" time. If this is under 12 seconds then you're all good.

    ```txt
    real    1m45.089s
    user    1m44.497s
    sys     0m0.560s
    ```

3. Once you are happy with your performance, don't forget to change CMake back to `[Debug]` by running `cmake -DCMAKE_BUILD_TYPE=Debug -B build` in the project directory. This will add back debug symbols in so that you can more effectively debug your code.

### 4.5. Compiling with main.cpp

We have provided a `main.cpp` file that you can use a scratchpad and informal place to test your code. This is a great place to start and to debug, but as your program develops you should be relying on running tests.

Remember, to compile your main function you simply run `make debugging` followed by running `./debugging` in the `build` folder.

## 5. Marking Criteria

This assignment will contribute 15% to your final mark.

The assessment for the assignment recognises the difficulty of the task, the importance of style, and the importance of appropriate use of programming methods (e.g. using while loops instead of a dozen if statements).

<table class="table table-bordered table-striped">
  <tr>
    <td align=right>50%</td>
    <td>
      <b>Correctness</b><br />
      The correctness of your program will be determined automatically by tests that we will run against your program. You will not know the full sample of tests used prior to marking. Your program must also find the sentence(s) for a given input in the time limit specified above.
    </td>
  </tr>
  <tr>
    <td align=right>25%</td>
    <td>
      <b>Your tests</b><br />
      You are required to write your own tests to ensure your program works. You will write tests in the <code>word_break.test.cpp</code> file. Please read the <a href="https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md">Catch2 tutorial</a> or review lecture/lab content to see how to write tests. Tests will be marked on several factors. These include, <em>but are not limited to</em>:
      <ul>
        <li>Correctness — an incorrect test is worse than useless.</li>
        <li>
          Coverage - your tests might be great, but if they don't cover the part that ends up failing, they weren't much good to you.
        </li>
        <li>
          Brittleness — If you change your implementation, will the tests need to be changed (this generally means avoiding calling functions specific to your implementation where possible - ones that would be private if you were doing OOP).
        </li>
        <li>
          Clarity — If your test case failed, it should be immediately obvious what went wrong (this means splitting it up into appropriately sized sub-tests, amongst other things).
        </li>
        <li>
          Simplicity — Your test cases should be simple, avoiding things like loops and other complex conditional logic so that the likelihood of of errors being introduced in your tests is reduced.
        </li>
      </ul>
      At least half of the marks of this section may be awarded with the expectation that your own tests pass your own code.
    </td>
  </tr>
  <tr>
    <td align=right>25%</td>
    <td>
      <b>C++ Style & Best Practices</b><br />
      Your adherence to good C++ best practices as shown in lectures and as documented on the course website. This is based on how well you use modern C++  methodologies taught in this course as opposed to using backwards-compatible C methods. This section will also include marks for how well you follow general best porgramming practices, including maintaining small functions, reducing nesting in loops, having meaningful variable names, etc. You may also receive a penalty for this section if your code is not formatted perfectly according to the clang-format config file in your repo.
    </td>
  </tr>
</table>

Please note: Significant penalties may apply if you do not comply with the 'Git Commit Requirements' requirements as described in section 6 below.

## 6. Git Commit Requirements

It's imperative that we are able to track your progress when marking.

For assignment 1, there are some requirements for us to track your ongoing progress:

1. You must make commits on at least 3 unique days prior to due date.
2. All of your commits to master must successfully compile (according to the pipeline). You are given 3 exceptions.
3. Your commits must be meaningful in description (e.g. "Continued work on loop speed")
4. Each commit include no more than 50 lines additions of code (this may differ in future assignments). You are given no exceptions.

Failure to adhere to these guidelines in their entirety may result in a mimumum 20% penalty. Any moderate or significant failure may result in a 0 grade.

Please note: If you choose to work on separate branches before merging into master, you must squash your commits when merging back in. This means that you can make many commits on other branches fine, it's just whatever comes back to master needs to be a single commit that compiles with no more than 50 line additions.

## 7. Originality of Work

The work you submit must be your own work. Submission of work partially or completely derived from any other person or jointly written with any other person is not permitted.

The penalties for such an offence may include negative marks, automatic failure of the course and possibly other academic discipline. Assignment submissions will be examined both automatically and manually for such submissions.

Relevant scholarship authorities will be informed if students holding scholarships are involved in an incident of plagiarism or other misconduct.

Do not provide or show your assignment work to any other person &mdash; apart from the teaching staff of COMP6771.

If you knowingly provide or show your assignment work to another person for any reason, and work derived from it is submitted, you may be penalised, even if the work was submitted without your knowledge or consent. This may apply even if your work is submitted by a third party unknown to you.

Every time you make commits or pushes on this repository, you are acknowledging that the work you submit is your own work (as described above).

Note you will not be penalised if your work has the potential to be taken without your consent or knowledge.

**PLEASE NOTE: We have a record of ALL previous submissions of this assignment submitted. If you find a solution from a friend, or online, we will find it and you will receive 0 for the assignment and potentially 0 for the course.** Trust me, at least 1 person does it every term and I encourage you not to think you'll get lucky.

## 8. Dryrun

If you want to check if you've actually not totally screwed it all up, and see if they pass a very basic compilation example, then run this command on the CSE systems.

`6771 dryrun ass1`

## 9. Submission

This assignment is due _Friday 27th of June, 19:59:59_.

To submit your assignment, you must ensure you've pushed all of your code to your gitlab master branch. You can check if you've done this properly by seeing what code is on the gitlab site on your master branch.

We will collect the latest work on your master branch of gitlab at the time of submission.

It is your responsibiltiy to ensure that your code can run successfully on a CSE machine / VLAB when cloned fresh from Gitlab.

## 10. Late Submission Policy

Late submissions are not accepted, except in the case of ELS adjustment or Special Consideration approval.

## 11. Appendix

- (note 1) You’ll need to consult the lexicon to see if the transformation is a valid word in either case.

## FAQ

Nothing yet.

[us]: https://en.cppreference.com/w/cpp/container/unordered_set
[Algorithms]: https://en.cppreference.com/w/cpp/algorithm
[vector]: https://en.cppreference.com/w/cpp/container/vector
