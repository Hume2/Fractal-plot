#include <assert.h>
#include <iostream>
#include <stdio.h>

#include "renderer.h"

#include "colour.h"
#include "../main.h"

Renderer* Renderer::s_current = NULL;
Point2D Renderer::center = Point2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
float Renderer::perspective_factor = 400;

Renderer::Renderer() :
  window(),
  screen_surface(),
  pixels(),
  offset_x(0),
  offset_y(0)
{
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    assert(0);
  }

  window = SDL_CreateWindow( "FG", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
  //SDL_FillRect( screen_surface, NULL, SDL_MapRGB( screen_surface->format, 0xFF, 0xFF, 0xFF ) );
}

bool Renderer::put_pixel(int x, int y, const Colour c) {
  x += offset_x;
  y += offset_y;
  if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT) {
    return false;
  }

  pixels[y * SCREEN_WIDTH + x] = SDL_MapRGB( screen_surface->format, c.r, c.g, c.b );
  return true;
}

bool Renderer::put_pixel(const Point3D p, const Colour c) {
  if (p.z <= 0) {
    return false;
  } else {
    float perspective = perspective_factor / p.z;
    Point2D projection(p * perspective);
    projection += center;

    if (projection.x < 0 || projection.y < 0 ||
        projection.x >= SCREEN_WIDTH || projection.y >= SCREEN_HEIGHT) {
      return false;
    }
    pixels[int(projection.y) * SCREEN_WIDTH + int(projection.x)] =
        SDL_MapRGB( screen_surface->format, c.r, c.g, c.b );
    return true;
  }
}

void Renderer::fill_rect(int x1, int y1, int x2, int y2, const Colour c) {
  SDL_Rect dsrect;
  dsrect.x = x1 + offset_x;
  dsrect.y = y1 + offset_y;
  dsrect.w = x2 - x1 + 1;
  dsrect.h = y2 - y1 + 1;
  SDL_FillRect(screen_surface, &dsrect, SDL_MapRGB( screen_surface->format, c.r, c.g, c.b ));
}

void Renderer::set_offset(int x, int y) {
  offset_x = x;
  offset_y = y;
}

Point2D Renderer::get_offset() const {
  return Point2D(offset_x, offset_y);
}
