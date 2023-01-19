#include "s21_parse_obj.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix_t/s21_matrix.h"
#include "s21_affin_p.h"
#include "s21_data_structure.h"

#define MAX_SIZE 512
#define VERTICE 1
#define FACET 2

float max_elem(float a, float b, float c);
float min_elem(float a, float b, float c);
data_t* InitData();

data_t* LoadObjFile(const char* file_path) {
  data_t* data = InitData();
  if (data) {
    CountObj(file_path, data);
    ParseObj(file_path, &data);
    ScaleObj(&data);
  }
  return data;
}

data_t* InitData() {
  data_t* data = calloc(1, sizeof(*data));
  if (data) {
    data->vertices_count = 0;
    data->facets_count = 0;
    data->size_f = 0;
  }
  return data;
}

int ScaleObj(data_t** object) {
  affine_t* a = malloc(1 * sizeof(*a));
  if (a && object) {
    a->rotateX = 0;
    a->rotateY = 0;
    a->rotateZ = 0;
    a->moveX = 0;
    a->moveY = 0;
    a->moveZ = 0;
    a->scale = 1 / (*object)->max_vert + (*object)->min_vert;
    MoveAndRotateModel(object, a);
  }
  free(a);
  return 0;
}

int CountObj(const char* file_path, data_t* data) {
  FILE* obj = OpenFile(file_path);

  size_t max_size = MAX_SIZE;
  char* line = calloc(max_size, sizeof(*line));
  ;

  if (line) {
    while (fgets(line, MAX_SIZE - 1, obj) != NULL && (!feof(obj))) {
      if (FormatCheck(line) == 'v') {
        data->vertices_count += 3;
      } else if (FormatCheck(line) == 'f') {
        data->size_f += FacetsAnalyzer(line);
        (data->facets_count)++;
      }
    }
  }
  free(line);
  fclose(obj);
  return 0;
}

int ParseObj(const char* file_path, data_t** data) {
  FILE* obj = OpenFile(file_path);

  size_t max_size = MAX_SIZE;
  char* line = calloc(max_size, sizeof(*line));
  ;

  int mas = (*data)->vertices_count * 3;
  float* vertexes = calloc(mas, sizeof(float));
  unsigned int* facets = calloc((*data)->size_f * 2, sizeof(unsigned int));
  int i = 0;
  int j = 0;
  if (vertexes) {
    while (fgets(line, MAX_SIZE, obj) != NULL && (!feof(obj))) {
      if (FormatCheck(line) == 'v') {
        int a = i, b = i + 1, c = i + 2;
        sscanf(line, "v %f %f %f", &vertexes[a], &vertexes[b], &vertexes[c]);
        (*data)->max_vert = max_elem(vertexes[a], vertexes[b], vertexes[c]);
        (*data)->min_vert = min_elem(vertexes[a], vertexes[b], vertexes[c]);
        i += 3;
      } else if (FormatCheck(line) == 'f') {
        ArrayFacetFactory(line, facets, &j);
      }
    }
  }
  (*data)->size_f = j;
  (*data)->base_vertex_array = vertexes;
  (*data)->base_lines_array = facets;
  (*data)->vertex_array = calloc(mas, sizeof(float));
  (*data)->lines_array = calloc(j, sizeof(unsigned int));
  free(line);
  fclose(obj);
  return 0;
}

FILE* OpenFile(const char* filename) {
  FILE* fp = fopen(filename, "r");
  if (!fp) {
    perror("File doesn't exist.");
    fprintf(stderr, "%s\n", filename);
    exit(1);
  }
  return fp;
}

char FormatCheck(const char* line) {
  char ret = 0;
  if ((line[0] == 'v') && (line[1] == ' ' || isdigit(line[1]))) ret = 'v';
  if (line[0] == 'f') ret = 'f';
  return ret;
}

int FacetsAnalyzer(const char* line) {
  int ret = 0;
  char* number_char = calloc(strlen(line) + 2, sizeof(*number_char));
  if (number_char) {
    strcpy(number_char, line);
    char* num_pointer = strtok(number_char, " ");
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

int ArrayFacetFactory(const char* line, unsigned int* facet_row, int* ind) {
  char* number_char = (char*)line;
  char* num_pointer = strtok(number_char, " ");
  int i = *ind;
  int ret = 0;
  int start = 0;
  int first_facet_value = 0;
  while (num_pointer != NULL) {
    if (isdigit(*num_pointer)) {
      int facet = strtold(num_pointer, NULL) - 1;
      facet_row[i++] = facet;
      if (start)
        facet_row[i++] = facet;
      else
        first_facet_value = facet;
      start = 1;
    }
    num_pointer = strtok(NULL, " ");
  }
  if (start) facet_row[i++] = first_facet_value;
  *ind = i;
  return ret;
}

int DebugObj(const char* file_path, data_t* data) {
  printf("%s = FILE\n", file_path);
  printf("%d = vertices_count\n", data->vertices_count);
  printf("%d = facets_count \n", data->facets_count);
  printf("VERTICES_MATRIX \n");
  int f = 0;
  for (size_t i = 0; i < data->vertices_count / 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      printf("%f ", data->base_vertex_array[f++]);
    }
    printf("\n");
  }
  printf("FACET_DATA \n");
  for (size_t i = 0; i < data->size_f; i++) {
    printf("%d ", data->base_lines_array[i]);
  }
  return 0;
}

void RemoveObject(data_t* obj) {
  if (obj) {
    printf("Null Down\n");
    free(obj->lines_array);
    free(obj->vertex_array);
    free(obj->base_lines_array);
    free(obj->base_vertex_array);
    free(obj);
  }
}

float max_elem(float a, float b, float c) {
  float ans = 0;
  if (a >= b && a >= c) {
    ans = a;
  } else if (b >= a && b >= c) {
    ans = b;
  } else {
    ans = c;
  }
  return ans;
}

float min_elem(float a, float b, float c) {
  float ans = 0;
  if (a <= b && a <= c) {
    ans = a;
  } else if (b <= a && b <= c) {
    ans = b;
  } else {
    ans = c;
  }
  return ans;
}
