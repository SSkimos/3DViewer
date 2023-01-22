#ifndef MODEL_S21_PARSE_OBJ_H_
#define MODEL_S21_PARSE_OBJ_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>

#include "s21_data_structure.h"
data_t* LoadObjFile(const char* file_path);
int ParseObj(const char* file_path, data_t** data);
int CountObj(const char* file_path, data_t* data);
long double* RemakeMatrix(data_t* data);
long double* RemakeFacets(data_t* data, int* s);
int DataAllocate(data_t** data);
int DebugObj(const char* file_path, data_t* data);

int ArrayFacetFactory(const char* line, unsigned int* facet_row, int* ind);
FILE* OpenFile(const char* filename);
void RemoveObject(data_t* obj);
char FormatCheck(const char* line);
int ScaleObj(data_t** object);
int FacetsAnalyzer(const char* line);
int FormatFacet(char* line, int facet_count);

float max_elem(float a, float b, float c);
float min_elem(float a, float b, float c);
data_t* InitData();

#ifdef __cplusplus
}
#endif

#endif  // MODEL_S21_PARSE_OBJ_H_
