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
  int mas = (*data)->vertices_count * 3;
  int facets_memory = 1;
  long double * vertexes = calloc(mas, sizeof(long double));
  unsigned int* facets = calloc(facets_memory, sizeof(unsigned int));
  int i = 0;
  int j = 0;
  if (vertexes) {
    while ((getline(&line, &max_size, obj) != -1) && (!feof(obj))) {
      if (FormatCheck(line) == VERTICE) {
        int a = i, b=i+1, c=i+2;
        long double tmp1=0, tmp2=0, tmp3=0;
        printf("line = %s", line);
        sscanf(line, "v %Lf %Lf %Lf", &tmp1, &tmp2, &tmp3);
        //sscanf(line, "v %Lf %Lf %Lf", &(vertexes[a]), &vertexes[b], &vertexes[c]);
        printf("v %Lf %Lf %Lf = SCED\n", tmp1, tmp2, tmp3);
        //printf("v %Lf %Lf %Lf = SCANNED\n", (vertexes[a]), vertexes[b], vertexes[c]);
        i+=3;
      } else if (FormatCheck(line) == FACET) {
        facets_memory += FacetsAnalyzer(line);
        facets = realloc(facets, facets_memory * 2 * sizeof(unsigned int));
        ArrayFacetFactory(line, facets, &j);
      }
    }
  }
  (*data)->vertex_array = vertexes;
  (*data)->lines_array = facets;
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


int ArrayFacetFactory(const char* line, unsigned int* facet_row, int* ind) {
  char* number_char = (char*) line;
  char *num_pointer = strtok(number_char, " ");
  int i = *ind;
  int ret = 0;
  int start = 0;
  int first_facet_value = 0;
  while (num_pointer != NULL) {
    if (isdigit(*num_pointer)) {
      // 1 7 5
      // 1 7 7 5 5 1
      int facet = strtold(num_pointer, NULL) - 1;
      facet_row[i++] = facet;
      if (start) facet_row[i++] = facet;
      else first_facet_value = facet; 
      start = 1;
    }
    num_pointer = strtok(NULL, " ");
  }
  if (start) facet_row[i++] = start;
  *ind = i;
  return ret;
}

int DebugObj(const char* file_path, data_t *data) {
  printf("%s = FILE\n", file_path);
  printf("%d = vertices_count\n", data->vertices_count);
  printf("%d = facets_count \n", data->facets_count);
  printf("VERTICES_MATRIX \n");
  int f = 0;
  for (int i = 0; i < data->vertices_count; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%lf ", data->vertex_array[f++]);
    }
    printf("\n");
  }
  printf("FACET_DATA \n");
  // for (int i = 0; i < data->facets_count; i++) {
  //   printf("%d: ", i+1);
  //   for (int j = 0; j < data->polygons[i].v_in_facets; j++) {
  //     printf(" %1.2Lf", data->polygons[i].vertexes[j]);
  //   }
  //   printf("\n");
  // }
  return 0;
}

