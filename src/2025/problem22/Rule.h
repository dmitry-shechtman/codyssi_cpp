#pragma once

#include "Range.h"

typedef Point<int16_t, 4> Point4;
typedef Range<int16_t, 4> Range4;
typedef Point<int16_t, 3> Point3;
typedef Range<int16_t, 3> Range3;

struct Rule {
    Point4 factor;
    int divisor;
    int remainder;
    Point4 velocity;

    constexpr bool IsDebris(const Point4& point) const {
        int dot = 0;
        for (int i = 0; i < 4; ++i) {
            dot += point[i] * factor[i];
        }
        while (dot < 0) {
            dot += divisor;
        }
        return dot % divisor == remainder;
    }
};

template<typename S>
std::basic_istream<S>& operator >>(std::basic_istream<S>& in, Rule& rule) {
    std::string s;
    S c;
    return in >> s >> s >>
        rule.factor >> s >> s >>
        rule.divisor >> s >> s >>
        rule.remainder >> s >> s >> s >> c >>
        rule.velocity;
}
