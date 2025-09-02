#include "gdwg_graph.h"

#include <catch2/catch.hpp>

#include <string>

TEST_CASE("insert_node and insert_edge basic test") {
	auto g = gdwg::Graph<std::string, int>{};
	REQUIRE(g.insert_node("A"));
	REQUIRE(g.insert_node("B"));
	REQUIRE_FALSE(g.insert_node("A")); // existed

	SECTION("Insert weighted edge") {
		REQUIRE(g.insert_edge("A", "B", 5));
		REQUIRE_FALSE(g.insert_edge("A", "B", 5)); // exsited
	}

	SECTION("Insert unweighted edge") {
		REQUIRE(g.insert_edge("A", "B"));
	}

	SECTION("Insert edge with missing node throws") {
		REQUIRE_THROWS_WITH(g.insert_edge("A", "C", 10), // not exsit
		                    "Cannot call gdwg::Graph<N, E>::insert_edge when either src or dst node does not exist");
	}
}

TEST_CASE("replace_node test") {
	auto g = gdwg::Graph<std::string, int>{};
	REQUIRE(g.insert_node("A"));
	REQUIRE(g.insert_node("B"));
	REQUIRE(g.insert_edge("A", "B", 42));

	SECTION("Replace with new node") {
		REQUIRE(g.replace_node("A", "C"));
		// C -> B now exists
		REQUIRE(g.insert_edge("C", "B", 42) == false);
	}

	SECTION("Replace node that doesn't exist") {
		REQUIRE_THROWS_WITH(g.replace_node("X", "Y"),
		                    "Cannot call gdwg::Graph<N, E>::replace_node on a node that doesn't exist");
	}

	SECTION("Replace with already existing node") {
		REQUIRE_FALSE(g.replace_node("A", "B")); // B already exists
	}
}

TEST_CASE("merge_replace_node test") {
	auto g = gdwg::Graph<std::string, int>{};
	REQUIRE(g.insert_node("A"));
	REQUIRE(g.insert_node("B"));
	REQUIRE(g.insert_node("C"));
	REQUIRE(g.insert_node("D"));
	REQUIRE(g.insert_edge("A", "B", 1)); // A -> B
	REQUIRE(g.insert_edge("A", "C", 2)); // A -> C
	REQUIRE(g.insert_edge("A", "D", 3)); // A -> D
	REQUIRE(g.insert_edge("B", "B", 1)); // B -> B
	g.merge_replace_node("A", "B");

	REQUIRE_FALSE(g.is_node("A")); // no A
	REQUIRE(g.is_node("B")); // B C D exist
	REQUIRE(g.is_node("C"));
	REQUIRE(g.is_node("D"));

	// insert some edges should exist, because A replaced by B
	REQUIRE_FALSE(g.insert_edge("B", "B", 1));
	REQUIRE_FALSE(g.insert_edge("B", "C", 2));
	REQUIRE_FALSE(g.insert_edge("B", "D", 3));

	REQUIRE(g.insert_edge("B", "C", 996)); // test insert new edges
	REQUIRE(g.insert_edge("C", "B", 5));
}

TEST_CASE("erase_node basic test") {
	auto g = gdwg::Graph<std::string, int>{};
	g.insert_node("A");
	g.insert_node("B");
	g.insert_node("C");
	g.insert_edge("A", "B", 1);
	g.insert_edge("C", "A", 2);

	REQUIRE(g.erase_node("A") == true);
	REQUIRE_FALSE(g.is_node("A"));
}

TEST_CASE("erase_edge basic test") {
	auto g = gdwg::Graph<std::string, int>{};
	g.insert_node("A");
	g.insert_node("B");
	g.insert_edge("A", "B", 5);
	g.insert_edge("A", "B");

	SECTION("Erase weighted edge") {
		REQUIRE(g.erase_edge("A", "B", 5)); // true
		REQUIRE_FALSE(g.erase_edge("A", "B", 5)); // erase again, false
	}

	SECTION("Erase unweighted edge") {
		REQUIRE(g.erase_edge("A", "B"));
		REQUIRE_FALSE(g.erase_edge("A", "B"));
	}

	SECTION("Throws if not exist") {
		REQUIRE_THROWS_WITH(g.erase_edge("X", "B", 5),
		                    "Cannot call gdwg::Graph<N, E>::erase_edge on src or dst if they don't exist in the graph");
	}
}

TEST_CASE("erase_edge(iterator) test") {
	auto g = gdwg::Graph<std::string, int>{};
	g.insert_node("A");
	g.insert_node("B");
	g.insert_edge("A", "B", 42);

	auto it = g.begin();
	REQUIRE(it != g.end());

	auto next = g.erase_edge(it);
	REQUIRE(next == g.end());
}

TEST_CASE("erase_edge(i, s)") {
	auto g = gdwg::Graph<std::string, int>{};
	g.insert_node("A");
	g.insert_node("B");
	g.insert_node("C");

	g.insert_edge("A", "B", 10);
	g.insert_edge("A", "C", 20);
	g.insert_edge("B", "C", 30);

	// iterator：
	auto it1 = g.begin(); // A->B
	auto it2 = std::next(it1); // A->C
	auto it3 = std::next(it2); // B->C

	// erase A->B and A->C
	auto ret = g.erase_edge(it1, it3);

	REQUIRE(std::distance(g.begin(), g.end()) == 1);
	REQUIRE(ret != g.end());
	REQUIRE((*ret)->print_edge() == "B -> C | W | 30");
}

TEST_CASE("clear() test") {
	auto g = gdwg::Graph<std::string, int>{};
	g.insert_node("A");
	g.insert_node("B");
	g.insert_edge("A", "B", 111);
	REQUIRE(g.is_node("A"));
	REQUIRE(g.is_node("B"));

	g.clear();
	REQUIRE_FALSE(g.is_node("A")); // False: is clear
	REQUIRE_FALSE(g.is_node("B"));
	REQUIRE(g.begin() == g.end());
}

TEST_CASE("basic test") {
	// These are commented out right now
	//  because withour your implementation
	//  it will not compile. Uncomment them
	//  once you've done the work
	auto g = gdwg::Graph<int, std::string>{};
	auto n = 5;
	g.insert_node(n);
	CHECK(g.is_node(n));
}

TEST_CASE("accessors test 1: ") {
	auto g = gdwg::Graph<std::string, int>{};

	SECTION("check") {
		REQUIRE(g.empty());
		REQUIRE_FALSE(g.is_node("A"));
		REQUIRE(g.nodes().empty());
	}

	SECTION("check after adding nodes") {
		g.insert_node("B");
		g.insert_node("A");
		g.insert_node("C");
		REQUIRE_FALSE(g.empty());
		REQUIRE(g.is_node("A"));
		REQUIRE(g.is_node("B"));
		REQUIRE_FALSE(g.is_node("D"));

		auto expected_nodes = std::vector<std::string>{"A", "B", "C"};
		REQUIRE(g.nodes() == expected_nodes);
	}

	SECTION("is_connected ") {
		g.insert_node("A");
		g.insert_node("B");
		g.insert_node("C");

		REQUIRE_FALSE(g.is_connected("A", "B"));
		g.insert_edge("A", "B", 5);
		REQUIRE(g.is_connected("A", "B"));

		REQUIRE_FALSE(g.is_connected("B", "A")); // reverse

		g.insert_edge("A", "C");
		REQUIRE(g.is_connected("A", "C"));

		REQUIRE_THROWS_WITH(g.is_connected("A", "Z"), // not exist
		                    "Cannot call gdwg::Graph<N, E>::is_connected if src or dst node don't exist in the graph");
	}
}

TEST_CASE("accessors test 2: edges()") {
	auto g = gdwg::Graph<std::string, int>{};
	g.insert_node("A");
	g.insert_node("B");
	g.insert_edge("A", "B", 5);
	g.insert_edge("A", "B", 1);
	g.insert_edge("A", "B");

	auto edges = g.edges("A", "B");

	REQUIRE(edges.size() == 3);
	REQUIRE(edges[0]->print_edge() == "A -> B | U");
	REQUIRE(edges[1]->print_edge() == "A -> B | W | 1");
	REQUIRE(edges[2]->print_edge() == "A -> B | W | 5");

	REQUIRE_THROWS_WITH(g.edges("A", "Z"),
	                    "Cannot call gdwg::Graph<N, E>::edges if src or dst node don't exist in the graph");
}

TEST_CASE("accessors test 3: find()") {
	auto g = gdwg::Graph<std::string, int>{};
	g.insert_node("X");
	g.insert_node("Y");
	g.insert_edge("X", "Y", 42);
	g.insert_edge("X", "Y");

	SECTION("weighted edge") {
		auto it = g.find("X", "Y", 42);
		REQUIRE(it != g.end());
		REQUIRE((*it)->print_edge() == "X -> Y | W | 42");
	}

	SECTION("unweighted edge") {
		auto it = g.find("X", "Y");
		REQUIRE(it != g.end());
		REQUIRE((*it)->print_edge() == "X -> Y | U");
	}

	SECTION("not exist edge") {
		auto it = g.find("Y", "X");
		REQUIRE(it == g.end());
	}
}

TEST_CASE("accessors test 4: connections()") {
	auto g = gdwg::Graph<std::string, int>{};
	g.insert_node("A");
	g.insert_node("B");
	g.insert_node("C");
	g.insert_edge("A", "B", 1);
	g.insert_edge("A", "C", 2);
	g.insert_edge("A", "B");

	SECTION("connections") {
		auto result = g.connections("A");
		REQUIRE(result.size() == 2);
		REQUIRE(result[0] == "B");
		REQUIRE(result[1] == "C");
	}

	SECTION("No connections") {
		auto result = g.connections("B");
		REQUIRE(result.empty());
	}

	SECTION("Throw if src not exist") {
		REQUIRE_THROWS_WITH(g.connections("D"),
		                    "Cannot call gdwg::Graph<N, E>::connections if src doesn't exist in the graph");
	}
}

TEST_CASE("operator== ") {
	auto g1 = gdwg::Graph<std::string, int>();
	auto g2 = gdwg::Graph<std::string, int>();
	g1.insert_node("A");
	g1.insert_node("B");
	g1.insert_edge("A", "B", 5);
	g2.insert_node("A");
	g2.insert_node("B");
	g2.insert_edge("A", "B", 5); // g1g2 exactly same
	REQUIRE(g1 == g2);

	auto g3 = gdwg::Graph<std::string, int>();
	g3.insert_node("A");
	g3.insert_node("C"); // diff node
	g3.insert_edge("A", "C", 5);
	REQUIRE_FALSE(g1 == g3);

	auto g4 = gdwg::Graph<std::string, int>();
	g4.insert_node("A");
	g4.insert_node("B");
	g4.insert_edge("A", "B", 10); // diff edge weight
	REQUIRE_FALSE(g1 == g4);

	auto g5 = gdwg::Graph<std::string, int>();
	g5.insert_node("A");
	g5.insert_node("B");
	g5.insert_edge("B", "A", 5); // diff direction
	REQUIRE_FALSE(g1 == g5);

	auto g6 = gdwg::Graph<std::string, int>();
	g6.insert_node("A");
	g6.insert_node("B");
	g6.insert_edge("A", "B", 5);
	g6.insert_edge("A", "B", 3);

	g1.insert_edge("A", "B", 3); // g1 add same edge, require true
	REQUIRE(g1 == g6);
}

TEST_CASE("<< operator test") {
	using graph = gdwg::Graph<int, int>;
	auto const v = std::vector<std::tuple<int, int, std::optional<int>>>{
	    {4, 1, -4},
	    {3, 2, 2},
	    {2, 4, std::nullopt},
	    {2, 4, 2},
	    {2, 1, 1},
	    {4, 1, std::nullopt},
	    {6, 2, 5},
	    {6, 3, 10},
	    {1, 5, -1},
	    {3, 6, -8},
	    {4, 5, 3},
	    {5, 2, std::nullopt},
	};

	auto g = graph{};
	for (const auto& [from, to, weight] : v) {
		g.insert_node(from);
		g.insert_node(to);
		if (weight.has_value()) {
			g.insert_edge(from, to, weight.value());
		}
		else {
			g.insert_edge(from, to);
		}
	}
	g.insert_node(64);

	auto out = std::ostringstream{};
	out << g;

	auto const expected_output = std::string_view(R"(1 (
  1 -> 5 | W | -1
)
2 (
  2 -> 1 | W | 1
  2 -> 4 | U
  2 -> 4 | W | 2
)
3 (
  3 -> 2 | W | 2
  3 -> 6 | W | -8
)
4 (
  4 -> 1 | U
  4 -> 1 | W | -4
  4 -> 5 | W | 3
)
5 (
  5 -> 2 | U
)
6 (
  6 -> 2 | W | 5
  6 -> 3 | W | 10
)
64 (
)
)");
	CHECK(out.str() == expected_output);
}
