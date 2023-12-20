#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <array>
#include <algorithm>

namespace generic{
    template <typename U, typename V>
    std::ostream& operator<<(std::ostream& os, const std::pair<U, V>& p) {
        os << "{" << p.first << ": " << p.second << "}";
        return os;
    }

    template <typename T, typename U = T>
    class ostream_iterator {
    public:
        ostream_iterator(std::ostream& os, const char* delimiter)
            : os_(os), delimiter_(delimiter) {}

        template <typename V>
        typename std::enable_if<!std::is_same<T, std::vector<V>>::value &&
                                !std::is_same<T, std::map<V, V>>::value &&
                                !std::is_same<T, std::array<V, 0>>::value &&
                                !std::is_same<T, std::array<V, 1>>::value &&
                                !std::is_same<T, std::list<V>>::value,
                                ostream_iterator>::type
        operator=(const V& value) {
            os_ << value << delimiter_;
            return *this;
        }

        template <typename V>
        typename std::enable_if<std::is_same<T, std::vector<V>>::value, ostream_iterator>::type
        operator=(const std::vector<V>& values) {
            os_ << "{ ";
            if (!values.empty()) {
                std::copy(values.begin(), values.end() - 1, ostream_iterator<V, U>(os_, delimiter_));
                ostream_iterator<V, U>(os_, delimiter_) = values.back();
            }
            os_ << "}" << delimiter_;
            return *this;
        }

        template <typename V>
        typename std::enable_if<std::is_same<T, std::list<V>>::value, ostream_iterator>::type
        operator=(const std::list<V>& values) {
            os_ << "{ ";
            if (!values.empty()) {
                auto it = values.begin();
                ostream_iterator<V, U>(os_, delimiter_) = *it;
                ++it;
                for (; it != values.end(); ++it) {
                    os_ << delimiter_;
                    ostream_iterator<V, U>(os_, delimiter_) = *it;
                }
            }
            os_ << "}" << delimiter_;
            return *this;
        }

        template <typename V, std::size_t N>
        typename std::enable_if<std::is_same<T, std::array<V, N>>::value, ostream_iterator>::type
        operator=(const std::array<V, N>& values) {
            os_ << "{ ";
            std::copy(values.begin(), values.end(), ostream_iterator<V, U>(os_, delimiter_));
            os_ << "}" << delimiter_;
            return *this;
        }

        ostream_iterator& operator*() {
            return *this;
        }

        ostream_iterator* operator->() {
            return this;
        }

        ostream_iterator& operator++() {
            return *this;
        }

        ostream_iterator operator++(int) {
            return *this;
        }

    private:
        std::ostream& os_;
        const char* delimiter_;
    };
}