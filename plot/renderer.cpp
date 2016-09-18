#include <assert.h>
#include <iostream>
#include <stdio.h>

#include "renderer.h"

#include "colour.h"
#include "../main.h"

Renderer* Renderer::s_current = NULL;

Renderer::Renderer() :
  window(),
  screen_surface(),
  pixels()
{
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    assert(0);
  }

  window = SDL_CreateWindow( "FG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
  if( window == NULL ) {
    std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    assert(0);
  }

  screen_surface = SDL_GetWindowSurface( window );
  pixels = (Uint32 *)screen_surface->pixels;

  SDL_FillRect( screen_surface, NULL, SDL_MapRGB( screen_surface->format, 0xFF, 0xFF, 0xFF ) );

  s_current = this;
}

Renderer::~Renderer() {
  SDL_DestroyWindow( window );
  SDL_Quit();
}

Renderer* Renderer::current() {
  return s_current;
}

void Renderer::update_window() {
  SDL_UpdateWindowSurface(window);
  SDL_FillRect( screen_surface, NULL, SDL_MapRGB( screen_surface->format, 0xFF, 0xFF, 0xFF ) );
}

void Renderer::put_pixel(int x, int y, Colour c) {
  if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) {
    return;
  }

  pixels[y * SCREEN_WIDTH + x] = SDL_MapRGB( screen_surface->format, c.r, c.g, c.b );
}
