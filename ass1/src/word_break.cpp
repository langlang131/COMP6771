#include "word_break.h"
#include <string>
#include <fstream>    
#include <stdexcept>    
#include <limits>       
#include <iostream>
#include <unordered_map>

//Read file with one word per line
//Throw if file failed to open
auto word_break::read_lexicon(
	const std::string &path
) -> std::unordered_set<std::string> {
	std::unordered_set<std::string> lexicon;
	std::ifstream file(path);
	if (!file) {
        throw std::runtime_error("Failed to open file: " + path);
    }

	std::string word;
	while (std::getline(file, word)) {
		if (!word.empty()) {
			lexicon.insert(word);
		}
	}
	return lexicon;
}
namespace word_break {
// Recursively finds all minimal-word splits
auto dfs(
	const std::string& s,
	size_t start,
	const std::unordered_set<std::string>& lexicon,
	std::unordered_map<size_t, std::pair<size_t, std::vector<std::vector<std::string>>>>& memo
) -> std::pair<size_t, std::vector<std::vector<std::string>>> {
	if (start == s.size()) {
        return {0, { { } }}; // to the end, return
	}
	
	if (memo.find(start) != memo.end()) {
		return memo[start]; // use cache

	}

	size_t min_words = std::numeric_limits<size_t>::max();
	std::vector<std::vector<std::string>> results;

	// Try every possible substring 
	for (size_t end = start + 1; end <= s.size(); ++end) {
		std::string word = s.substr(start, end - start);
		if (lexicon.find(word) != lexicon.end()) {
			auto [sub_words, sub_sentences] = dfs(s, end, lexicon, memo);

			// only consider the path if it is a minimal-word split currently
            if (!sub_sentences.empty() && sub_words + 1 <= min_words) {
				if (sub_words + 1 < min_words) {
					results.clear(); // only keep the shortest 'sentence'
					min_words = sub_words + 1;
				}

				for (const auto& subs : sub_sentences) {
					auto sentence = std::vector<std::string>{word};
					sentence.insert(sentence.end(), subs.begin(), subs.end());
					results.push_back(std::move(sentence));
				}
			}
		}
	}
	memo[start] = {min_words, results};
	return memo[start];
}
auto word_break(
    const std::string& string_to_break,
    const std::unordered_set<std::string>& lexicon
) -> std::vector<std::vector<std::string>> {
	std::unordered_map<size_t, std::pair<size_t, std::vector<std::vector<std::string>>>> memo;
	auto [_, result] = dfs(string_to_break, 0, lexicon, memo);
	return result;
}
} // namespace word_break
