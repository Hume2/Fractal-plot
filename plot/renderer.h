#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

#include "../math/matrix.h"
#include "../math/point.h"

class Colour;

class Renderer
{
  public:
    Renderer();
    ~Renderer();

    static Renderer* current();

    static Point3D relative_pos;

    void update_window();

    //Returns false when not drawn
    bool put_pixel(int x, int y, const Colour c);
    bool put_pixel(Point3D p, const Colour c);

    void fill_rect(int x1, int y1, int x2, int y2, const Colour c);

    void set_offset(int x, int y);
    void set_transform_matrix(const Matrix3D matrix);

    Point2D get_offset() const;
    const Matrix3D get_transform_matrix() const;

    SDL_Window* get_window() const {
      return window;
    }

  private:
    static Renderer* s_current;
    static Point2D center;
    static float perspective_factor;

    float* height_map;
    int* time_map;

    SDL_Window* window;
    SDL_Surface* screen_surface;
    Uint32* pixels;

    int offset_x, offset_y;
    Matrix3D transform_matrix;
};

#endif // RENDERER_H
