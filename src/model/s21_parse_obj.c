#include "s21_parse_obj.h"
#include "matrix_t/s21_matrix.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define VERTICE 1
#define FACET 2 
#define MATRIX &(*data)->matrix_3d.matrix
#define POLYGON (*data)->polygons


int ParseCountObj(const char* file_path) {
  data_t* data = calloc(1, sizeof(*data));
  CountObj(file_path, data);
  ParseObj(file_path, &data);
  printf("FILE = %s\n", file_path);
  DebugObj(data);
  return 0;
}

int CountObj(const char* file_path, data_t* data) {
  FILE* obj = OpenFile(file_path);

  size_t max_size = 128;
  char* line = calloc(max_size, sizeof(*line));;

  long double* facet_row = calloc(64, sizeof(*facet_row));
  int f_analysis = 0;
  data->vertices_count = 0;
  data->facets_count = 0;
  while ((getline(&line, &max_size, obj) != -1) && (!feof(obj))) {
    if (FormatCheck(line) == VERTICE) {
      long double tmp1 = 0, tmp2 = 0, tmp3 = 0;
      data->vertices_count += sscanf(line, "v %Lf %Lf %Lf", &tmp1, &tmp2, &tmp3);
    } else if (FormatCheck(line) == FACET) {
      (data->facets_count)++;
    }
  }
  free(line);
  free(facet_row);
  fclose(obj);
  return 0;
}


int ParseObj(const char* file_path, data_t** data) {
  FILE* obj = OpenFile(file_path);
  size_t max_size = 128;
  char* line = calloc(max_size, sizeof(*line));;
  char* num_pointer = NULL;
  long double* facet_row = calloc(64, sizeof(*facet_row));
  int d = 0;

  int i = 0;
  int j = 0;

  s21_create_matrix(((*data)->vertices_count)/3+1, 3, &((*data)->matrix_3d));
  (*data)->polygons = calloc(1, sizeof(*(*data)->polygons));
  while ((getline(&line, &max_size, obj) != -1) && (!feof(obj))) {
    if (FormatCheck(line) == 1) {
      sscanf(line, "v %Lf %Lf %Lf", MATRIX[i+1][0], MATRIX[i+1][1], MATRIX[i+1][2]);
      i++;
    } else if (FormatCheck(line) == 2) {
      POLYGON[j].v_in_facets = FacetsAnalyzer(line);
      POLYGON[j].vertexes = calloc(POLYGON[j].v_in_facets, sizeof(*POLYGON[j].vertexes));
      ArrayFacetFactory(line, POLYGON[j].vertexes);
    }
  }
  free(line);
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
  char* number_char = (char*) line;
  int num_count = 0;
  char *num_pointer = strtok(number_char, " ");
  int i = 0;
  int ret = 0;
  while (num_pointer != NULL) {
    if (*num_pointer != 'f') 
      i++; 
    num_pointer = strtok(NULL, " ");
  }
  ret = i;
  return ret;
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

int DebugObj(data_t *data) {
  printf("%d = vertices_count\n", data->vertices_count);
  printf("%d = facets_count \n", data->facets_count);
  for (int i = 0; i < data->matrix_3d.rows; i++) {
    for (int j = 0; j < data->matrix_3d.columns; j++) {
      printf(" %Lf", data->matrix_3d.matrix[i][j]);
    }
    printf("\n");
  }
  for (int i = 0; i < data->vertices_count; i++) {
    for (int j = 0; j < data->polygons[i].v_in_facets; j++) {
      printf(" %Lf", data->polygons[i].vertexes[j]);
    }
    printf("\n");
  }
  return 0;
}
int DataAllocate(data_t** data) {

  return 0;
}
