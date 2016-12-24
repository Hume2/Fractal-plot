#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <stdio.h>
#include <vector>

#include "../math/fractal.h"
#include "../math/point.h"

#include "../plot/colour.h"

class Matrix3D;

class Model
{
  protected:
    static double r(const double base, const double modifier);

    class Transform
    {
      public:
        enum Type {MATRIX, TRANSLATE, ROTATE, SHEAR, SCALE};

        Transform(Type type_);
        ~Transform();

        float* data;
        float* modif;
        Type type;

        Matrix3D get_matrix() const;
        int get_count() const;
    };

    class Branch
    {
      public:
        Branch();
        ~Branch();

        std::vector<Transform> transforms;
        Point3D pos, pos_m;
        Colour c, c_m;
        double chance, chance_m;

        const Fractal3D::Branch use_prototype() const;
    };

  public:
    Model();
    ~Model();

    int maxiter, offscreen_factor;
    std::vector<Branch> branches;

    Fractal3D use_prototype() const;
};

#endif // MODEL_H
