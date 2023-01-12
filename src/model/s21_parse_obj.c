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

  int f_analysis = 0;
  int i = 0;
  (*data)->vertex_array = calloc((*data)->vertices_count + 1, sizeof(double));
  while ((getline(&line, &max_size, obj) != -1) && (!feof(obj))) {
    if (FormatCheck(line) == VERTICE) {
      int a = i, b=i+1, c=i+2;
      sscanf(line, "v %lf %lf %lf", &(*data)->vertex_array[a], &(*data)->vertex_array[b], &(*data)->vertex_array[c]);
      i+=3;
    } else if (FormatCheck(line) == FACET) {
      continue;
    }
  }
  free(line);
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
  // printf("%s = FILE\n", file_path);
  // printf("%d = vertices_count\n", data->vertices_count);
  // printf("%d = facets_count \n", data->facets_count);
  // printf("VERTICES_MATRIX \n");
  // for (int i = 0; i < data->matrix_3d.rows; i++) {
  //   printf("%d: ", i+1);
  //   for (int j = 0; j < data->matrix_3d.columns; j++) {
  //     printf(" %1.2Lf", data->matrix_3d.matrix[i][j]);
  //   }
  //   printf("\n");
  // }
  // printf("FACET_DATA \n");
  // for (int i = 0; i < data->facets_count; i++) {
  //   printf("%d: ", i+1);
  //   for (int j = 0; j < data->polygons[i].v_in_facets; j++) {
  //     printf(" %1.2Lf", data->polygons[i].vertexes[j]);
  //   }
  //   printf("\n");
  // }
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
  // if (data) {
  //   long double old = data->polygons[0].vertexes[0];
  //   res = calloc(1024, sizeof(*res));
  //   res[f++] = old;
  //   for (int i = 0; i < data->facets_count; i++) {
  //     // res = realloc(res, (f+data->polygons[i].v_in_facets) * sizeof(long double));
  //     for (int j = 1; j < data->polygons[i].v_in_facets; j++) {
  //       res[f++] = (data->polygons->vertexes[j]);
  //       res[f++] = (data->polygons->vertexes[j]);
  //     }
  //   }
  // }
  // s = calloc(1, sizeof(*s));
  // s[0] = f;
  return res;
}
