#include <assert.h>
#include <iostream>

#include "model_manager.h"
#include "lisp_loader.h"

#include "../math/fractal.h"

ModelManager::ModelManager() :
  models()
{

}

ModelManager::~ModelManager() {

}

void ModelManager::init_from_lisp() {
  LispLoader lisp("models-lisp.txt");
  std::string key = lisp.get_key();
  if (key != "fractal-set") {
    std::cout << "Error: Models-lisp.txt is not a fractal-set file." << std::endl;
    std::cout << key << std::endl;
    assert(false);
  }

  while (!lisp.is_end()) {
    key = lisp.get_key();

    if (key == "model") {
      load_model_lisp(lisp);
    } else {
      lisp.go_up();
    }
  }

  std::cout << models.size() << " models loaded" << std::endl;
}

void ModelManager::load_model_lisp(LispLoader& lisp) {
  std::string key, id;
  float num;
  Model model;

  while (!lisp.is_end()) {
    key = lisp.get_key();

    if (key == "id") {
      lisp.get_string( &id );
    } else if (key == "maxiter") {
      lisp.get_num( &num );
      model.maxiter = num;
    } else if (key == "offscreen_factor") {
      lisp.get_num( &num );
      model.offscreen_factor = num;
    } else if (key == "branch") {
      Model::Branch branch;
      branch.load_from_lisp(lisp);
      model.branches.push_back(branch);
    } else {
      lisp.go_up();
    }
  }
  lisp.go_up();

  models[id] = model;
}

const Model& ModelManager::get_model(std::string id) const {
  auto it = models.find(id);
  if (it != models.end()) {
    return it->second;
  } else {
    return models.begin()->second;
  }
}

Fractal3D ModelManager::fabricate(std::string id) const {
  auto it = models.find(id);
  if (it != models.end()) {
    return it->second.use_prototype();
  } else {
    return models.begin()->second.use_prototype();
  }
}
