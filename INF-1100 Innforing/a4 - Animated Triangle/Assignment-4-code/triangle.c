#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "triangle.h"
#include "drawline.h"
#include <math.h>

#define TRIANGLE_PENCOLOR   0xBBBB0000

/* 
 * Print triangle coordinates along with a message
 */
void print_triangle(triangle_t *triangle, char *msg)
{
    printf("%s: %d,%d - %d,%d - %d,%d\n",
        msg,
        triangle->x1, triangle->y1, 
        triangle->x2, triangle->y2, 
        triangle->x3, triangle->y3);
}

/*
 * Return 0 if triangle coordinates are outside the surface boundary. 1 otherwise.
 */
int sanity_check_triangle(SDL_Surface *surface, triangle_t *triangle)
{
    if (triangle->sx1 < 0 || triangle->sx1 >= surface->w ||
        triangle->sx2 < 0 || triangle->sx2 >= surface->w ||
        triangle->sx3 < 0 || triangle->sx3 >= surface->w ||
        triangle->sy1 < 0 || triangle->sy1 >= surface->h ||
        triangle->sy2 < 0 || triangle->sy2 >= surface->h ||
        triangle->sy3 < 0 || triangle->sy3 >= surface->h) {
        return 0;
    } else {
        return 1;
    }
}

/*
 * Scale triangle, altering the on-screen coordinates(e.g. triangle->sx1)
 */
void scale_triangle(triangle_t *triangle)
{
    // TODO: Replace the code below with code that scales each triangle coordinate. 
    // The scaling factor is specified in triangle->scale.
    // Remember that this function MUST write to the on-surface coordinates.
    // Do not alter the model coordinates.

    triangle->sx1 = (triangle->x1 * triangle->scale);
    triangle->sx2 = (triangle->x2 * triangle->scale);
    triangle->sx3 = (triangle->x3 * triangle->scale);
    triangle->sy1 = (triangle->y1 * triangle->scale);
    triangle->sy2 = (triangle->y2 * triangle->scale);
    triangle->sy3 = (triangle->y3 * triangle->scale);
}

/*
 * Move the triangle to the center of the surface,
 * altering the on-screen coordinates(e.g. triangle->sx1)
 */
void translate_triangle(triangle_t *triangle)
{
    // TODO: Insert code that moves the triangle on the surface.
    // The translation coordinates are specified in triangle->tx and triangle->ty.
    // Remember to use the on-surface coordinates (triangle->sx1, etc.)

    triangle->tx = 1024/2;
    triangle->ty = 768/2;

    triangle->sx1 = (triangle->sx1 + triangle->tx);
    triangle->sy1 = (triangle->sy1 + triangle->ty);
    triangle->sx2 = (triangle->sx2 + triangle->tx);
    triangle->sy2 = (triangle->sy2 + triangle->ty);
    triangle->sx3 = (triangle->sx3 + triangle->tx);
    triangle->sy3 = (triangle->sy3 + triangle->ty);
}

/*
 * Calculate the triangle bounding box,
 * altering fields of the triangle's rect(e.g. triangle->rect.x)
 */
void calculate_triangle_bounding_box(triangle_t *triangle)
{
    // TODO: Insert code that calculates the bounding box of a triangle.
    // Remember to use the on-surface coordinates (triangle->sx1, etc.)
    // The bounding box coordinates should be written to 
    // triangle->rect.x, triangle->rect.y, triangle->rect.w, triangle->rect.h

    int lowestX, lowestY;
    int highestX, highestY;

    /* checking which X value is the lowest */
    if((triangle->sx1 <= triangle->sx2) && (triangle->sx1 <= triangle->sx3)){
        lowestX = triangle->sx1;
    }
    if((triangle->sx2 <= triangle->sx1) && (triangle->sx2 <= triangle->sx3)){
        lowestX = triangle->sx2;
    }
    if((triangle->sx3 <= triangle->sx1) && (triangle->sx3 <= triangle->sx2)){
        lowestX = triangle->sx3;
    }

    /* checking which Y value is lowest */
    if((triangle->sy1 <= triangle->sy2) && (triangle->sy1 <= triangle->sy3)){
        lowestY = triangle->sy1;
    }
    if((triangle->sy2 <= triangle->sy1) && (triangle->sy2 <= triangle->sy3)){
        lowestY = triangle->sy2;
    }
    if((triangle->sy3 <= triangle->sy1) && (triangle->sy3 <= triangle->sy2)){
        lowestY = triangle->sy3;
    }

    /* checking which X value is the highest */
    if((triangle->sx1 >= triangle->sx2) && (triangle->sx1 >= triangle->sx3)){
        highestX = triangle->sx1;
    }
    if((triangle->sx2 >= triangle->sx1) && (triangle->sx2 >= triangle->sx3)){
        highestX = triangle->sx2;
    }
    if((triangle->sx3 >= triangle->sx1) && (triangle->sx3 >= triangle->sx2)){
        highestX = triangle->sx3;
    }

    /* checking which Y value is highest */
    if((triangle->sy1 >= triangle->sy2) && (triangle->sy1 >= triangle->sy3)){
        highestY = triangle->sy1;
    }
    if((triangle->sy2 >= triangle->sy1) && (triangle->sy2 >= triangle->sy3)){
        highestY = triangle->sy2;
    }
    if((triangle->sy3 >= triangle->sy1) && (triangle->sy3 >= triangle->sy2)){
        highestY = triangle->sy3;
    }
    
    triangle->rect.x = lowestX;
    triangle->rect.y = lowestY;
    triangle->rect.w = (highestX - lowestX);
    triangle->rect.h = (highestY - lowestY);
}

/*
 * Fill the triangle on the surface with the triangle's color
 */
void fill_triangle(SDL_Surface *surface, triangle_t *triangle)
{
    // TODO: Insert code that fills the triangle with the color specified in triangle->fillcolor.
    // Hint: Draw the triangle with color TRIANGLE_PENCOLOR (this color can not
    // occur in e.g. the teapot or the example triangles).  Thus, if your 
    // approach to filling the triangle relies on looking for the edges of
    // the triangle on the surface (via the GetPixel function), you will find those
    // edges even if the triangle overlaps with a triangle that has already
    // been drawn on the surface.
    
    int edgecounter;
    int xfirst, yfirst;
    int xlast, ylast;

    // increasing the Y coordinate within the bounding box
    for(int ycounter = (triangle->rect.y); ycounter <= (triangle->rect.y + triangle->rect.h); ycounter++)
    {
        edgecounter = 0;
        xfirst, yfirst = 0;
        xlast, ylast = 0;

        // increasing the X coordinate within the bounding box
        for(int xcounter = (triangle->rect.x); xcounter <= (triangle->rect.x + triangle->rect.w); xcounter++)
        {
            // checking if the color of the pixel is equal to the color of the triangle that is being filled
            if(get_pixel(surface, xcounter, ycounter) == triangle->fillcolor)
            {
                edgecounter++;
        
                // saving the coordinates of the first pixel that was equal to the correct color
                if(edgecounter == 1){
                    xfirst = xcounter;
                    yfirst = ycounter;
                }

                // saving the coordinates of the last pixel that was equal to the correct color
                if(edgecounter >= 1){
                    xlast = xcounter;
                    ylast = ycounter;
                }

                // draws a line between the first and last point of the correct color
                draw_line(surface, xfirst, yfirst, xlast, ylast, triangle->fillcolor);
            }
        }
    } 
}

void RotateTriangle(triangle_t *triangle)
{
        float radians = ((triangle->rotation * M_PI) / 180);

        triangle->sx1 = ( (cos(radians) * triangle->x1) - (sin(radians) * triangle->y1) );
        triangle->sy1 = ( (sin(radians) * triangle->x1) + (cos(radians) * triangle->y1) );
        triangle->sx2 = ( (cos(radians) * triangle->x2) - (sin(radians) * triangle->y2) );
        triangle->sy2 = ( (sin(radians) * triangle->x2) + (cos(radians) * triangle->y2) );
        triangle->sx3 = ( (cos(radians) * triangle->x3) - (sin(radians) * triangle->y3) );
        triangle->sy3 = ( (sin(radians) * triangle->x3) + (cos(radians) * triangle->y3) );
}

/*
 * Draw a filled triangle on the given surface
 */
void draw_triangle(SDL_Surface *surface, triangle_t *triangle)
{    
    int isOK;

    /* Scale. */
    scale_triangle(triangle);

    /* Rotation */
    RotateTriangle(triangle);
    
    /* Translate. */
    translate_triangle(triangle);
    
    /* Determine bounding box */
    calculate_triangle_bounding_box(triangle);

    /* Sanity check that triangle is within surface boundaries. */
    isOK = sanity_check_triangle(surface, triangle);
    if (!isOK) {
        print_triangle(triangle, "Triangle outside surface boundaries");
        return;
    }

    /* 
     * TODO: Insert calls to draw_line to draw the triangle.
     * Remember to use the on-surface coordinates (triangle->sx1, etc.)
     */

    /* Draws triangle wireframe */
    draw_line(surface, (triangle->sx1), (triangle->sy1), (triangle->sx2), (triangle->sy2), (triangle->fillcolor));
    draw_line(surface, (triangle->sx2), (triangle->sy2), (triangle->sx3), (triangle->sy3), (triangle->fillcolor));
    draw_line(surface, (triangle->sx3), (triangle->sy3), (triangle->sx1), (triangle->sy1), (triangle->fillcolor));

    /* Bounding box */
    //draw_line(surface, triangle->rect.x, triangle->rect.y, (triangle->rect.x + triangle->rect.w), triangle->rect.y, TRIANGLE_PENCOLOR);
    //draw_line(surface, (triangle->rect.x + triangle->rect.w), triangle->rect.y, (triangle->rect.x + triangle->rect.w), (triangle->rect.y + triangle->rect.h), TRIANGLE_PENCOLOR);  
    //draw_line(surface, (triangle->rect.x + triangle->rect.w), (triangle->rect.y + triangle->rect.h), triangle->rect.x, (triangle->rect.y + triangle->rect.h), TRIANGLE_PENCOLOR);
    //draw_line(surface, triangle->rect.x, triangle->rect.y, triangle->rect.x, (triangle->rect.y + triangle->rect.h), TRIANGLE_PENCOLOR); 

    /* Fill triangle */
    fill_triangle(surface, triangle);
}

