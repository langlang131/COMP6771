#include "gdwg_graph.h"
#include <algorithm>
#include <sstream>

namespace gdwg {

	template<typename N, typename E>
	auto operator<<(std::ostream& os, Graph<N, E> const& g) -> std::ostream& {
		if (g.empty()) {
			return os;
		}
		for (auto const& node : g.nodes_) {
			os << node << " (\n";

			// Collect edge: src == node
			std::vector<std::tuple<N, bool, std::optional<E>>> outgoing_edges;
			for (auto const& edge : g.edges_) {
				auto [src, dst] = edge->get_nodes();
				if (src != node)
					continue;

				bool is_weighted = edge->is_weighted();
				std::optional<E> weight = edge->get_weight();
				outgoing_edges.emplace_back(dst, is_weighted, weight);
			}
			// Sort
			std::sort(outgoing_edges.begin(), outgoing_edges.end(), [](auto const& a, auto const& b) {
				auto const& [dst1, is_w1, weight1] = a;
				auto const& [dst2, is_w2, weight2] = b;

				if (dst1 != dst2)
					return dst1 < dst2;
				if (is_w1 != is_w2)
					return !is_w1;
				if (!is_w1)
					return false;
				return *weight1 < *weight2;
			});

			// Output edges
			for (auto const& [dst, is_weighted, weight] : outgoing_edges) {
				os << "  " << node << " -> " << dst;
				if (is_weighted)
					os << " | W | " << *weight;
				else
					os << " | U";
				os << "\n";
			}
			os << ")\n";
		}
		return os;
	}

	template auto operator<<(std::ostream&, Graph<int, int> const&) -> std::ostream&;
	template auto operator<<(std::ostream&, Graph<std::string, int> const&) -> std::ostream&;

} // namespace gdwg
