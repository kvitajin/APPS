#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include "geeky.h"


/*-----------------------------------------------------------------------------------------------*/
static void        binRect                                 ( SDL_Renderer    * dst,
                                                             int               val,
                                                             int               cnt,
                                                             int               x,
                                                             int               y,
                                                             int               w )
{
  int i;
  SDL_Rect r;
  
  r . y = y;
  r . h = w;
  r . w = w;
  for ( i = cnt - 1; i >= 0; i -- )
  {
    if ( val & 1 )
      SDL_SetRenderDrawColor ( dst,   0,   0,   0, 255 );
    else
      SDL_SetRenderDrawColor ( dst, 224, 224, 224, 255 );
    r . x = x + i * 1.2 * w;
    SDL_RenderFillRect ( dst, &r );
    val >>= 1;
  }
}  
/*-----------------------------------------------------------------------------------------------*/
void               drawGeekyClock                          ( SDL_Renderer    * dst,
                                                             int               x0,
                                                             int               y0,
                                                             int               w )
{
  struct timeval tv;
  struct tm t;
  
  gettimeofday ( &tv, NULL );
  t = *localtime ( &tv . tv_sec );

  binRect ( dst, t . tm_hour, 5, x0, y0, w );
  binRect ( dst, t . tm_min,  6, x0, y0 + 1.2 * w, w );
  binRect ( dst, t . tm_sec,  6, x0, y0 + 2.4 * w, w );
  binRect ( dst, (tv . tv_usec / 1000 ) % 1000, 10, x0, y0 + 3.6 * w, w * 0.8 );
}  
/*-----------------------------------------------------------------------------------------------*/
