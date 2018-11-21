#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <SDL2/SDL.h>
#include "digital.h"

static const int g_Segments[] = 
{ 
  0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f 
};
/*-----------------------------------------------------------------------------------------------*/
static void        drawSegmentHor                          ( SDL_Renderer    * dst,
                                                             int               x,
                                                             int               y,
                                                             int               w,
                                                             int               on )
{
  int thick = w / 10, i;
  
  if ( on )
    SDL_SetRenderDrawColor ( dst,   0,   0,   0, 255 );
  else
    SDL_SetRenderDrawColor ( dst, 224, 224, 224, 255 );
  
  for ( i = 0; i < thick; i ++ )
  {
    SDL_RenderDrawLine ( dst, x + 1 + i, y + i, x + w - 1 - i, y + i );
    SDL_RenderDrawLine ( dst, x + 1 + i, y - i, x + w - 1 - i, y - i );
  }  
}
/*-----------------------------------------------------------------------------------------------*/
static void        drawSegmentVer                          ( SDL_Renderer    * dst,
                                                             int               x,
                                                             int               y,
                                                             int               h,
                                                             int               on )
{
  int thick = h / 10, i;
  
  if ( on )
    SDL_SetRenderDrawColor ( dst,   0,   0,   0, 255 );
  else
    SDL_SetRenderDrawColor ( dst, 224, 224, 224, 255 );
  
  for ( i = 0; i < thick; i ++ )
  {
    SDL_RenderDrawLine ( dst, x + i, y - 1 - i, x + i, y - h + 1 + i );
    SDL_RenderDrawLine ( dst, x - i, y - 1 - i, x - i, y - h + 1 + i );
  }  
}
/*-----------------------------------------------------------------------------------------------*/
static void        drawDigit                               ( SDL_Renderer    * dst,
                                                             int               digit,
                                                             int               x,
                                                             int               y,
                                                             int               w,
                                                             int               h )
{
  drawSegmentHor ( dst, x,     y - 2 * h, w, g_Segments[digit] & 0x01 );
  drawSegmentHor ( dst, x,     y - h    , w, g_Segments[digit] & 0x40 );
  drawSegmentHor ( dst, x,     y        , w, g_Segments[digit] & 0x08 );
  drawSegmentVer ( dst, x    , y        , h, g_Segments[digit] & 0x10 );
  drawSegmentVer ( dst, x + w, y        , h, g_Segments[digit] & 0x04 );
  drawSegmentVer ( dst, x    , y - h    , h, g_Segments[digit] & 0x20 );
  drawSegmentVer ( dst, x + w, y - h    , h, g_Segments[digit] & 0x02 );
}  
/*-----------------------------------------------------------------------------------------------*/
void               drawDigitalClock                        ( SDL_Renderer    * dst,
                                                             int               xc,
                                                             int               y0,
                                                             int               digitW )
{
  int x = xc - 2.75 * digitW;
  int smallW = 0.8 * digitW;
  int digitH = 2.5 * digitW;
  struct timeval tv;
  struct tm t;
  
  gettimeofday ( &tv, NULL );
  t = *localtime ( &tv . tv_sec );
  
  drawDigit ( dst, t . tm_hour / 10, x,                y0, digitW, digitW );
  drawDigit ( dst, t . tm_hour % 10, x + 1.3 * digitW, y0, digitW, digitW );
  drawDigit ( dst, t . tm_min / 10,  x + 3.2 * digitW, y0, digitW, digitW );
  drawDigit ( dst, t . tm_min % 10,  x + 4.5 * digitW, y0, digitW, digitW );
  
  drawDigit ( dst, t . tm_sec / 10,  x,                                           y0 + 1.3 * digitH, digitW, digitW );
  drawDigit ( dst, t . tm_sec % 10,  x + 1.3 * digitW,                            y0 + 1.3 * digitH, digitW, digitW );
  drawDigit ( dst, (tv . tv_usec / 100000) % 10, x + 2.7 * digitW,                y0 + 1.3 * digitH, smallW, smallW );
  drawDigit ( dst, (tv . tv_usec / 10000) % 10,  x + 2.7 * digitW + 1.3 * smallW, y0 + 1.3 * digitH, smallW, smallW );
  drawDigit ( dst, (tv . tv_usec / 1000) % 10,   x + 2.7 * digitW + 2.6 * smallW, y0 + 1.3 * digitH, smallW, smallW );
}  
/*-----------------------------------------------------------------------------------------------*/
