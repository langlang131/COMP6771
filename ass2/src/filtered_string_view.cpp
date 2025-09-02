#include "./filtered_string_view.h"
#include <compare>
#include <cstring>
#include <set>

namespace fsv {

    filter filtered_string_view::default_predicate = [](const char&) { return true; };

    filtered_string_view::filtered_string_view() noexcept
    : ptr_(nullptr)
    , length_(0)
    , pred_(default_predicate) {}

    filtered_string_view::filtered_string_view(const std::string& str)
    : ptr_(str.data())
    , length_(str.size())
    , pred_(default_predicate) {}

    filtered_string_view::filtered_string_view(const std::string& str, filter predicate)
    : ptr_(str.data())
    , length_(str.size())
    , pred_(std::move(predicate)) {}

    filtered_string_view::filtered_string_view(const char* str)
    : ptr_(str)
    , length_(std::strlen(str))
    , pred_(default_predicate) {}

    filtered_string_view::filtered_string_view(const char* str, filter predicate)
    : ptr_(str)
    , length_(std::strlen(str))
    , pred_(std::move(predicate)) {}

    filtered_string_view::filtered_string_view(const filtered_string_view& other)
    : ptr_(other.ptr_)
    , length_(other.length_)
    , pred_(other.pred_) {}

    filtered_string_view::filtered_string_view(filtered_string_view&& other)
    : ptr_(other.ptr_)
    , length_(other.length_)
    , pred_(std::move(other.pred_)) {
        other.ptr_ = nullptr;
        other.length_ = 0;
        other.pred_ = filter{};
    }

    auto fsv::filtered_string_view::operator=(const filtered_string_view& other) -> filtered_string_view& {
        if (this != &other) {
            ptr_ = other.ptr_;
            length_ = other.length_;
            pred_ = other.pred_;
        }
        return *this;
    }

    auto filtered_string_view::operator=(filtered_string_view&& other) -> filtered_string_view& {
        if (this != &other) {
            ptr_ = other.ptr_;
            length_ = other.length_;
            pred_ = std::move(other.pred_);
            other.ptr_ = nullptr;
            other.length_ = 0;
            other.pred_ = filter{};
        }
        return *this;
    }

    auto filtered_string_view::operator[](std::size_t n) const -> const char& {
        std::size_t count = 0;
        for (std::size_t i = 0; i < length_; ++i) {
            if (pred_(ptr_[i])) {
                if (count == n) {
                    return ptr_[i];
                }
                ++count;
            }
        }

        return ptr_[0];
    }

    filtered_string_view::operator std::string() const {
        std::string result;
        for (std::size_t i = 0; i < length_; ++i) {
            if (pred_(ptr_[i])) {
                result += ptr_[i];
            }
        }
        return result;
    }

    auto filtered_string_view::at(std::size_t index) const -> const char& {
        std::size_t count = 0;
        for (std::size_t i = 0; i < length_; ++i) {
            if (pred_(ptr_[i])) {
                if (count == index) {
                    return ptr_[i];
                }
                ++count;
            }
        }

        throw std::domain_error{"filtered_string_view::at(" + std::to_string(index) + "): invalid index"};
    }

    auto filtered_string_view::size() const noexcept -> std::size_t {
        std::size_t count = 0;
        for (std::size_t i = 0; i < length_; ++i) {
            if (pred_(ptr_[i])) {
                ++count;
            }
        }
        return count;
    }
    auto filtered_string_view::empty() const noexcept -> bool {
        return size() == 0;
    }
    auto filtered_string_view::data() const noexcept -> const char* {
        return ptr_;
    }
    auto filtered_string_view::predicate() const noexcept -> const filter& {
        return pred_;
    }
    auto operator==(const fsv::filtered_string_view& lhs, const fsv::filtered_string_view& rhs) -> bool {
        std::size_t lhs_size = lhs.size();
        std::size_t rhs_size = rhs.size();
        if (lhs_size != rhs_size) {
            return false;
        }
        for (std::size_t i = 0; i < lhs_size; ++i) {
            if (lhs[i] != rhs[i]) {
                return false;
            }
        }
        return true;
    }
    auto operator!=(const fsv::filtered_string_view& lhs, const fsv::filtered_string_view& rhs) -> bool {
        return !(lhs == rhs);
    }

    auto operator<(const fsv::filtered_string_view& lhs, const fsv::filtered_string_view& rhs) -> bool {
        std::size_t i = 0;
        std::size_t lhs_size = lhs.size();
        std::size_t rhs_size = rhs.size();
        while (i < lhs_size && i < rhs_size) {
            if (lhs[i] != rhs[i]) {
                return lhs[i] < rhs[i];
            }
            ++i;
        }
        return lhs_size < rhs_size;
    }
    auto operator>(const fsv::filtered_string_view& lhs, const fsv::filtered_string_view& rhs) -> bool {
        return rhs < lhs;
    }
    auto operator<=(const fsv::filtered_string_view& lhs, const fsv::filtered_string_view& rhs) -> bool {
        return !(rhs < lhs);
    }
    auto operator>=(const fsv::filtered_string_view& lhs, const fsv::filtered_string_view& rhs) -> bool {
        return !(lhs < rhs);
    }
    auto operator<<(std::ostream& os, const fsv::filtered_string_view& fsv) -> std::ostream& {
        for (std::size_t i = 0; i < fsv.size(); ++i) {
            os << fsv[i];
        }
        return os;
    }

    auto compose(const filtered_string_view& fsv, const std::vector<filter>& filts) -> filtered_string_view {
        filter composed_pred = [filts](const char& c) {
            for (const auto& f : filts) {
                if (!f(c)) {
                    return false;
                }
            }
            return true;
        };
        return filtered_string_view{fsv.data(), composed_pred};
    }

    auto split(const filtered_string_view& fsv, const filtered_string_view& tok) -> std::vector<filtered_string_view> {
        std::vector<filtered_string_view> result;
        const char* base = fsv.data();
        const auto& pred = fsv.predicate();
        std::string full_str;
        for (std::size_t i = 0; i < fsv.size(); ++i) {
            full_str += fsv[i];
        }
        std::string tok_str = static_cast<std::string>(tok);

        // if token is empty (after filtering), treat it as not appearing in fsv
        if (tok_str.empty()) {
            result.push_back(fsv);
            return result;
        }

        std::size_t start = 0;
        // iterate through all token occurrences
        while (true) {
            std::size_t pos = full_str.find(tok_str, start);
            std::size_t end = (pos == std::string::npos) ? full_str.size() : pos;
            std::size_t filtered_offset = 0;
            std::vector<const char*> selected_chars;
            for (std::size_t i = 0; i < strlen(base); ++i) {
                if (pred(base[i])) {
                    if (filtered_offset >= start && filtered_offset < end) {
                        selected_chars.push_back(&base[i]);
                    }
                    ++filtered_offset;
                }
            }
            filter sub_pred = [selected_chars](const char& c) {
                for (auto ptr : selected_chars) {
                    if (&c == ptr)
                        return true;
                }
                return false;
            };
            result.emplace_back(base, sub_pred);
            if (pos == std::string::npos)
                break;
            start = pos + tok_str.size();
        }
        return result;
    }
    auto substr(const filtered_string_view& fsv, std::size_t pos, std::optional<std::size_t> count)
        -> filtered_string_view {
        std::size_t fsv_size = fsv.size();
        if (pos > fsv_size) {
            throw std::out_of_range{"filtered_string_view::substr(" + std::to_string(pos)
                                    + "): position out of range for filtered string of size " + std::to_string(fsv_size)};
        }
        std::size_t end = count ? std::min(pos + count.value(), fsv_size) : fsv_size;
        std::vector<const char*> selected_chars;
        std::size_t filtered_index = 0;
        const char* base = fsv.data();
        const auto& pred = fsv.predicate();
        for (std::size_t i = 0; i < std::strlen(base); ++i) {
            if (pred(base[i])) {
                if (filtered_index >= pos && filtered_index < end) {
                    selected_chars.push_back(&base[i]);
                }
                ++filtered_index;
            }
        }
        filter sub_pred = [selected_chars](const char& c) {
            for (auto ptr : selected_chars) {
                if (&c == ptr) {
                    return true;
                }
            }
            return false;
        };
        return filtered_string_view{base, sub_pred};
    }
} // namespace fsv
