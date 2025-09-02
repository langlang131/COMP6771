#ifndef COMP6771_DICTIONARY_H
#define COMP6771_DICTIONARY_H

#include <istream>
#include <string>
#include <vector>

auto to_word_list(std::istream &input) -> std::vector<std::string>;

auto print_valid_words(
    const std::vector<std::string> &valid_words,
    std::istream &input,
    std::ostream &output
) -> void;

#endif  // COMP6771_DICTIONARY_H
