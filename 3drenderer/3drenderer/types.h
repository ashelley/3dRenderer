#ifndef TYPES_H
#define TYPES_H

#include <stdbool.h>
#include <math.h>

typedef struct {
	float x;
	float y;
} vec2;

typedef struct {
	float x;
	float y;
	float z;
} vec3;

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


#endif
