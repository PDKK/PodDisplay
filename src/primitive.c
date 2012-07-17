
#include "support.h"		// support routines
#include "keys.h"		// defines key indexes for key down boolean array
#include "obj.h"		// loading and displaying wavefront OBJ derived shapes
#include "input.h"

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>		// usleep

#include <kazmath.h>		// matrix manipulation routines


typedef struct {
    float x,y,z;
} vertex_data_t;

typedef struct {
    vertex_data_t v1, v2, v3;
} triangle_data_t;

typedef struct {
    triangle_data_t t1, t2;
} slice_position_data_t;

typedef struct {
    float u,v;
} texture_data_t;

typedef struct {
    texture_data_t v1, v2, v3;
} triangle_texture_data_t;

typedef struct {
    triangle_texture_data_t t1, t2;
} slice_texture_data_t;

void createCylinder(struct obj_t * result) {
    // iterate around a cylinder, generating long triangles
    slice_position_data_t * vertices;
    slice_texture_data_t * texCoords;
    slice_position_data_t * normals;
    int slice;
    int num_slices = 10;
    float r = .2;
    float h = 1.0;

    /* 3 floats per vertex, 3 vertices per triangle, 2 triangles per face */
    vertices = (slice_position_data_t*) malloc(num_slices*sizeof(slice_position_data_t));
    /* 2 floats per vertex, 3 vertices per triangle, 2 triangles per face */
    texCoords = (slice_texture_data_t*) malloc(num_slices*sizeof(slice_texture_data_t));
    /* 3 floats per vertex, 3 vertices per triangle, 2 triangles per face */
    normals = (slice_position_data_t*) malloc(num_slices*sizeof(slice_position_data_t));

    for (slice=0;slice < num_slices; slice++) {
        // vertices
        vertices[slice].t1.v1.x = r*sin(2*3.14*slice/num_slices);
        vertices[slice].t1.v1.y = r*cos(2*3.14*slice/num_slices);
        vertices[slice].t1.v1.z = 0;
        vertices[slice].t1.v3.x = r*sin(2*3.14*slice/num_slices);
        vertices[slice].t1.v3.y = r*cos(2*3.14*slice/num_slices);
        vertices[slice].t1.v3.z = h;
        vertices[slice].t1.v2.x = r*sin(2*3.14*(slice+1)/num_slices);
        vertices[slice].t1.v2.y = r*cos(2*3.14*(slice+1)/num_slices);
        vertices[slice].t1.v2.z = h;
        vertices[slice].t2.v1.x = r*sin(2*3.14*slice/num_slices);
        vertices[slice].t2.v1.y = r*cos(2*3.14*slice/num_slices);
        vertices[slice].t2.v1.z = 0;
        vertices[slice].t2.v3.x = r*sin(2*3.14*(slice+1)/num_slices);
        vertices[slice].t2.v3.y = r*cos(2*3.14*(slice+1)/num_slices);
        vertices[slice].t2.v3.z = h;
        vertices[slice].t2.v2.x = r*sin(2*3.14*(slice+1)/num_slices);
        vertices[slice].t2.v2.y = r*cos(2*3.14*(slice+1)/num_slices);
        vertices[slice].t2.v2.z = 0;
        // normal
        normals[slice].t1.v1.x = sin(2*3.14*slice/num_slices);
        normals[slice].t1.v1.y = cos(2*3.14*slice/num_slices);
        normals[slice].t1.v1.z = 0;
        normals[slice].t1.v3.x = sin(2*3.14*slice/num_slices);
        normals[slice].t1.v3.y = cos(2*3.14*slice/num_slices);
        normals[slice].t1.v3.z = h;
        normals[slice].t1.v2.x = sin(2*3.14*(slice+1)/num_slices);
        normals[slice].t1.v2.y = cos(2*3.14*(slice+1)/num_slices);
        normals[slice].t1.v2.z = h;
        normals[slice].t2.v1.x = sin(2*3.14*slice/num_slices);
        normals[slice].t2.v1.y = cos(2*3.14*slice/num_slices);
        normals[slice].t2.v1.z = 0;
        normals[slice].t2.v3.x = sin(2*3.14*(slice+1)/num_slices);
        normals[slice].t2.v3.y = cos(2*3.14*(slice+1)/num_slices);
        normals[slice].t2.v3.z = h;
        normals[slice].t2.v2.x = sin(2*3.14*(slice+1)/num_slices);
        normals[slice].t2.v2.y = cos(2*3.14*(slice+1)/num_slices);
        normals[slice].t2.v2.z = 0;
        // normal
        // texture
        texCoords[slice].t1.v1.u = (float)slice/num_slices;
        texCoords[slice].t1.v1.v = 0;
        texCoords[slice].t1.v3.u = (float)slice/num_slices;
        texCoords[slice].t1.v3.v = 1;
        texCoords[slice].t1.v2.u = (float)(slice+1)/num_slices;
        texCoords[slice].t1.v2.v = 1;
        texCoords[slice].t2.v1.u = (float)slice/num_slices;
        texCoords[slice].t2.v1.v = 0;
        texCoords[slice].t2.v3.u = (float)(slice+1)/num_slices;
        texCoords[slice].t2.v3.v = 1;
        texCoords[slice].t2.v2.u = (float)(slice+1)/num_slices;
        texCoords[slice].t2.v2.v = 0;
        // normal
    }


    createObj(result, num_slices*6, (float *)vertices, (float *)texCoords, (float *)normals,
              "resources/shaders/textured.vert", "resources/shaders/textured.frag");
}
