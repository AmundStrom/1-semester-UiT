#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL.h>
#include <time.h>
#include "drawline.h"
#include "triangle.h"
#include "list.h"
#include "teapot_data.h"
#include "sphere_data.h"
#include "object.h"

/* Two macro's that find the lesser or greater of two values */
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

/*
 * Clear the surface by filling it with 0x00000000(black).
 */
void clear_screen(SDL_Surface *surface)
{
    if(SDL_FillRect(surface, NULL, 0x00000000) < 0){
        fprintf(stderr, "Unable to clear the surface. Error returned: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

/*
 * Accelerate the object; altering its speed based on the boost given.
 */
void accelerate_object(object_t *a, float boost, float maxspeed)
{
    float s;
    float news;
    
    /* Calculate lenght of speed vector */
    s = sqrtf(a->speedx * a->speedx + a->speedy * a->speedy);

    /* Boost speed */
    news = s * boost;
    if (news < 0.0)
        news = 0.0;
    if (news > maxspeed)
        news = maxspeed;    
    a->speedx *= news/s;
    a->speedy *= news/s;
}

/*
 * Animate bouncing balls on the screen.
 */
void bouncing_balls(SDL_Window *window)
{
    SDL_Event event;
    SDL_Surface *surface;
    surface = SDL_GetWindowSurface(window);

    /* declaring variables */
    int i;
    list_t *list = list_create();
    list_iterator_t *iter = list_createiterator(list);
    object_t *object;

    /* initiate time */
    srand(time(NULL));

        /* creates a list with 5 objects */
        for(i = 0; i < 5; i++){
            object = create_object(surface, sphere_model, SPHERE_NUMTRIANGLES);
            list_addlast(list, object);
            printf("object %i, speedx: %f\n", i, object->speedx);
        }

    /* Wait for the user to exit the application */
    /* Animation loop */
    int done = 0;
    while (!done)
    {
        /* Update the window surface */
        SDL_UpdateWindowSurface(window);
        /* Makes the window surface black */
        clear_screen(surface);

        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    done = 1;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_SHOWN)
                        SDL_SetWindowPosition(window, 50, 50);
                    break;
            }          
        }

/* Animation content */

    /* reset the list iterator, so it points to the first item in the list */
    list_resetiterator(iter);

    /* a for-loop equal to the size of the list, so every item in the list will be updated every "frame" */
    for(i = 0; i < list_size(list); i++){
        
        /* set object equal to the current item in the list, 
        list_next(iter) will then move to the next item in the list */
        object = list_next(iter);

        /* Check if the object is outside of the width of the screen.
        if it is, multiply speedx with -1 so it will change direction */
        if(object->tx + (object->radius + object->speedx) >= surface->w || object->tx - (object->radius + fabs(object->speedx)) <= 0){
            object->speedx = (object->speedx) * (-1);
        }
        /* Check if the object is outside of the height of the screen.
        if it is, multiply speedy with -1 so it will change direction.
        we also want it to lose some speed when it hits the ground, therefore we add the accelerate_object funtion */
        if(object->ty + (object->radius + object->speedy) >= surface->h || object->ty - (object->radius + fabs(object->speedy)) <= 0){
            object->speedy = (object->speedy) * (-1);
            accelerate_object(object, 0.8, fabs(object->speedy));
        }

        /* change the position of the object on the screen, this will make the illusion of the object moving */
        object->tx += object->speedx;
        object->ty += object->speedy; 
        object->rotation += object->speedx;
        object->speedy += 0.04;

        /* draws the object */
        draw_object(object);

        /* if the object is visibly still, decrease object->ttl by 1 
        if object->ttl is 0 (which takes about 5 seconds) remove and destroy the ball, and create a new one */
        if(object->speedx < 0.01 && object->speedx > -0.01){
            object->ttl--;
            if(object->ttl == 0){
                list_remove(list, object);
                destroy_object(object);
                object = create_object(surface, sphere_model, SPHERE_NUMTRIANGLES);
                list_addlast(list, object);
            }
        }
    }   /* end of for-loop */

    /* if list is empty, destroy the whole list 
    (this will never be true, but i have tested it and it works) */
    if(list_size(list) == 0){
        list_destroyiterator(iter);
        list_destroy(list);
        printf("list is destroyed\n");
    }

    /* wait 3ms before repeating the animation loop */            
    SDL_Delay(3);
    } 
}

int main(void)
{
    const size_t bufsize = 100;
    
    /* Change the screen width and height to your own liking */
    const int screen_w = 1200;
    const int screen_h = 600;

    char errmsg[bufsize];
    SDL_Window *window;

    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < -1) {
        snprintf(errmsg, bufsize, "Unable to initialize SDL.");
        goto error;
    }
    
    /* Create a 1200x650 window */
    window = SDL_CreateWindow("The Amazing Bouncing Balls",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screen_w, screen_h,
                              0);
    if(!window) {
        snprintf(errmsg, bufsize, "Unable to get video surface.");
        goto error;
    }

    /* Start bouncing some balls */
    bouncing_balls(window);

    /* Wait a little bit jic something went wrong (so that printfs can be read) */
    // SDL_Delay(5000); 

    /* Shut down SDL */
    SDL_Quit();
    
    return 0;

    /* Upon an error, print message and quit properly */
error:
    fprintf(stderr, "%s Error returned: %s\n", errmsg, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}