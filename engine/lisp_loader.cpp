#include <assert.h>
#include <sstream>
#include <iostream>

#include "lisp_loader.h"

LispLoader::LispLoader(std::string filename) :
  f(fopen(filename.c_str(), "r")),
  c()
{
  if (!f) {
    std::cout << "Error: unable to open file " << filename << std::endl;
    assert(false);
  }
  c = fgetc(f);
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
  bool b = true;
  while (b) {
    go_down();
    b = is_end();
    if (b) {
      go_up();
    }
  }
  std::string s = "";
  while (c > ' ' && c != ')') {
    s += c;
    go_ahead();
  }
  //std::cout << "Loaded key: " << s << std::endl;

  return s;
}

bool LispLoader::is_end() {
  skip_whitespace();
  return c == ')';
}

bool LispLoader::load_number(float& val) {
  val = 0;
  float xp = 1;
  bool sgn = false;

  if (c == '-') {
    sgn = true;
    go_ahead();
  } else if (c == '+') {
    go_ahead();
  }

  if (c < '0' || c > '9') {
    return false;
  }

  while (c >= '0' && c <= '9') {
    val *= 10;
    val += c - '0';
    go_ahead();
  }
  if (c == '.') {
    go_ahead();
    while (c >= '0' && c <= '9') {
      xp /= 10;
      val += float(c - '0') * xp;
      go_ahead();
    }
  }

  if (sgn) {
    val = -val;
  }

  return true;
}

bool LispLoader::get_num(float* val) {
  if (is_end()) {
    go_up();
    return false;
  }

  if (!load_number(*val)) {
    return false;
  }

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
  float num = 0;

  skip_whitespace();

  while (load_number(num)) {
    val->push_back(num);
    skip_whitespace();
  }

  go_up();
  return true;
}
