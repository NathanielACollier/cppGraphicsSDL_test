/*
  Nathaniel Collier
   8/25/2007
 Opengl Functions to do various things
   may use some of the sdl
*/

// describes a rectangle
struct dim_type
{
  int x; // x pos
  int y; // y pos
  int w; // width
  int h; // height

  dim_type(int _x,int _y, int _w,int _h )
  {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
  }
};



bool mouse_within_rect( dim_type x, int m_x, int m_y );
void draw_rect( dim_type x );
void draw_bitmap( string filename, int x, int y );


