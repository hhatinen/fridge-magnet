#pragma once

#include <math.h>

typedef struct {
    float x, y;
} vec2;

inline vec2 vec2_add(vec2 a, vec2 b) {
    vec2 ret = {a.x + b.x, a.y + b.y};
    return ret;
}

inline vec2 vec2_sub(vec2 a, vec2 b) {
    vec2 ret = {a.x - b.x, a.y - b.y};
    return ret;
}

inline vec2 vec2_mul(vec2 a, float b) {
    vec2 ret = {a.x * b, a.y * b};
    return ret;
}

inline float vec2_len(vec2 a) {
    return sqrtf(a.x * a.x + a.y * a.y);
}

inline float vec2_lenSq(vec2 a) {
    return a.x * a.x + a.y * a.y;
}

inline float vec2_dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

inline vec2 vec2_norm(vec2 a) {
    float len = vec2_len(a);
    vec2 ret = {a.x / len, a.y / len};
    return ret;
}