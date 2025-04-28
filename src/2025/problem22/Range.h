#pragma once

#include "Point.h"

template<typename T, int K>
requires(std::is_signed_v<T> && K > 0)
struct Range {
    class Iterator {
        using value_type        = Point<T, K>;
        using difference_type   = std::ptrdiff_t;
        using reference         = const Point<T, K>&;
        using pointer           = const Point<T, K>*;
        using iterator_category = std::bidirectional_iterator_tag;

        const Range<T, K>& range;
        Point<T, K> point;

        constexpr Iterator(const Range<T, K>& range, const Point<T, K>& point)
            : range(range), point(point) {}

    public:
        constexpr ~Iterator() {}
        constexpr reference operator * () const { return point; }
        constexpr pointer   operator ->() const { return &point; }
        constexpr Iterator& operator ++();
        constexpr Iterator& operator --();
        constexpr Iterator  operator ++(int);
        constexpr Iterator  operator --(int);
        constexpr bool operator ==(const Iterator& other) const;
        constexpr bool operator !=(const Iterator& other) const;

        friend Range;
    };

    const Point<T, K> min;
    const Point<T, K> max;

    constexpr Range() {}
    constexpr ~Range() {}

    constexpr Range(const Point<T, K>& min, const Point<T, K>& max)
        : min(min), max(max) {}

    template<int L>
    constexpr Range(const Range<T, L>& range) requires(L >= K)
        : min(range.min), max(range.max) {}

    constexpr T Width()   const requires(K > 0) { return (*this)[0]; }
    constexpr T Height()  const requires(K > 1) { return (*this)[1]; }
    constexpr T Depth()   const requires(K > 2) { return (*this)[2]; }
    constexpr T Anakata() const requires(K > 3) { return (*this)[3]; }

    constexpr T operator [](size_t index) const requires(std::is_integral_v<T>);

    constexpr T Length() const;
    constexpr Point<T, K> Size() const;
    constexpr bool Contains(const Point<T, K>& point) const;
    constexpr size_t GetIndex(Point<T, K> point) const requires(std::is_integral_v<T>);
    constexpr bool TryGetIndex(Point<T, K> point, size_t& index) const requires(std::is_integral_v<T>);

    constexpr Iterator cbegin() const requires(std::is_integral_v<T>);
    constexpr Iterator begin() const requires(std::is_integral_v<T>);
    constexpr Iterator cend() const requires(std::is_integral_v<T>);
    constexpr Iterator end() const requires(std::is_integral_v<T>);

    static constexpr Range FromMinAndSize(const Point<T, K>& min, const Point<T, K>& size)
    requires(std::is_integral_v<T>);
};

template<typename T, int K>
constexpr T Range<T, K>::operator [](size_t index) const
requires(std::is_integral_v<T>) {
    return max[index] - min[index] + 1;
}

template<typename T, int K>
constexpr T Range<T, K>::Length() const {
    T length = 1;
    for (int i = 0; i < K; ++i) {
        length *= (*this)[i];
    }
    return length;
}

template<typename T, int K>
constexpr Point<T, K> Range<T, K>::Size() const {
    Point<T, K> size;
    for (int i = 0; i < K; ++i) {
        size[i] = (*this)[i];
    }
    return size;
}

template<typename T, int K>
constexpr bool Range<T, K>::Contains(const Point<T, K>& point) const {
    for (int i = 0; i < K; ++i) {
        if (point[i] < min[i] || point[i] > max[i]) {
            return false;
        }
    }
    return true;
}

template<typename T, int K>
constexpr size_t Range<T, K>::GetIndex(Point<T, K> point) const
requires(std::is_integral_v<T>) {
    size_t index = 0;
    for (int i = 0; i < K; ++i) {
        index = (index * (*this)[i]) + point[i] - min[i];
    }
    return index;
}

template<typename T, int K>
constexpr bool Range<T, K>::TryGetIndex(Point<T, K> point, size_t& index) const
requires(std::is_integral_v<T>) {
    if (!Contains(point)) {
        return false;
    }
    index = GetIndex(point);
    return true;
}

template<typename T, int K>
constexpr Range<T, K>::Iterator& Range<T, K>::Iterator::operator ++() {
    for (int i = K - 1; i >= 0 && point[i]++ == range.max[i]; --i) {
        point[i] = i ? range.min[i] : point[i];
    }
    return *this;
}

template<typename T, int K>
constexpr Range<T, K>::Iterator& Range<T, K>::Iterator::operator --() {
    for (int i = K - 1; i >= 0 && point[i]-- == range.min[i]; --i) {
        point[i] = i ? range.max[i] : point[i];
    }
    return *this;
}

template<typename T, int K>
constexpr Range<T, K>::Iterator Range<T, K>::Iterator::operator ++(int) {
    Iterator old(*this);
    ++*this;
    return old;
}

template<typename T, int K>
constexpr Range<T, K>::Iterator Range<T, K>::Iterator::operator --(int) {
    Iterator old(*this);
    --*this;
    return old;
}

template<typename T, int K>
constexpr bool Range<T, K>::Iterator::operator ==(const Range<T, K>::Iterator& other) const {
    return this->point == other.point;
}

template<typename T, int K>
constexpr bool Range<T, K>::Iterator::operator !=(const Range<T, K>::Iterator& other) const {
    return !(*this == other);
}

template<typename T, int K>
constexpr Range<T, K>::Iterator Range<T, K>::cbegin() const
requires(std::is_integral_v<T>) {
    return Iterator(*this, min);
}

template<typename T, int K>
constexpr Range<T, K>::Iterator Range<T, K>::begin() const
requires(std::is_integral_v<T>) {
    return cbegin();
}

template<typename T, int K>
constexpr Range<T, K>::Iterator Range<T, K>::cend() const
requires(std::is_integral_v<T>) {
    return Iterator(*this, min.WithX(max.X() + 1));
}

template<typename T, int K>
constexpr Range<T, K>::Iterator Range<T, K>::end() const
requires(std::is_integral_v<T>) {
    return cend();
}

template<typename T, int K>
constexpr Range<T, K> Range<T, K>::FromMinAndSize(const Point<T, K>& min, const Point<T, K>& size)
requires(std::is_integral_v<T>) {
    return Range(min, min + size - Point<T, K>::One());
}

template<typename T, int K>
Point<T, K> operator %(const Point<T, K>& point, const Range<T, K>& range)
requires(std::is_integral_v<T>) {
    Point<T, K> mod;
    for (int i = 0; i < K; ++i) {
        mod[i] = point[i] - range.min[i];
        while (mod[i] < 0) {
            mod[i] += range[i];
        }
        mod[i] = (mod[i] % range[i]) + range.min[i];
    }
    return mod;
}

template<typename S, typename T, int K>
std::basic_istream<S>& operator >>(std::basic_istream<S>& in, Range<T, K>& range) {
    S c;
    return in >> range.min >> c >> range.max;
}

template<typename S, typename T, int K>
std::basic_ostream<S>& operator <<(std::basic_ostream<S>& out, const Range<T, K>& range) {
    return out << range.min << '~' << range.max;
}
