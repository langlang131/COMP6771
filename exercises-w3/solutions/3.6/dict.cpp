#include "./dict.h"

auto to_word_list(std::istream &input) -> std::vector<std::string> {
  return {std::istream_iterator<std::string>{input}, std::istream_iterator<std::string>{}};
}

auto print_valid_words(
    const std::vector<std::string> &valid_words,
    std::istream &input,
    std::ostream &output
) -> void {
    std::copy_if(
        std::istream_iterator<std::string>{input},
        std::istream_iterator<std::string>{},
        std::ostream_iterator<std::string>{output, " "},
        [&](const std::string& s) {
            return std::find(valid_words.begin(), valid_words.end(), s) != valid_words.end();
        });
}
