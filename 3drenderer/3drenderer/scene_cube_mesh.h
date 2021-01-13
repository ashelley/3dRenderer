#ifndef SCENE_H
#define SCENE_H

#include "renderer.h"

#define N_MESH_VERTICES 8
#define N_MESH_FACES 6*2 // 6 cube faces, 2 triangles per face

vec3 cube_rotation = { .x = 0, .y = 0, .z = 0 };
vec3* mesh_vertices;
vec3i* mesh_faces;

triangle* triangles_to_render;

void scene_initialize() {
	mesh_vertices = (vec3*)(malloc(sizeof(vec3) * N_MESH_VERTICES));
    mesh_faces = (vec3i*)(malloc(sizeof(vec3i) * N_MESH_FACES));
    triangles_to_render = (triangle*)malloc(sizeof(triangle) * N_MESH_FACES);
    
    mesh_vertices[0] = (vec3){ .x = -1, .y = -1, .z = -1 };
    mesh_vertices[1] = (vec3){ .x = -1, .y = 1, .z = -1 };
    mesh_vertices[2] = (vec3){ .x = 1, .y = 1, .z = -1 };
    mesh_vertices[3] = (vec3){ .x = 1, .y = -1, .z = -1 };
    mesh_vertices[4] = (vec3){ .x = 1, .y = 1, .z = 1 };
    mesh_vertices[5] = (vec3){ .x = 1, .y = -1, .z = 1 };
    mesh_vertices[6] = (vec3){ .x = -1, .y = 1, .z = 1 };
    mesh_vertices[7] = (vec3){ .x = -1, .y = -1, .z = 1 };

    // front
    mesh_faces[0] = (vec3i){ .a = 1, .b = 2, .c = 3 };
    mesh_faces[1] = (vec3i){ .a = 1, .b = 3, .c = 4 };
    // right
    mesh_faces[2] = (vec3i){ .a = 4, .b = 3, .c = 5 };
    mesh_faces[3] = (vec3i){ .a = 4, .b = 5, .c = 6 },
    // back
    mesh_faces[4] = (vec3i){ .a = 6, .b = 5, .c = 7 };
    mesh_faces[5] = (vec3i){ .a = 6, .b = 7, .c = 8 };
    // left
    mesh_faces[6] = (vec3i){ .a = 8, .b = 7, .c = 2 };
    mesh_faces[7] = (vec3i){ .a = 8, .b = 2, .c = 1 };
    // top
    mesh_faces[8] = (vec3i){ .a = 2, .b = 7, .c = 5 };
    mesh_faces[9] = (vec3i){ .a = 2, .b = 5, .c = 3 };
    // bottom
    mesh_faces[10] = (vec3i){ .a = 6, .b = 8, .c = 1 };
    mesh_faces[11] = (vec3i){ .a = 6, .b = 1, .c = 4 };
}

void scene_update() {
    cube_rotation.x += 0.01;
    cube_rotation.y += 0.01;
    cube_rotation.z += 0.01;

    for (int i = 0; i < N_MESH_FACES; i++) {
        vec3i face = mesh_faces[i];

        vec3 verts[3];
        verts[0] = mesh_vertices[face.a - 1];
        verts[1] = mesh_vertices[face.b - 1];
        verts[2] = mesh_vertices[face.c - 1];

        triangle tri;

        for (int j = 0; j < 3; j++) {
            vec3 transformed = verts[j];
            transformed = rotate_x(transformed, cube_rotation.x);
            transformed = rotate_y(transformed, cube_rotation.y);
            transformed = rotate_z(transformed, cube_rotation.z);

            transformed.z -= camera_pos.z;

            vec2 pos = project(transformed);

            tri.points[j] = pos;
        }

        triangles_to_render[i] = tri;

    }
}

void scene_render() {
    for (int i = 0; i < N_MESH_FACES; i++) {
        triangle tri = triangles_to_render[i];

        draw_triangle(
            tri.points[0].x + (window_width / 2),
            tri.points[0].y + (window_height / 2),
            tri.points[1].x + (window_width / 2),
            tri.points[1].y + (window_height / 2),
            tri.points[2].x + (window_width / 2),
            tri.points[2].y + (window_height / 2),
            0xFF00FF00
        );

        draw_rect(tri.points[0].x + (window_width / 2), tri.points[0].y + (window_height / 2), 5, 5, 0xFFFFFF00);
        draw_rect(tri.points[1].x + (window_width / 2), tri.points[1].y + (window_height / 2), 5, 5, 0xFFFFFF00);
        draw_rect(tri.points[2].x + (window_width / 2), tri.points[2].y + (window_height / 2), 5, 5, 0xFFFFFF00);
    }
}

#endif