#include <SDL2/SDL.h>
#include "analog.h"
#include "digital.h"
#include "geeky.h"

#define TYPE_ANALOG  0
#define TYPE_DIGITAL 1
#define TYPE_GEEKY   2

int                main                                    ( int               argc, 
                                                             char            * argv [] ) 
{
  SDL_Window   * win = NULL;
  SDL_Renderer * renderer = NULL;
  int            clockType = TYPE_ANALOG;
  
  SDL_Init ( SDL_INIT_VIDEO );

  win = SDL_CreateWindow ( "PA1 clock", 20, 20, 250, 250, 0 );
  renderer = SDL_CreateRenderer ( win, -1, SDL_RENDERER_ACCELERATED );

  while (1) 
  {
    SDL_Event e;
    if ( SDL_WaitEventTimeout ( &e, 20 ) )
    {
      if ( e . type == SDL_QUIT ) 
        break;
      if ( e.type == SDL_KEYUP )
      {
        switch ( e . key . keysym . sym )
        {
          case SDLK_a:
            clockType = TYPE_ANALOG;
            break;
          case SDLK_g:
            clockType = TYPE_GEEKY;
            break;
          case SDLK_d:
            clockType = TYPE_DIGITAL;
            break;
        }
      }
    }
    SDL_SetRenderDrawColor ( renderer, 255, 255, 255, 255 );
    SDL_RenderClear(renderer);
    switch ( clockType )
    {
      case TYPE_ANALOG:
        drawAnalogClock ( renderer, 125, 125, 110 );
        break;
      case TYPE_DIGITAL:
        drawDigitalClock ( renderer, 125, 110, 30 );
        break;
      case TYPE_GEEKY:
        drawGeekyClock ( renderer, 20, 20, 20 );
        break;
    }
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
