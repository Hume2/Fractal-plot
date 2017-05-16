#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <stdio.h>
#include <vector>

#include "../math/fractal.h"
#include "../math/point.h"

#include "../plot/colour.h"

class LispLoader;
class Matrix3D;

class Model
{
  protected:
    friend class ModelManager;

    static double r(const double base, const double modifier);

    class Transform
    {
      public:
        enum Type {MATRIX = 1, TRANSLATE = 2, ROTATE = 3, SHEAR = 4, SCALE = 5};

        Transform(Type type_);
        ~Transform();

        std::vector<float> data;
        std::vector<float> modif;
        Type type;

        Matrix3D get_matrix() const;
        int get_count() const;

        void save(FILE* f);
    };

    class Branch
    {
      public:
        Branch();
        ~Branch();

        std::vector<Transform> transforms;
        Point3D pos, pos_m;
        Colour c, c_m;
        float chance, chance_m;

        const Fractal3D::Branch use_prototype() const;

        void load(FILE* f);
        void save(FILE* f);
        void load_from_lisp(LispLoader& lisp);
        void load_transform_from_lisp(LispLoader& lisp);
    };

  public:
    Model();
    ~Model();

    int maxiter, offscreen_factor;
    std::vector<Branch> branches;

    void load(FILE* f);
    void save(FILE* f);

    Fractal3D use_prototype() const;
};

#endif // MODEL_H
