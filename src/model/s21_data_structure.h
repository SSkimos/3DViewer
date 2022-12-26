#ifndef MODEL_DATA_STRUCTURE_H_
#define MODEL_DATA_STRUCTURE_H_

typedef struct Matrix {
	double **matrix;
	int rows;
	int cols;
} matrix_t;

typedef struct facets {
	int *vertexes;
	int v_in_facets;
} polygon_t;

typedef struct data {
  unsigned int vertices_count;
  unsigned int facets_count;
  matrix_t* matrix_3d;
  polygon_t* polygons;
} data_t;





#endif // MODEL_DATA_STRUCTURE_H_
