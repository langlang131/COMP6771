#include "word_break.h"

#include <catch2/catch.hpp>

TEST_CASE("empty input returns empty split") {
	auto lexicon = std::unordered_set<std::string>{"dogs", "an", "dragonfly"};
	auto result = word_break::word_break("", lexicon);

	REQUIRE(result.size() == 1); // empty split consider as a successful split
	REQUIRE(result[0].empty());  
}

TEST_CASE("empty lexicon returns no result") { 
	auto lexicon = std::unordered_set<std::string>{};
	auto result = word_break::word_break("abcd", lexicon);

	REQUIRE(result.empty());  
}

TEST_CASE("one solution test") {
	auto lexicon = std::unordered_set<std::string>{"dogs", "an", "dragonfly"};
	auto result = word_break::word_break("dogsandragonfly", lexicon);

	REQUIRE(result.size() == 1);
	REQUIRE(result[0] == std::vector<std::string>{"dogs", "an", "dragonfly"});
}

TEST_CASE("no solution test") {
	auto lexicon = std::unordered_set<std::string>{"cat", "dog"};
	auto result = word_break::word_break("xyzabc", lexicon);

	REQUIRE(result.empty());
}

TEST_CASE("can't split it all: no solution test") {
	auto lexicon = std::unordered_set<std::string>{"cat", "dog"};
	auto result = word_break::word_break("catxyzdog", lexicon);

	REQUIRE(result.empty());
}

TEST_CASE("recognize single words") {
	auto lexicon = std::unordered_set<std::string>{"dragon", "fly", "dragonfly"};
	auto result = word_break::word_break("dragonfly", lexicon);

	REQUIRE(result[0] == std::vector<std::string>{"dragonfly"});
}

TEST_CASE("recognize single words II") {
	auto lexicon = std::unordered_set<std::string>{"dragonfly"};
	auto result = word_break::word_break("dragonfly", lexicon);

	REQUIRE(result[0] == std::vector<std::string>{"dragonfly"});
}


TEST_CASE("only return minimal-word splits") {
	auto lexicon = std::unordered_set<std::string>{
		"dog", "dogs", "sand", "and", "rag", "on", "fly",
		"an", "dragon", "dragonfly"
	};

	auto result = word_break::word_break("dogsandragonfly", lexicon);
	REQUIRE(result.size() == 1);

	// dogs an dragonfly
	REQUIRE(result[0] == std::vector<std::string>{"dogs", "an", "dragonfly"});
}

TEST_CASE("use repeat words") {
	auto lexicon = std::unordered_set<std::string>{
		"dog"
	};

	auto result = word_break::word_break("dogdogdogdog", lexicon);
	REQUIRE(result.size() == 1);
	REQUIRE(result[0] == std::vector<std::string>{"dog","dog", "dog", "dog"});
}

TEST_CASE("minimal split with repeated words") {
	auto lexicon = std::unordered_set<std::string>{
		"dog", "dogs", "sand", "and", "rag", "on", "fly",
		"an", "dragon", "dragonfly"
	};

	auto result = word_break::word_break("dogsdogsandragonfly", lexicon);
	REQUIRE(result.size() == 1);
	REQUIRE(result[0] == std::vector<std::string>{"dogs","dogs", "an", "dragonfly"});
}

TEST_CASE("mutiple (answers) minimal-word splits") {
	auto lexicon = std::unordered_set<std::string>{
		"dog", "dogs", "sand", "and", 
	};

	auto result = word_break::word_break("dogsand", lexicon);
	REQUIRE(result.size() == 2);
	REQUIRE_THAT(result, Catch::Matchers::UnorderedEquals(std::vector<std::vector<std::string>>{
		{"dog", "sand"},
		{"dogs", "and"}
	}));
}

TEST_CASE("basic test: at -> it") {
	auto const lexicon = std::unordered_set<std::string>{
		"at",
		"it"
	};

	const auto expected = std::vector<std::vector<std::string>>{
		{"at", "it"}
	};

	auto const ladders = word_break::word_break("atit", lexicon);

	CHECK(ladders == expected);
}


