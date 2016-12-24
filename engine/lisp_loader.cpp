#include "lisp_loader.h"

#include <sstream>
#include <iostream>

LispLoader::LispLoader(std::string filename) :
  f(fopen(filename.c_str(), "r")),
  c(fgetc(f))
{

}

LispLoader::~LispLoader() {
  fclose(f);
}

void LispLoader::skip_whitespace() {
  while (c <= ' ') {
    go_ahead();
  }
}

bool LispLoader::go_down() {
  while (c != '(') {
    if (c == ')') {
      return false;
    }
    go_ahead();
  }
  go_ahead();

  return true;
}

void LispLoader::go_up() {
  int b = 1;
  while (b) {
    if (c == ')') {
      b--;
    } else if (c == '(') {
      b++;
    }
    go_ahead();
  }
}

std::string LispLoader::get_key() {
  go_down();
  skip_whitespace();
  std::string s = "";
  while (c > ' ' && c != ')') {
    s += c;
    go_ahead();
  }
  std::cout << "Loaded key: " << s << std::endl;

  return s;
}

bool LispLoader::is_end() {
  skip_whitespace();
  return c == ')';
}

float LispLoader::load_number() {
  float val = 0;
  float xp = 1;
  bool sgn = false;

  if (c == '-') {
    sgn = true;
    go_ahead();
  } else if (c == '+') {
    go_ahead();
  }

  while (c != '.' && c > ' ') {
    val *= 10;
    val += c - '0';
    go_ahead();
  }
  if (c == '.') {
    go_ahead();
    while (c > ' ') {
      xp /= 10;
      val += float(c - '0') * xp;
      go_ahead();
    }
  }

  return val;
}

bool LispLoader::get_num(float* val) {
  if (is_end()) {
    go_up();
    return false;
  }

  *val = load_number();

  go_up();
  return true;
}

bool LispLoader::get_bool(bool *val) {
  if (is_end() || c != '#') {
    go_up();
    return false;
  }
  go_ahead();
  if (c == 't') {
    *val = true;
  } else if (c == 'f') {
    *val = false;
  } else {
    go_up();
    return false;
  }

  go_up();
  return true;
}

bool LispLoader::get_string(std::string* val) {
  if (is_end()) {
    go_up();
    return false;
  }

  if (c != '"') {
    go_up();
    return false;
  }
  go_ahead();

  *val = "";
  while (c != '"') {
    if (c == '\\') {
      go_ahead();
      if (c == 'n') {
        *val += '\n';
        go_ahead();
        continue;
      }
    }
    *val += c;
    go_ahead();
  }

  go_up();
  return true;
}

bool LispLoader::get_array(std::vector<float>* val) {
  val->clear();

  while (!is_end()) {
    val->push_back(load_number());
  }

  go_up();
  return true;
}
