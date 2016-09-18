#include <stdio.h>
#include <iostream>

#include <SDL2/SDL.h>

#include "main.h"

#include "math/point.h"
#include "math/matrix.h"

int main(int argc, char *argv[])
{
  SDL_Window* window = NULL;
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

  //SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
  //SDL_Texture * texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
  Uint32* pixels = (Uint32 *)screen_surface->pixels;//new Uint32[SCREEN_WIDTH * SCREEN_WIDTH];

  SDL_FillRect( screen_surface, NULL, SDL_MapRGB( screen_surface->format, 0xFF, 0xFF, 0xFF ) );

  //pixels[100 * SCREEN_WIDTH + 100] = 0;

  bool quit = false;
  while (!quit)
  {
    SDL_UpdateWindowSurface(window);
//    SDL_UpdateTexture(texture, NULL, pixels, SCREEN_WIDTH * sizeof(Uint32));
    SDL_Event event;
    bool leftMouseButtonDown;
    SDL_PollEvent(&event);
    //SDL_WaitEvent(&event);

    switch (event.type)
    {
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT)
            leftMouseButtonDown = false;
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
            leftMouseButtonDown = true;
    case SDL_MOUSEMOTION:
        if (leftMouseButtonDown)
        {
            int mouseX = event.motion.x;
            int mouseY = event.motion.y;
            pixels[mouseY * SCREEN_WIDTH + mouseX] = 0;
        }
        break;
    case SDL_QUIT:
        quit = true;
        break;
    }

//    SDL_RenderClear(renderer);
//    SDL_RenderCopy(renderer, texture, NULL, NULL);
//    SDL_RenderPresent(renderer);
  }
  //delete[] pixels;
  //SDL_DestroyTexture(texture);
  //SDL_DestroyRenderer(renderer);

  SDL_DestroyWindow( window );
  SDL_Quit();

  Point3D point(5, 2, 3);
  Matrix3D matrix(Matrix3D::ROTATE, 1, 1, 1);
  matrix.add_transform(Matrix3D(Matrix3D::TRANSLATE, 3, 3, 3));
  point = matrix.apply_transform(point);

  std::cout << point.to_string() << std::endl;
  return 0;
}

