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
    DebugObj(file_path, data);
    printf("%zu\n", sizeof(*data));
    // FREE DATA !!!
  }
  return data;
}

long double* RemakeMatrix(data_t* data) {
  long double *res = NULL;
  int f = 0;
  if (data) {
    res = calloc(data->matrix_3d.columns*data->matrix_3d.rows, sizeof(*res));
    for (int i = 1; i < data->matrix_3d.rows; i++) {
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

  (*data)->polygons = calloc((*data)->facets_count, sizeof(*(*data)->polygons));
  while ((getline(&line, &max_size, obj) != -1) && (!feof(obj))) {
    if (FormatCheck(line) == 1) {
      sscanf(line, "v %Lf %Lf %Lf", MATRIX[i+1][0], MATRIX[i+1][1], MATRIX[i+1][2]);
      i++;
    } else if (FormatCheck(line) == 2) {
      POLYGON[j].v_in_facets = FacetsAnalyzer(line);
      POLYGON[j].vertexes = calloc(POLYGON[j].v_in_facets, sizeof(*POLYGON[j].vertexes));
      ArrayFacetFactory(line, POLYGON[j].vertexes);
      j++;
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
      if (*num_pointer != 'f') 
        i++; 
      num_pointer = strtok(NULL, " ");
    }
    ret = i;
  } else {
    ret = 1;
  }
  free(number_char);
  return ret;
}


int ArrayFacetFactory(const char* line, long double* facet_row) {
  char* number_char = (char*) line;
  char *num_pointer = strtok(number_char, " ");
  int i = 0;
  int ret = 0;
  while (num_pointer != NULL) {
    if (*num_pointer != 'f') 
      facet_row[i++] = strtold(num_pointer, NULL) - 1;
    num_pointer = strtok(NULL, " ");
  }
  return ret;
}

int DebugObj(const char* file_path, data_t *data) {
  printf("%s = FILE\n", file_path);
  printf("%d = vertices_count\n", data->vertices_count);
  printf("%d = facets_count \n", data->facets_count);
  printf("VERTICES_MATRIX \n");
  // for (int i = 0; i < data->matrix_3d.rows; i++) {
  //   for (int j = 0; j < data->matrix_3d.columns; j++) {
  //     printf(" %Lf", data->matrix_3d.matrix[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("FACET_DATA \n");
  // for (int i = 0; i < data->facets_count; i++) {
  //   for (int j = 0; j < data->polygons[i].v_in_facets; j++) {
  //     printf(" %Lf", data->polygons[i].vertexes[j]);
  //   }
  //   printf("\n");
  // }
  return 0;
}
int DataAllocate(data_t** data) {

  return 0;
}
