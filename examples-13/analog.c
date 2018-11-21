#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include "analog.h"

/*-----------------------------------------------------------------------------------------------*/
static void        drawDial                                ( SDL_Renderer    * dst,
                                                             int               xc,
                                                             int               yc,
                                                             int               r )
{
  int i;
  
  for ( i = 0; i < 60; i ++ )
  {
    int x1 = xc + r * cos ( i * M_PI / 30 );
    int y1 = yc + r * sin ( i * M_PI / 30 );
    int rr = i % 5 == 0 ? 0.85 * r : 0.92 * r;
    int x2 = xc + rr * cos ( i * M_PI / 30 );
    int y2 = yc + rr * sin ( i * M_PI / 30 );
    
    SDL_RenderDrawLine ( dst, x1, y1, x2, y2 );
  }
}  
/*-----------------------------------------------------------------------------------------------*/
static void        drawHand                                ( SDL_Renderer    * dst,
                                                             int               xc,
                                                             int               yc,
                                                             int               r,
                                                             int               v )
{
  int x = xc + r * cos ( ( 15 - v ) * M_PI / 30 );
  int y = yc - r * sin ( ( 15 - v ) * M_PI / 30 );
  
  SDL_RenderDrawLine ( dst, xc, yc, x, y );
}
/*-----------------------------------------------------------------------------------------------*/
void               drawAnalogClock                         ( SDL_Renderer    * dst,
                                                             int               xc,
                                                             int               yc,
                                                             int               r )
{
  struct timeval tv;
  struct tm t;
  
  gettimeofday ( &tv, NULL );
  t = *localtime ( &tv . tv_sec );
  
  SDL_SetRenderDrawColor ( dst, 0, 0, 0, 255 );
  drawDial ( dst, xc, yc, r );
  //drawDial ( dst, xc, yc + r / 2, r / 3 );
  
  drawHand ( dst, xc, yc, 0.8 * r, t . tm_min );
  drawHand ( dst, xc, yc, 0.6 * r, ( t . tm_hour % 12 ) * 5 + t . tm_min / 12 );

  SDL_SetRenderDrawColor ( dst, 255, 0, 0, 255 );
  drawHand ( dst, xc, yc, 0.9 * r, t . tm_sec );
  
  SDL_SetRenderDrawColor ( dst, 0, 0, 0, 255 );
  //drawHand ( dst, xc, yc + r / 2, 0.9 * r / 3, 60.0 * tv . tv_usec / 1000000 );
}  
/*-----------------------------------------------------------------------------------------------*/
