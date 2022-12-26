#include "s21_parse_obj.h"

int main() {
  const char*filename = "../obj/box.obj";
  ParseCountObj(filename);
  const char*filenam = "../obj/skyscraper.obj";
  ParseCountObj(filenam);
  return 0;
}
