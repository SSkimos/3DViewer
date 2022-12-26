#include "s21_parse_obj.h"

int s21_parse_obj(const char* file_path) {
  FILE* obj = s21_open_file(file_path);
  size_t max_size = 128;
  char* line = calloc(max_size, sizeof(*line));;
  int i = 0;
  while ((getline(&line, &max_size, obj) != -1) && (!feof(obj))) {
    printf("%s", line);
  }
  free(line);
  fclose(obj);
  return 0;
}

FILE* s21_open_file(const char* filename) {
  FILE* fp = fopen(filename, "r");
  if (!fp) {
    perror("File doesn't exist.");
    exit(1);
  }
  return fp;
}
