
// SDL Libraries
#pragma comment(lib,"SDL.lib")
#pragma comment(lib,"SDLmain.lib")
// Opengl Libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib" )
// freetype library
#pragma comment(lib, "freetype.lib")

/*
 Nathaniel Collier
 8/25/2007
 SDL Test Application
*/

#include <string>
#include <iostream>
#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>


using namespace std;

#include "opengl_colors.h"
#include "nac_opengl.h"
#include "FreeType.h"
#include "card_type.h"



vector<string> picture_list;
vector<card_type> card_list;
int pic_count = 0;


 freetype::font_data arialblk_8pt;
vector<string> load_file_list_from_file( string filename );
void end_game();
int process_events(SDL_Event& event, SDL_Surface*& screen );
void opengl_draw_test();
void setup_opengl( SDL_Surface*& screen );
vector<card_type> generate_cards( int min, int max );


int main ( int argc, char *argv[] )
{
  SDL_Surface* screen;
  SDL_Event event;
 

  //setup_screen( screen );
  int gameover = 0;
  
  atexit( end_game );

  setup_opengl( screen );
  

   picture_list = load_file_list_from_file( "pic_list.txt" );

   card_list = generate_cards(0,54);

   cout << "\nLoaded: " << card_list.size() << " cards" << endl;

   cout << "\nLoaded: " << picture_list.size() << " pictures" << endl;

   arialblk_8pt.init("arialblack.TTF", 8);	 //Build the freetype font

  cout << "\n" << glGetString(GL_EXTENSIONS) << endl;

    draw_bitmap( "image/image.bmp", 0 , 0 );
    draw_bitmap( "image/image.bmp", 128,128);
	draw_bitmap( "image/image.bmp", 256,256);
	draw_bitmap( "image/linux.bmp", 20, 300 );

	draw_bitmap( picture_list[pic_count] , 400,100);
    
	SDL_GL_SwapBuffers();
    
    
    //freetype::print(our_font, 0, 300, "Active FreeType Text - %d", 3);



   

  /* message pump */
  while (!gameover)
  {

    gameover = process_events(event,screen);

    /* update the screen */
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }

  /* cleanup SDL */
  end_game();

  return 0;
}

void setup_opengl( SDL_Surface*& screen )
{
    // Slightly different SDL initialization
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        return;
    }

    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*

    screen = SDL_SetVideoMode( 640, 480, 16, SDL_OPENGL /*| SDL_FULLSCREEN*/ ); // *changed*
    if ( !screen ) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		return;
	}
	
    // Set the OpenGL state after creating the context with SDL_SetVideoMode

    glClearColor(0,0,0,0);

	glEnable( GL_TEXTURE_2D ); // Need this to display a texture

    glViewport( 0, 0, 640, 480 );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho( 0, 640, 480, 0, -1, 1 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
     
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	SDL_GL_SwapBuffers();

}



int process_events(SDL_Event& event, SDL_Surface*& screen )
{
  int gameover = 0;

  int m_x=0,
	  m_y=0;

    /* look for an event */
    if (SDL_PollEvent(&event)) {
      /* an event was found */
      switch (event.type) {
        /* mouse button released */
	    case SDL_MOUSEBUTTONUP:

		  break;
	    /* mouse button pressed */
		case SDL_MOUSEBUTTONDOWN:
           
		  break;
	    /* mouse moved */
		case SDL_MOUSEMOTION:
		   
		   m_x = event.motion.x;
		   m_y = event.motion.y;

		   glColor3ubv( black );
		   draw_rect( dim_type(525,0,111,12) );

		   
		   glColor3ubv( green );
           freetype::print(arialblk_8pt, 525, 480 - 10 , "Mouse x:%d y:%d", m_x,m_y );

           glColor3ubv( black );
           draw_rect( dim_type(400,20,200,12) );
		   if( mouse_within_rect( dim_type(0,0,128,128), m_x,m_y ) )
		   {
		     glColor3ubv( red );
             freetype::print(arialblk_8pt,400,480 -30, "Mouse in first picture");
		   }
		   else
		   if( mouse_within_rect( dim_type(128,128,128,128),m_x,m_y))
		   {
             glColor3ubv( blue );
			 freetype::print(arialblk_8pt,400,480 -30, "Mouse in second picture");
		   }
		   else
		   if( mouse_within_rect( dim_type(256,256,256,256),m_x,m_y))
		   {
             glColor3ubv( green );
			 freetype::print(arialblk_8pt,400,480 -30, "Mouse in third picture" );
		   }
		   else
		   if( mouse_within_rect( dim_type(400,100,71,96),m_x,m_y ))
		   {
             glColor3ubv( yellow );
			 if( card_list.size() > pic_count )
			 {
               freetype::print(arialblk_8pt,400,480 -30, card_list[pic_count].name.c_str() );
			 }
			 else
			 {
			   freetype::print(arialblk_8pt,400,480 -30, "Mouse in Card Picture" );
			 }
		   }

		   SDL_GL_SwapBuffers();
		  break;
        /* close button clicked */
        case SDL_QUIT:
          gameover = 1;
          break;

        /* handle the keyboard */
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
		    case SDLK_LEFT:
              
	         
              pic_count = ((pic_count == 0) ? picture_list.size() - 1 : pic_count - 1);


              glColor3ubv(white);
			  draw_bitmap( picture_list[pic_count] , 400,100);
               SDL_GL_SwapBuffers();
			   
			 

			  break;
		    case SDLK_RIGHT:

	          pic_count = ((pic_count == picture_list.size() - 1) ? 0 : pic_count + 1);
 

              glColor3ubv(white);
			  draw_bitmap( picture_list[pic_count] , 400,100);
               SDL_GL_SwapBuffers();
			   

		      
			  

			  break;
            case SDLK_ESCAPE:
            case SDLK_q:
              gameover = 1;
              break;
          }
          break;
      }
    }
  return gameover;
}


void end_game()
{
  SDL_Quit();
}


vector<string> load_file_list_from_file( string filename )
{
  ifstream fin(filename.c_str());
  string line;
  vector<string> temp;

  if( !fin )
  {
     cout << "\nError occured loading picture file\"" << filename << "\".";
	 exit(0);
  }

  while( getline(fin,line) )
  {
    if( line.size() > 1 )
    temp.push_back( line );  
  }

  return temp;
}



vector<card_type> generate_cards( int min, int max )
{
  vector<card_type> temp;
  card_type x;
  int cmin=0,cmax=0;
  if( max > 54 || max <= min ) // 52 + 2 jokers
  {
    cout << "\nBad Max | min to 54 |";
	exit(0);
  }

  if( min < 0 || min >= max )
  {
    cout << "\nBad Min | 0 to max |";
	exit(0);
  }
  
  // 4 suits 1 to 4
  // 14 faces 1 to 14
  

  for( int face = 1; face <= 14; ++face )
  {
    for( int suit = 1; suit <= 4; ++suit )
	{
      if( cmin == min )
	  {
        temp.push_back( x.create_card( suit,face) );
	  }
	  else
	  {
        ++cmin;
	  }

	  if( cmax == max )
	  {
        return temp;
	  }
	  else
	  {
        ++cmax;
	  }
	}
  }
  return temp; 
}










