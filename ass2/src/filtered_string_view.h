#ifndef COMP6771_ASS2_FSV_H
#define COMP6771_ASS2_FSV_H

#include <compare>
#include <functional>
#include <iterator>
#include <optional>
#include <ostream>
#include <string>

namespace fsv {
    using filter = std::function<bool(const char&)>;

    class filtered_string_view {
        class iter {
        public:
            using MEMBER_TYPEDEFS_GO_HERE = void;

            iter();

            auto operator*() const -> void; // change this
            auto operator->() const -> void; // change this

            auto operator++() -> iter&;
            auto operator++(int) -> iter;
            auto operator--() -> iter&;
            auto operator--(int) -> iter;

            friend auto operator==(const iter&, const iter&) -> bool;
            friend auto operator!=(const iter&, const iter&) -> bool;

        private:
            /* Implementation-specific helper functions*/

            /* Implementation-specific private members */
        };

    public:
        filtered_string_view() noexcept;
        filtered_string_view(const std::string& str);
        filtered_string_view(const std::string& str, filter predicate);
        filtered_string_view(const char* str);
        filtered_string_view(const char* str, filter predicate);
        filtered_string_view(const filtered_string_view& other);
        filtered_string_view(filtered_string_view&& other);
        ~filtered_string_view() = default;

        auto operator=(const filtered_string_view& other) -> filtered_string_view&;
        auto operator=(filtered_string_view&& other) -> filtered_string_view&;
        auto operator[](std::size_t n) const -> const char&;
        auto at(std::size_t index) const -> const char&;
        explicit operator std::string() const;

        [[nodiscard]] auto size() const noexcept -> std::size_t;
        [[nodiscard]] auto empty() const noexcept -> bool;
        [[nodiscard]] auto data() const noexcept -> const char*;
        [[nodiscard]] auto predicate() const noexcept -> const filter&;

        static filter default_predicate;

        using iterator = void; // change this
        using const_iterator = void; // change this
        using reverse_iterator = void; // change this
        using const_reverse_iterator = void; // change this

    private:
        /* Implementation-specific helper functions*/
        const char* ptr_;
        std::size_t length_;
        filter pred_;

        /* Implementation-specific private members */
    };
    auto operator==(const fsv::filtered_string_view& lhs, const fsv::filtered_string_view& rhs) -> bool;
    auto operator!=(const fsv::filtered_string_view& lhs, const fsv::filtered_string_view& rhs) -> bool;
    auto operator<(const fsv::filtered_string_view& lhs, const fsv::filtered_string_view& rhs) -> bool;
    auto operator>(const fsv::filtered_string_view& lhs, const fsv::filtered_string_view& rhs) -> bool;
    auto operator<=(const fsv::filtered_string_view& lhs, const fsv::filtered_string_view& rhs) -> bool;
    auto operator>=(const fsv::filtered_string_view& lhs, const fsv::filtered_string_view& rhs) -> bool;
    auto operator<<(std::ostream& os, const fsv::filtered_string_view& fsv) -> std::ostream&;
    auto compose(const filtered_string_view& fsv, const std::vector<filter>& filts) -> filtered_string_view;
    auto split(const filtered_string_view& fsv, const filtered_string_view& tok) -> std::vector<filtered_string_view>;
    auto substr(const filtered_string_view& fsv, std::size_t pos = 0, std::optional<std::size_t> count = std::nullopt)
        -> filtered_string_view;
} // namespace fsv

#endif // COMP6771_ASS2_FSV_H
