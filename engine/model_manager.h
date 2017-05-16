#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include <stdio.h>
#include <map>
#include <string>

#include "model.h"

class LispLoader;
class Fractal3D;

class ModelManager
{
  public:
    ModelManager();
    ~ModelManager();

    void load();
    void save();
    void init_from_lisp();
    static std::string get_model_path();

    const Model& get_model(std::string id) const;
    Fractal3D fabricate(std::string id) const;

  private:
    std::map<std::string, Model> models;

    void load_model_lisp(LispLoader& lisp);
};

#endif // MODELMANAGER_H
