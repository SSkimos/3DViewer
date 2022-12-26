#include "s21_parse_obj.h"
#include <stdio.h>

int ParseObj(const char* file_path) {
  FILE* obj = OpenFile(file_path);
  size_t max_size = 128;
  char* line = calloc(max_size, sizeof(*line));;
  int d = 0;
  int f_analysis = 0;
  long double tmp1 = 0, tmp2 = 0, tmp3 = 0;
  while ((getline(&line, &max_size, obj) != -1) && (!feof(obj))) {
    if (FormatCheck(line) == 1) {
      printf("%s", line);
      sscanf(line, "v %Lf %Lf %Lf", &tmp1, &tmp2, &tmp3);
      printf("%Lf %Lf %Lf\n", tmp1, tmp2, tmp3);
    } else if (FormatCheck(line) == 2) {
      if (!f_analysis) {
        d += FacetsAnalyzer(line);
        f_analysis = 1;
      }
    }
  }
  free(line);
  fclose(obj);
  printf("\n\n%d\n\n", d);
  return 0;
}

FILE* OpenFile(const char* filename) {
  FILE* fp = fopen(filename, "r");
  if (!fp) {
    perror("File doesn't exist.");
    exit(1);
  }
  return fp;
}

int FormatCheck(const char* line) {
  int ret = 0;
  if (line[0] == 'v') ret = 1; 
  if (line[0] == 'f') ret = 2;
  return ret;
}

int FacetsAnalyzer(const char* line) {
  int corrupt_count = 0;
  int num_count = 0;
  int ret = 0;
  for (char c = *line; c != '\0'; c = *++line) {
    if (c == 'f') corrupt_count++;
    if (corrupt_count > 1) {
      ret = -1;
      break;
    }
    if (c == ' ') num_count ++;
    if (c == '\n') break;
  }
  ret = num_count;
  return ret;
}
