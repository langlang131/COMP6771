#ifndef GDWG_GRAPH_H
#define GDWG_GRAPH_H
#include <iostream>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// TODO: Make both graph and edge generic
//       ... this won't just compile
//       straight away
namespace gdwg {
	template<typename N, typename E>
	class Graph;

	template<typename N, typename E>
	auto operator<<(std::ostream& os, Graph<N, E> const& g) -> std::ostream&;

	template<typename N, typename E>
	class Edge {
	 public:
		virtual ~Edge() = default;
		virtual auto print_edge() const -> std::string = 0;
		virtual auto is_weighted() const -> bool = 0;
		virtual auto get_weight() const -> std::optional<E> = 0;
		virtual auto get_nodes() const -> std::pair<N, N> = 0;
		virtual auto operator==(Edge const& other) const -> bool = 0;

	 private:
		// You may need to add data members and member functions
		friend class Graph<N, E>;
	};

	template<typename N, typename E>
	class WeightedEdge : public Edge<N, E> {
	 public:
		WeightedEdge(N const& src, N const& dst, E const& weight)
		: src_(src)
		, dst_(dst)
		, weight_(weight) {}
		auto print_edge() const -> std::string override {
			std::ostringstream oss;
			oss << src_ << " -> " << dst_ << " | W | " << weight_;
			return oss.str();
		}
		auto is_weighted() const -> bool override {
			return true;
		}
		auto get_weight() const -> std::optional<E> override {
			return weight_;
		}
		auto get_nodes() const -> std::pair<N, N> override {
			return {src_, dst_};
		}
		auto operator==(Edge<N, E> const& other) const -> bool override {
			if (!other.is_weighted())
				return false;
			auto [o_src, o_dst] = other.get_nodes();
			return src_ == o_src && dst_ == o_dst && weight_ == other.get_weight();
		}

	 private:
		N src_;
		N dst_;
		E weight_;
	};

	template<typename N, typename E>
	class UnweightedEdge : public Edge<N, E> {
	 public:
		UnweightedEdge(N const& src, N const& dst)
		: src_(src)
		, dst_(dst) {}
		auto print_edge() const -> std::string override {
			std::ostringstream oss;
			oss << src_ << " -> " << dst_ << " | U";
			return oss.str();
		}
		auto is_weighted() const -> bool override {
			return false;
		}
		auto get_weight() const -> std::optional<E> override {
			return std::nullopt;
		}
		auto get_nodes() const -> std::pair<N, N> override {
			return {src_, dst_};
		}
		auto operator==(Edge<N, E> const& other) const -> bool override {
			if (other.is_weighted())
				return false;
			auto [o_src, o_dst] = other.get_nodes();
			return src_ == o_src && dst_ == o_dst;
		}

	 private:
		N src_;
		N dst_;
	};

	template<typename N, typename E>
	struct EdgeComparator {
		bool operator()(const std::unique_ptr<Edge<N, E>>& lhs, const std::unique_ptr<Edge<N, E>>& rhs) const {
			auto [lhs_src, lhs_dst] = lhs->get_nodes();
			auto [rhs_src, rhs_dst] = rhs->get_nodes();
			if (lhs_src != rhs_src)
				return lhs_src < rhs_src;
			if (lhs_dst != rhs_dst)
				return lhs_dst < rhs_dst;
			return lhs->get_weight() < rhs->get_weight();
		}
	};

	template<typename N, typename E>
	class Graph {
	 public:
		Graph() = default;

		Graph(std::initializer_list<N> il) {
			for (auto const& node : il) {
				nodes_.insert(node);
			}
		}

		template<typename InputIt>
		Graph(InputIt first, InputIt last) {
			for (auto it = first; it != last; ++it) {
				nodes_.insert(*it);
			}
		}

		Graph(Graph const& other) = default;

		Graph(Graph&& other) noexcept = default;

		auto operator=(Graph const& other) -> Graph& = default;

		auto operator=(Graph&& other) noexcept -> Graph& = default;

		auto insert_node(N const& value) -> bool {
			return nodes_.insert(value).second;
		}
		auto insert_edge(N const& src, N const& dst, std::optional<E> weight = std::nullopt) -> bool;
		auto replace_node(N const& old_data, N const& new_data) -> bool;

		auto merge_replace_node(N const& old_data, N const& new_data) -> void;
		auto erase_node(N const& value) -> bool;
		auto erase_edge(N const& src, N const& dst, std::optional<E> weight = std::nullopt) -> bool;

		[[nodiscard]] auto is_node(N const& value) const -> bool {
			return nodes_.find(value) != nodes_.end();
		}
		[[nodiscard]] auto empty() const -> bool {
			return nodes_.empty();
		}
		[[nodiscard]] auto is_connected(N const& src, N const& dst) const -> bool {
			if (!is_node(src) || !is_node(dst)) {
				throw std::runtime_error("Cannot call gdwg::Graph<N, E>::is_connected if src or dst node don't exist "
				                         "in the graph");
			}

			for (auto const& edge : edges_) {
				auto [e_src, e_dst] = edge->get_nodes();
				if (e_src == src && e_dst == dst) {
					return true;
				}
			}
			return false;
		}
		[[nodiscard]] auto nodes() const -> std::vector<N> {
			return std::vector<N>(nodes_.begin(), nodes_.end());
		}
		[[nodiscard]] auto edges(N const& src, N const& dst) const -> std::vector<std::unique_ptr<Edge<N, E>>> {
			if (!is_node(src) || !is_node(dst)) {
				throw std::runtime_error("Cannot call gdwg::Graph<N, E>::edges if src or dst node don't exist in the "
				                         "graph");
			}

			std::vector<std::unique_ptr<Edge<N, E>>> result;

			for (auto const& edge : edges_) {
				auto [e_src, e_dst] = edge->get_nodes();
				if (e_src == src && e_dst == dst) {
					if (edge->is_weighted()) {
						result.push_back(std::make_unique<WeightedEdge<N, E>>(e_src, e_dst, edge->get_weight().value()));
					}
					else {
						result.push_back(std::make_unique<UnweightedEdge<N, E>>(e_src, e_dst));
					}
				}
			}

			return result;
		}
		[[nodiscard]] auto connections(N const& src) const -> std::vector<N> {
			if (!is_node(src)) {
				throw std::runtime_error("Cannot call gdwg::Graph<N, E>::connections if src doesn't exist in the "
				                         "graph");
			}
			std::set<N> unique_dsts;

			for (auto const& edge : edges_) {
				auto [e_src, e_dst] = edge->get_nodes();
				if (e_src == src) {
					unique_dsts.insert(e_dst);
				}
			}
			return std::vector<N>(unique_dsts.begin(), unique_dsts.end());
		}
		[[nodiscard]] auto operator==(Graph const& other) const -> bool {
			// node part
			if (this->nodes_ != other.nodes_) {
				return false;
			}

			// compare edge numbers
			if (this->edges_.size() != other.edges_.size()) {
				return false;
			}

			// edge part
			auto it1 = this->edges_.begin();
			auto it2 = other.edges_.begin();

			while (it1 != this->edges_.end()) {
				auto const& edge1 = *it1;
				auto const& edge2 = *it2;

				if (!(*edge1 == *edge2)) {
					return false;
				}

				++it1;
				++it2;
			}

			return true;
		}

		void print_nodes() const {
			for (const auto& node : nodes_) {
				std::cout << node << "\n";
			}
		}
		using iterator = typename std::set<std::unique_ptr<Edge<N, E>>, EdgeComparator<N, E>>::iterator;
		using const_iterator = typename std::set<std::unique_ptr<Edge<N, E>>, EdgeComparator<N, E>>::const_iterator;
		auto erase_edge(iterator i) -> iterator;
		[[nodiscard]] auto begin() -> iterator {
			return edges_.begin();
		}
		[[nodiscard]] auto end() -> iterator {
			return edges_.end();
		}

		[[nodiscard]] auto begin() const -> const_iterator {
			return edges_.begin();
		}
		[[nodiscard]] auto end() const -> const_iterator {
			return edges_.end();
		}
		auto erase_edge(iterator i, iterator s) -> iterator;
		auto clear() noexcept -> void;
		// friend auto operator<<(std::ostream& os, Graph const& g) -> std::ostream&;
		friend auto operator<< <>(std::ostream& os, Graph<N, E> const& g) -> std::ostream&;

		[[nodiscard]] auto find(N const& src, N const& dst, std::optional<E> weight = std::nullopt) const
		    -> const_iterator {
			for (auto it = edges_.begin(); it != edges_.end(); ++it) {
				auto const& edge = *it;
				auto [e_src, e_dst] = edge->get_nodes();

				if (e_src == src && e_dst == dst) {
					if (!weight.has_value() && !edge->is_weighted()) {
						return it;
					}
					if (weight.has_value() && edge->is_weighted() && edge->get_weight() == weight) {
						return it;
					}
				}
			}
			return edges_.end();
		}

	 private:
		std::set<N> nodes_;
		std::set<std::unique_ptr<Edge<N, E>>, EdgeComparator<N, E>> edges_;
	};

	template<typename N, typename E>
	auto Graph<N, E>::insert_edge(N const& src, N const& dst, std::optional<E> weight) -> bool {
		if (!is_node(src) || !is_node(dst)) {
			throw std::runtime_error("Cannot call gdwg::Graph<N, E>::insert_edge when either src or dst node does not "
			                         "exist");
		}

		std::unique_ptr<Edge<N, E>> new_edge;
		if (weight.has_value()) {
			new_edge = std::make_unique<WeightedEdge<N, E>>(src, dst, weight.value());
		}
		else {
			new_edge = std::make_unique<UnweightedEdge<N, E>>(src, dst);
		}

		for (auto const& e : edges_) {
			if (*e == *new_edge) {
				return false;
			}
		}

		edges_.insert(std::move(new_edge));
		return true;
	}

	template<typename N, typename E>
	auto gdwg::Graph<N, E>::replace_node(N const& old_data, N const& new_data) -> bool {
		if (!is_node(old_data)) {
			throw std::runtime_error("Cannot call gdwg::Graph<N, E>::replace_node on a node that doesn't exist");
		}
		if (is_node(new_data)) {
			return false;
		}
		nodes_.erase(old_data);
		nodes_.insert(new_data);

		std::set<std::unique_ptr<Edge<N, E>>, EdgeComparator<N, E>> new_edges;
		for (auto const& edge : edges_) {
			auto [src, dst] = edge->get_nodes();
			auto weight = edge->get_weight();

			if (src == old_data)
				src = new_data;
			if (dst == old_data)
				dst = new_data;

			std::unique_ptr<Edge<N, E>> new_edge;
			if (weight.has_value()) {
				new_edge = std::make_unique<WeightedEdge<N, E>>(src, dst, weight.value());
			}
			else {
				new_edge = std::make_unique<UnweightedEdge<N, E>>(src, dst);
			}

			// duplicate edges will be removed
			new_edges.insert(std::move(new_edge));
		}

		edges_ = std::move(new_edges);
		return true;
	}

	template<typename N, typename E>
	auto Graph<N, E>::merge_replace_node(N const& old_data, N const& new_data) -> void {
		if (!is_node(old_data) || !is_node(new_data)) {
			throw std::runtime_error("Cannot call gdwg::Graph<N, E>::merge_replace_node on old or new data if they "
			                         "don't exist in the graph");
		}
		std::set<std::unique_ptr<Edge<N, E>>, EdgeComparator<N, E>> new_edges;

		for (auto const& edge : edges_) {
			auto [src, dst] = edge->get_nodes();
			auto weight = edge->get_weight();

			if (src == old_data)
				src = new_data;
			if (dst == old_data)
				dst = new_data;

			std::unique_ptr<Edge<N, E>> new_edge;
			if (weight.has_value()) {
				new_edge = std::make_unique<WeightedEdge<N, E>>(src, dst, weight.value());
			}
			else {
				new_edge = std::make_unique<UnweightedEdge<N, E>>(src, dst);
			}
			new_edges.insert(std::move(new_edge));
		}
		edges_ = std::move(new_edges);
		nodes_.erase(old_data);
	}

	template<typename N, typename E>
	auto Graph<N, E>::erase_node(N const& value) -> bool {
		if (!is_node(value)) {
			return false;
		}
		nodes_.erase(value);
		for (auto it = edges_.begin(); it != edges_.end();) {
			auto [src, dst] = (*it)->get_nodes();
			if (src == value || dst == value) {
				it = edges_.erase(it);
			}
			else {
				++it;
			}
		}
		return true;
	}

	template<typename N, typename E>
	auto Graph<N, E>::erase_edge(N const& src, N const& dst, std::optional<E> weight) -> bool {
		if (!is_node(src) || !is_node(dst)) {
			throw std::runtime_error("Cannot call gdwg::Graph<N, E>::erase_edge on src or dst if they don't exist in "
			                         "the graph");
		}

		for (auto it = edges_.begin(); it != edges_.end(); ++it) {
			auto const& edge = *it;
			auto [e_src, e_dst] = edge->get_nodes();

			if (e_src == src && e_dst == dst) {
				// no weight
				if (!weight.has_value() && !edge->is_weighted()) {
					edges_.erase(it);
					return true;
				}
				// weight
				if (weight.has_value() && edge->is_weighted() && edge->get_weight() == weight) {
					edges_.erase(it);
					return true;
				}
			}
		}
		return false;
	}

	template<typename N, typename E>
	auto Graph<N, E>::erase_edge(iterator i) -> iterator {
		auto next = std::next(i);

		edges_.erase(i);

		return next;
	}

	template<typename N, typename E>
	auto gdwg::Graph<N, E>::erase_edge(iterator i, iterator s) -> iterator {
		if (i == s) {
			return s;
		}
		auto return_it = s;

		while (i != s) {
			i = edges_.erase(i);
		}
		return return_it;
	}

	template<typename N, typename E>
	auto gdwg::Graph<N, E>::clear() noexcept -> void {
		nodes_.clear();
		edges_.clear();
	}

} // namespace gdwg

#endif // GDWG_GRAPH_H
