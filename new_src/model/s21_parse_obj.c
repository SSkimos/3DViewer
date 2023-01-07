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


data_t* ParseCountObj(const char* file_path) {
  data_t* data = calloc(1, sizeof(*data));
  if (data) {
    CountObj(file_path, data);
    ParseObj(file_path, &data);
    // DebugObj(file_path, data);
    // printf("%zu\n", sizeof(*data));
    // FREE DATA !!!
    // USE FGETS
  }
  return data;
}


int CountObj(const char* file_path, data_t* data) {
  FILE* obj = OpenFile(file_path);

  size_t max_size = 128;
  char* line = calloc(max_size, sizeof(*line));;

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
  fclose(obj);
  return 0;
}


int ParseObj(const char* file_path, data_t** data) {
  FILE* obj = OpenFile(file_path);
  size_t max_size = 128;
  char* line = calloc(max_size, sizeof(*line));;
  char* num_pointer = NULL;
  int d = 0;

  int i = 0;
  int j = 0;

  s21_create_matrix(((*data)->vertices_count)/3, 3, &((*data)->matrix_3d));

  (*data)->polygons = calloc((*data)->facets_count, sizeof(*(*data)->polygons));
  while ((getline(&line, &max_size, obj) != -1) && (!feof(obj))) {
    if (FormatCheck(line) == VERTICE) {
      sscanf(line, "v %Lf %Lf %Lf", MATRIX[i][0], MATRIX[i][1], MATRIX[i][2]);
      i++;
    } else if (FormatCheck(line) == FACET) {
      POLYGON[j].v_in_facets = FacetsAnalyzer(line);
      d += POLYGON[j].v_in_facets;
      POLYGON[j].vertexes = calloc(POLYGON[j].v_in_facets, sizeof(*POLYGON[j].vertexes));
      ArrayFacetFactory(line, POLYGON[j].vertexes, &(*data)->matrix_3d);
      j++;
    }
  }
  double* v_array = calloc(d * 7, sizeof(*v_array));
  int size = 0;
  int start = 0;
  for (int i = 0; i < (*data)->facets_count; i++) {
    for (int j = 0; j < POLYGON[i].v_in_facets; j++) {
      int ind = POLYGON[i].vertexes[j];
      v_array[size++] = *MATRIX[ind][0];
      v_array[size++] = *MATRIX[ind][1];
      v_array[size++] = *MATRIX[ind][2];
      if (start) v_array[size++] = *MATRIX[ind][0];
      if (start) v_array[size++] = *MATRIX[ind][1];
      if (start) v_array[size++] = *MATRIX[ind][2];
      start = 1;
      // if (v_array) v_array = realloc(v_array, size * sizeof(*v_array));
    }
  }
  // for (int i = 2; i < size; i+=3) {
  //   printf("ind = %f %f %f\n", v_array[i-2], v_array[i-1], v_array[i]);
  // }
  long double *mat_1d = calloc((*data)->vertices_count + 1, sizeof(*mat_1d));
  unsigned int t = 0;
  for (int i = 0; i < (*data)->matrix_3d.rows; i++) {
    for (int j = 0; j < (*data)->matrix_3d.columns; j++) {
      mat_1d[t++] = (*data)->matrix_3d.matrix[i][j];
    }
  }
  // for (int i = 2; i < t; i+=3) {
  //   printf("ver = %Lf %Lf %Lf\n", mat_1d[i-2], mat_1d[i-1], mat_1d[i]);
  // }
  free(line);
  (*data)->v_array = v_array;
  (*data)->mat_1d = mat_1d;
  (*data)->size_v = t;
  (*data)->size = size;
  // free(v_array);
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
  if ((line[0] == 'v') && (line[1] == ' ' || isdigit(line[1]))) ret = 1; 
  if (line[0] == 'f') ret = 2;
  return ret;
}

int FacetsAnalyzer(const char* line) {
  int ret = 0;
  char* number_char = calloc(strlen(line), sizeof(*number_char));
  if (number_char) {
    strcpy(number_char, line);
    int num_count = 0;
    char *num_pointer = strtok(number_char, " ");
    int i = 0;
    while (num_pointer != NULL) {
      if (isdigit(*num_pointer)) {
        i++; 
      }
      num_pointer = strtok(NULL, " ");
    }
    ret = i;
  } else {
    ret = 1;
  }
  free(number_char);
  return ret;
}


int ArrayFacetFactory(const char* line, long double* facet_row, matrix_t* s) {
  char* number_char = (char*) line;
  char *num_pointer = strtok(number_char, " ");
  int i = 0;
  int ret = 0;
  while (num_pointer != NULL) {
    if (isdigit(*num_pointer)) {
      int ind = strtold(num_pointer, NULL) - 1;
      facet_row[i++] = ind;
    }
    num_pointer = strtok(NULL, " ");
  }
  return ret;
}

int DebugObj(const char* file_path, data_t *data) {
  printf("%s = FILE\n", file_path);
  printf("%d = vertices_count\n", data->vertices_count);
  printf("%d = facets_count \n", data->facets_count);
  printf("VERTICES_MATRIX \n");
  for (int i = 0; i < data->matrix_3d.rows; i++) {
    printf("%d: ", i+1);
    for (int j = 0; j < data->matrix_3d.columns; j++) {
      printf(" %1.2Lf", data->matrix_3d.matrix[i][j]);
    }
    printf("\n");
  }
  printf("FACET_DATA \n");
  for (int i = 0; i < data->facets_count; i++) {
    printf("%d: ", i+1);
    for (int j = 0; j < data->polygons[i].v_in_facets; j++) {
      printf(" %1.2Lf", data->polygons[i].vertexes[j]);
    }
    printf("\n");
  }
  return 0;
}

int DataAllocate(data_t** data) {
  return 0;
}

long double* RemakeMatrix(data_t* data) {
  long double *res = NULL;
  int f = 0;
  if (data) {
    res = calloc(data->matrix_3d.columns*data->matrix_3d.rows, sizeof(*res));
    for (int i = 0; i < data->matrix_3d.rows; i++) {
      for (int j = 0; j < data->matrix_3d.columns; j++) {
        res[f++] = data->matrix_3d.matrix[i][j];
      }
    }
  }
  return res;
}

long double* RemakeFacets(data_t* data, int*s) {
  long double *res = NULL;
  int f = 0;
  if (data) {
    long double old = data->polygons[0].vertexes[0];
    res = calloc(1024, sizeof(*res));
    res[f++] = old;
    for (int i = 0; i < data->facets_count; i++) {
      // res = realloc(res, (f+data->polygons[i].v_in_facets) * sizeof(long double));
      for (int j = 1; j < data->polygons[i].v_in_facets; j++) {
        res[f++] = (data->polygons->vertexes[j]);
        res[f++] = (data->polygons->vertexes[j]);
      }
    }
  }
  s = calloc(1, sizeof(*s));
  s[0] = f;
  return res;
}
