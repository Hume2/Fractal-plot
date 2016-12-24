#ifndef LISPLOADER_H
#define LISPLOADER_H

#include <stdio.h>
#include <string>
#include <vector>

class LispLoader
{
  public:
    LispLoader(std::string filename);
    ~LispLoader();

    std::string get_key();
    bool is_end();

    bool get_num(float* val);
    bool get_bool(bool* val);
    bool get_string(std::string* val);
    bool get_array(std::vector<float>* val);

    bool go_down();
    void go_up();

  private:
    FILE* f;
    char c;

    void skip_whitespace();
    float load_number();

    inline void go_ahead() {
      c = fgetc(f);
    }
};

#endif // LISPLOADER_H
