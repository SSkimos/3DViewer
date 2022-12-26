#ifndef MODEL_S21_PARSE_OBJ_H_
#define MODEL_S21_PARSE_OBJ_H_
#include <stdlib.h>
#include <stdio.h>

int ParseObj(const char* file_path);
FILE* OpenFile(const char* filename);
int FormatCheck(const char* line);
int FacetsAnalyzer(const char* line);
int FormatFacet(char* line, int facet_count);

#endif  // MODEL_S21_PARSE_OBJ_H_
