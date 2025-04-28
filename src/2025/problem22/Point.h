#pragma once

#include <iostream>
#include <numeric>

template<typename T, int K>
requires(std::is_signed_v<T> && K > 0)
class Point {
    T values[K]{};

public:
    constexpr Point() {}
    constexpr ~Point() {}

    constexpr Point(T x, T y) requires(K == 2);
    constexpr Point(T x, T y, T z) requires(K == 3);
    constexpr Point(T x, T y, T z, T w) requires(K == 4);

    template<int L>
    constexpr Point(const Point<T, L>& point) requires(L >= K);

    constexpr T X() const requires(K > 0) { return values[0]; }
    constexpr T Y() const requires(K > 1) { return values[1]; }
    constexpr T Z() const requires(K > 2) { return values[2]; }
    constexpr T W() const requires(K > 3) { return values[3]; }
    constexpr T operator [](size_t index) const {
        return values[index];
    }

    constexpr T& X() requires(K > 0) { return values[0]; }
    constexpr T& Y() requires(K > 1) { return values[1]; }
    constexpr T& Z() requires(K > 2) { return values[2]; }
    constexpr T& W() requires(K > 3) { return values[3]; }
    constexpr T& operator [](size_t index) {
        return values[index];
    }

    constexpr Point WithX(T value) const requires(K > 0) { return With(0, value); }
    constexpr Point WithY(T value) const requires(K > 1) { return With(1, value); }
    constexpr Point WithZ(T value) const requires(K > 2) { return With(2, value); }
    constexpr Point WithW(T value) const requires(K > 3) { return With(3, value); }
    constexpr Point With(int index, T value) const;

    static constexpr Point One();
};

template<typename T, int K>
constexpr Point<T, K>::Point(T x, T y)
requires(K == 2) {
    values[0] = x;
    values[1] = y;
}

template<typename T, int K>
constexpr Point<T, K>::Point(T x, T y, T z)
requires(K == 3) {
    values[0] = x;
    values[1] = y;
    values[2] = z;
}

template<typename T, int K>
constexpr Point<T, K>::Point(T x, T y, T z, T w)
requires(K == 4) {
    values[0] = x;
    values[1] = y;
    values[2] = z;
    values[3] = w;
}

template<typename T, int K>
template<int L>
constexpr Point<T, K>::Point(const Point<T, L>& point) requires(L >= K) {
    for (int i = 0; i < K; ++i) {
        values[i] = point[i];
    }
}

template<typename T, int K>
constexpr Point<T, K> Point<T, K>::With(int index, T value) const {
    Point<T, K> point = *this;
    point[index] = value;
    return point;
}

template<typename T, int K>
constexpr Point<T, K> Point<T, K>::One() {
    Point one;
    for (int i = 0; i < K; ++i) {
        one[i] = 1;
    }
    return one;
}

template<typename T, int K>
Point<T, K> operator +(const Point<T, K>& left, const Point<T, K>& right) {
    Point<T, K> point;
    for (int i = 0; i < K; ++i) {
        point[i] = left[i] + right[i];
    }
    return point;
}

template<typename T, int K>
Point<T, K> operator -(const Point<T, K>& left, const Point<T, K>& right) {
    Point<T, K> point;
    for (int i = 0; i < K; ++i) {
        point[i] = left[i] - right[i];
    }
    return point;
}

template<typename T, int K>
Point<T, K>& operator +=(Point<T, K>& left, const Point<T, K>& right) {
    for (int i = 0; i < K; ++i) {
        left[i] += right[i];
    }
    return left;
}

template<typename T, int K>
Point<T, K>& operator -=(Point<T, K>& left, const Point<T, K>& right) {
    for (int i = 0; i < K; ++i) {
        left[i] -= right[i];
    }
    return left;
}

template<typename T, int K>
bool operator ==(const Point<T, K>& left, const Point<T, K>& right) {
    for (int i = 0; i < K; ++i) {
        if (left[i] != right[i]) {
            return false;
        }
    }
    return true;
}

template<typename T, int K>
bool operator !=(const Point<T, K>& left, const Point<T, K>& right) {
    return !(left == right);
}

namespace std {
    template<typename T, int K>
    constexpr T dot(const Point<T, K>& left, const Point<T, K>& right) {
        T dot = 0;
        for (int i = 0; i < K; ++i) {
            dot += left[i] * right[i];
        }
        return dot;
    }

    template<typename T, int K>
    constexpr T lcm(const Point<T, K>& point) {
        T lcm = 1;
        for (int i = 0; i < K; ++i) {
            lcm = std::lcm(lcm, point[i]);
        }
        return lcm;
    }
}

template<typename S, typename T, int K>
std::basic_istream<S>& operator >>(std::basic_istream<S>& in, Point<T, K>& point) {
    S c;
    for (int i = 0; i < K; ++i) {
        if (i > 0) {
            in >> c;
        }
        in >> point[i];
    }
    return in;
}

template<typename S, typename T, int K>
std::basic_ostream<S>& operator <<(std::basic_ostream<S>& out, const Point<T, K>& point) {
    for (int i = 0; i < K; ++i) {
        if (i > 0) {
            out << ',';
        }
        out << point[i];
    }
    return out;
}
