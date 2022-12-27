#ifndef MODEL_S21_PARSE_OBJ_H_
#define MODEL_S21_PARSE_OBJ_H_
#include <stdlib.h>
#include "s21_data_structure.h"
#include <stdio.h>

data_t* ParseCountObj(const char* file_path);
int ParseObj(const char* file_path, data_t** data);
int CountObj(const char* file_path, data_t* data);

int DataAllocate(data_t** data);
int DebugObj(const char* file_path, data_t* data);

FILE* OpenFile(const char* filename);

int FormatCheck(const char* line);
int FacetsAnalyzer(const char* line);
int FormatFacet(char* line, int facet_count);
int ArrayFacetFactory(const char* line, long double* facet_row);

#endif  // MODEL_S21_PARSE_OBJ_H_
