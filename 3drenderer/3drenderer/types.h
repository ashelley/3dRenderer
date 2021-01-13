#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} vec2;

typedef struct {
    union {
        float x;
        float a;
    };

    union {
        float y;
        float b;
    };

    union {
        float z;
        float c;
    };
} vec3;

typedef struct {
    union {
        int x;
        int a;
    };

    union {
        int y;
        int b;
    };

    union {
        int z;
        int c;
    };
} vec3i;

static vec3 rotate_x(vec3 v, float angle) {
    vec3 rotated_vector = {
        .x = v.x,
        .y = v.y * cosf(angle) - v.z * sinf(angle),
        .z = v.y * sinf(angle) + v.z * cosf(angle)
    };
    return rotated_vector;
}

static vec3 rotate_y(vec3 v, float angle) {
    vec3 rotated_vector = {
        .x = v.x * cosf(angle) - v.z * sinf(angle),
        .y = v.y,
        .z = v.x * sinf(angle) + v.z * cosf(angle)
    };
    return rotated_vector;
}

static vec3 rotate_z(vec3 v, float angle) {
    vec3 rotated_vector = {
        .x = v.x * cosf(angle) - v.y * sinf(angle),
        .y = v.x * sinf(angle) + v.y * cosf(angle),
        .z = v.z
    };
    return rotated_vector;
}

typedef struct {
    vec2 points[3];
} triangle;


#endif
