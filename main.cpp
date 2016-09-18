#include <stdio.h>
#include <iostream>

#include <SDL2/SDL.h>

#include "main.h"

#include "math/point.h"
#include "math/matrix.h"

#include "plot/colour.h"
#include "plot/renderer.h"

int main(int argc, char *argv[])
{
  /*SDL_Window* window = NULL;
  SDL_Surface* screen_surface = NULL;
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    return 1;
  }

  window = SDL_CreateWindow( "FG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  if( window == NULL ) {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    return 1;
  }

  screen_surface = SDL_GetWindowSurface( window );

  Uint32* pixels = (Uint32 *)screen_surface->pixels;//new Uint32[SCREEN_WIDTH * SCREEN_WIDTH];

  SDL_FillRect( screen_surface, NULL, SDL_MapRGB( screen_surface->format, 0xFF, 0xFF, 0xFF ) );

  //pixels[100 * SCREEN_WIDTH + 100] = 0;
*/
  Renderer renderer;

  bool quit = false;
  while (!quit)
  {
    renderer.update_window();
    //SDL_UpdateWindowSurface(window);
    SDL_Event event;
    bool leftMouseButtonDown;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT) {
         leftMouseButtonDown = false;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
            leftMouseButtonDown = true;
    case SDL_MOUSEMOTION:
        if (leftMouseButtonDown)
        {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;
            renderer.put_pixel(mouseX, mouseY, Colour(0xFF, 0x00, 0x00));
            //pixels[mouseY * SCREEN_WIDTH + mouseX] = SDL_MapRGB( screen_surface->format, 0xFF, 0x00, 0x00 );
        }
        break;
    case SDL_QUIT:
        quit = true;
        break;
    }
  }

  /*SDL_DestroyWindow( window );
  SDL_Quit();*/

  return 0;
}

