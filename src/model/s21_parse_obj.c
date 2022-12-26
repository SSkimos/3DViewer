#include "s21_parse_obj.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define VERTICE 1
#define FACET 2 

int CountObj(const char* file_path, data_t* data) {
  FILE* obj = OpenFile(file_path);
  size_t max_size = 128;
  char* line = calloc(max_size, sizeof(*line));;
  char* fmt_vert = "v %Lf %Lf %Lf";
  char* fmt_facet = calloc(64, sizeof(*fmt_facet));
  long double* facet_row = calloc(64, sizeof(*facet_row));
  int f_analysis = 0;
  long double tmp1 = 0, tmp2 = 0, tmp3 = 0;
  while ((getline(&line, &max_size, obj) != -1) && (!feof(obj))) {
    if (FormatCheck(line) == VERTICE) {
      data->vertices_count += sscanf(line, fmt_vert, &tmp1, &tmp2, &tmp3);
    } else if (FormatCheck(line) == FACET) {
      if (!f_analysis) {
        data->polygons->v_in_facets = FacetsAnalyzer(line);
        f_analysis = 1;
      }  
      ArrayFacetFactory(line, facet_row);
    }
  }
  free(line);
  free(fmt_facet);
  free(facet_row);
  fclose(obj);
  return 0;
}

int ParseObj(const char* file_path) {
  FILE* obj = OpenFile(file_path);
  size_t max_size = 128;
  char* line = calloc(max_size, sizeof(*line));;
  char* fmt_vert = "v %Lf %Lf %Lf";
  char* fmt_facet = calloc(64, sizeof(*fmt_facet));
  char* num_pointer = NULL;
  long double* facet_row = calloc(64, sizeof(*facet_row));
  int d = 0;
  int f_analysis = 0;
  long double tmp1 = 0, tmp2 = 0, tmp3 = 0;
  while ((getline(&line, &max_size, obj) != -1) && (!feof(obj))) {
    if (FormatCheck(line) == 1) {
      sscanf(line, fmt_vert, &tmp1, &tmp2, &tmp3);
    } else if (FormatCheck(line) == 2) {
      if (!f_analysis) {
        d += FacetsAnalyzer(line);
        f_analysis = 1;
      }  
      ArrayFacetFactory(line, facet_row);
    }
  }
  for (int i = 0; i < d-1; i++) printf("%Lf ", facet_row[i]);
  free(line);
  free(fmt_facet);
  free(facet_row);
  fclose(obj);
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

int ArrayFacetFactory(const char* line, long double* facet_row) {
  char* number_char = (char*) line;
  char *num_pointer = strtok(number_char, " ");
  int i = 0;
  int ret = 0;
  while (num_pointer != NULL) {
    if (*num_pointer != 'f') 
      facet_row[i++] = strtold(num_pointer, NULL);
    num_pointer = strtok(NULL, " ");
    if (i > 512) {
      ret = 1;
      break;
    } else {
      ret = i;
    }
  }
  return ret;
}
