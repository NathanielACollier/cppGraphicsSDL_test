/*
 Nathaniel Collier
 8/25/2007
 Opengl Functions to do various things
   may use some of the sdl
*/
#include <string>
#include <iostream>
#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>


using namespace std;

#include "opengl_colors.h"
#include "nac_opengl.h"
#include "Bitmap.h"



bool mouse_within_rect( dim_type x, int m_x, int m_y )
{
   bool y_range = false,
		x_range = false;

   // m_x can be in the range of x to x+ width
   if( m_x >= x.x && m_x <= (x.x+x.w))
	   x_range = true;
   // m_y can be in the range y to y-height
   if( m_y >= x.y && m_y <= (x.y+x.h))
	   y_range = true;
   
   return x_range && y_range;
}




void draw_rect(  dim_type x )
{  
  

    /*
	 Points are drawn clockwize as follows for a rectangle
	   page 174 opengl Game Programming
	        (151 is the books page number)
      (x,x) (0,1)
      (x+w,y) (1,1) 
      (x+w,y+h) (1,0) 
      (x,y+h) (0,0) 

	1                          2
   (0,1).....................(1,1) 
		.                   .
		.                   .
		.                   .
		.                   .
		.                   .
		.                   .
		.                   .
   (0,0).....................(1,0)
     4                         3
     */

glBegin( GL_QUADS );

	 glTexCoord2i(0,1); 
	 glVertex2i(x.x,x.y);

     glTexCoord2i(1,1); 
	 glVertex2i(x.x+x.w,x.y);

     glTexCoord2i(1,0); 
	 glVertex2i(x.x+x.w,x.y+x.h);

     glTexCoord2i(0,0); 
	 glVertex2i(x.x,x.y+x.h);
  glEnd();
}




/*
 As far as I can tell the image MUST be a 24bit bitmap
   I had all kinds of trouble untill I changed a bitmap from 4bits per pixel
   to 24 bits per pixel like the ones that worked.
*/

void draw_bitmap( string filename, int x, int y )
{
    GLuint texture; // Texture object handle
	Bitmap *image = new Bitmap();

	image->loadBMP( filename.c_str() );
    
	glGenTextures(1, &texture); 

	glBindTexture(GL_TEXTURE_2D, texture);
    

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);


	glTexImage2D(GL_TEXTURE_2D, 0, 4, image->width,image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data );
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image->width,image->height, GL_RGB, GL_UNSIGNED_BYTE, image->data );

    


	draw_rect( dim_type( x,y,image->width,image->height) );

	glDeleteTextures(1,&texture );
	delete image;
    
}


