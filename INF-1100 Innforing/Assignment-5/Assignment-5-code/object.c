#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "drawline.h"
#include "triangle.h"
#include "object.h"


/*
 * Return a newly created object based on the arguments provided.
 */
object_t *create_object(SDL_Surface *surface, triangle_t *model, int numtriangles)
{ 
    /* random variable */
    int r = rand();
    float random = r;
        while(random > 11){
            random = random/10;
        }

    object_t *NewObject = (object_t*)malloc(sizeof(object_t));
        NewObject->model = model;
        NewObject->surface = surface;
        NewObject->numtriangles = numtriangles;
        NewObject->rotation = 0;
        NewObject->scale = 0.1;
        NewObject->radius = (1000 * NewObject->scale) / 2;
        NewObject->tx = 150;
        NewObject->ty = 150;

        NewObject->speedx = random;
        NewObject->speedy = 0;
        NewObject->ttl = 400;
    return NewObject;
}

/*
 * Destroy the object, freeing the memory.
 */
void destroy_object(object_t *object)
{
    free(object);
}

/*
 * Draw the object on its surface.
 */
void draw_object(object_t *object)
{
    /* a for-loop that goes through every triangle of the sphere and changes them accordingly */
    for(int i = 0; i < object->numtriangles; i++)
    {
        object->model[i].tx = object->tx;
        object->model[i].ty = object->ty;
        object->model[i].scale = object->scale;
        object->model[i].rotation = object->rotation;
        draw_triangle(object->surface, &object->model[i]);    
    }
} 
