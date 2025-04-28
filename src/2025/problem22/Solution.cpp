#include "Solution.h"

Point4 Solution::vectors[] = {
    Point4( 0,  0,  0, 0),
    Point4(-1,  0,  0, 0),
    Point4( 1,  0,  0, 0),
    Point4( 0, -1,  0, 0),
    Point4( 0,  1,  0, 0),
    Point4( 0,  0, -1, 0),
    Point4( 0,  0,  1, 0)
};

int Solution::Part1() {
    const uint16_t Zero  = 0x4920;
    int total = 0;
    for (int i = 0; i < length * lcm; ++i) {
        counts[i] = Zero;
    }
    for (const Rule& rule: rules) {
        for (const Point4& point: range) {
            if (rule.IsDebris(point)) {
                Point4 p(point), v(rule.velocity);
                size_t index;
                for (int i = 0, offset = 0; i < lcm; ++i, offset += length) {
                    if (!(p = (p + v) % range).W() && (index = range3.GetIndex(p))) {
                        ++counts[index + offset];
                    }
                }
                ++total;
            }
        }
    }
    return total;
}

int Solution::Part2() {
    const Point3 start, end = range.max;
    std::vector<Point3> pts1, pts2, *pCurr = &pts1, *pNext = &pts2;
    pCurr->push_back(start);
    size_t index;
    for (int time = 0; ; ++time, std::swap(pCurr, pNext), pNext->clear()) {
        Count *counts = this->counts + time % lcm * length;
        for (const Point3& p: *pCurr) {
            if (p == end) {
                return time;
            }
            for (const Point4& v: vectors) {
                const Point3 q = p + Point3(v);
                if (range3.TryGetIndex(q, index)) {
                    if (!(counts[index] & (CountMask | SeenMask))) {
                        counts[index] |= SeenMask;
                        pNext->push_back(q);
                    }
                }
            }
        }
    }
    return -1;
}

int Solution::Part3() {
    const uint16_t MaxHits = 3;
    const Point4 start, end = range.max.WithW(MaxHits);
    std::vector<Point4> pts1, pts2, *pCurr = &pts1, *pNext = &pts2;
    pCurr->push_back(start);
    size_t index;
    for (int time = 0; ; ++time, std::swap(pCurr, pNext), pNext->clear()) {
        Count *counts = this->counts + time % lcm * length;
        Count shift = (time / lcm + 1) * 3;
        for (const Point4& p: *pCurr) {
            if (p == end) {
                return time;
            }
            for (const Point4& v: vectors) {
                Point4 q = p + v;
                if (range3.TryGetIndex(q, index)) {
                    const Count count = counts[index], hits = count & CountMask;
                    if ((q.W() += hits) < (count >> shift & CountMask)) {
                        counts[index] = hits | q.W() << shift;
                        pNext->push_back(q);
                    }
                }
            }
        }
    }
    return -1;
}
