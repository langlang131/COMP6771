# Solutions to theory questions

- What is a `TEST_CASE`?

> A `TEST_CASE` is a uniquely-named scope that has the context for our test framework, and will keep
  track of all the `CHECK`s and `REQUIRE`s that pass/fail.

- What is a `CHECK`? How is it different to an `assert`?

> `CHECK` will evaluate an expression and report if it is `false`, but the program will continue to
  run.

- What is a `REQUIRE`? How is this different to an `assert`?

> `REQUIRE` is closer to an `assert` than a check, in that it terminates the test case, but unlike
  an `assert`, it will gracefully exit the test case, rather than terminate on the spot. Subsequent
  test cases are still execute, so unlike an assert, it only aborts a portion of the program, rather
  than the whole program.

- What are `SECTION` blocks in Catch2, and how do they make testing easier?

> `SECTION` blocks allow us to write setup code for our checks. Every `SECTION` will run all the code in the `SECTION` block that it's enclosed in, all the way back up to the `TEST_CASE`. This means that we can modify what we're testing in one section, and still get the same state we started in all following states at the same level!
>
> All of your setup is done once, which reduces the amount of code duplication that you need to do, the amount of `REQUIRE`s you need to do, which optimises for both the reader and the writer.
