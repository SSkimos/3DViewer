#include "s21_parse_obj.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int ParseObj(const char* file_path) {
  FILE* obj = OpenFile(file_path);
  size_t max_size = 128;
  char* line = calloc(max_size, sizeof(*line));;
  char* fmt_vert = "v %Lf %Lf %Lf";
  char* fmt_facet = calloc(64, sizeof(*fmt_facet));
  char* num_pointer = NULL;
  int d = 0;
  int f_analysis = 0;
  long double tmp1 = 0, tmp2 = 0, tmp3 = 0;
  while ((getline(&line, &max_size, obj) != -1) && (!feof(obj))) {
    if (FormatCheck(line) == 1) {
      printf("%s", line);
      sscanf(line, fmt_vert, &tmp1, &tmp2, &tmp3);
      printf("%Lf %Lf %Lf\n", tmp1, tmp2, tmp3);
    } else if (FormatCheck(line) == 2) {
      if (!f_analysis) {
        d += FacetsAnalyzer(line);
        // FormatFacet(fmt_facet, d);
        f_analysis = 1;
      }  
      num_pointer = strtok(line, " ");
      while (num_pointer != NULL) {
        if (*num_pointer == 'f') {
          num_pointer = strtok(NULL, " ");
          continue;
        } else {
          printf("%Lf \n", strtold(num_pointer, NULL));
          num_pointer = strtok(NULL, " ");
        }
      }

    }
  }
  free(line);
  free(fmt_facet);
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
  int dig_count = 0;
  int space_before = 1;
  int ret = 0;
  for (char c = *line; c != '\0'; c = *++line) {
    if (c == 'f') {
      corrupt_count++;
      if (corrupt_count > 1) {
        ret = -1;
        break;
      }
    } else if (isdigit(c) || (c == '.') || (c==',')) {
      if (space_before) num_count++;
      space_before = 0;
    } else if (c == '\n') {
      if (isdigit(*(line-1))) num_count++;  
      break;
    } else  {
      if (c == ' ') space_before = 1;
    }
  }
  ret = num_count;
  return ret;
}


int FormatFacet(char* line, int facet_count) {
  line[0] = 'f';
  int i = 0;
  while (facet_count > 1) {
    strcat(line, " %d");
    --facet_count;
    i+=3;
  }
  line[i+1] ='\0';
  printf("\n\n%s\n\n", line);
  return 0;
}
