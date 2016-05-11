#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "classes.h"

void initMatrix(void *, int, int);
void populateMatrix(void *, int);
void printMatrix(void *);
matrix addMatrix(void *, void *);
matrix multiplyMatrix(void *, void *);
int l1normOfMatrix(void *);

void initVector(void *, int, int, int);
void populateVector(void *, int);
void printVector(void *);
vector addVector(void *, void *);
int multiplyVector(void *, void *);
int l1normOfVector(void *);

// Our 'Constructor' for Matrix
matrix new_matrix() {
	matrix m;
	m.init = initMatrix;
	m.populate = populateMatrix;
	m.print = printMatrix;
	m.add = addMatrix;
	m.multiply = multiplyMatrix;
	m.l1norm = l1normOfMatrix;
	return m;
}

matrix new_matrix_with_args(int rows, int columns) {
	matrix m = new_matrix();
	m.init(&m, rows, columns);
	return m;
}

// Our 'Constructor' for Vector
vector new_vector() {
	vector v;
	v.init = initVector;
	v.populate = populateVector;
	v.print = printVector;
	v.add = addVector;
	v.multiply = multiplyVector;
	v.l1norm = l1normOfVector;
	v.parent = new_matrix();
	return v;
}

vector new_vector_with_args(int dim, int min_elem, int max_elem) {
	vector v = new_vector();
	v.init(&v, dim, min_elem, max_elem);
	return v;
}

// Method definitions

void initMatrix(void *m, int rows, int columns) {
	((matrix *)m)->status = INITIALIZED;
	((matrix *)m)->rows = rows;
	((matrix *)m)->columns = columns;
	((matrix *)m)->array = (int *)malloc(sizeof(int) * rows * columns);
}

void initVector(void *v, int dim, int min_elem, int max_elem) {
	((vector *)v)->parent.init(&(((vector *)v)->parent), dim, 1);
	((vector *)v)->min_elem = min_elem;
	((vector *)v)->max_elem = max_elem;
}

void populateMatrix(void *m, int limiter) {
	int i, j;
	switch (((matrix *)m)->status) {
	case INITIALIZED:
		srand(time(NULL));
		for (i = 0; i < ((matrix *)m)->columns; i++) {
			for (j = 0; j < ((matrix *)m)->rows; j++) {
				((matrix *)m)->array[i * ((matrix *)m)->columns + j] = rand() / (float)RAND_MAX * limiter;
			}
		}
		break;
	case DESTROYED:
		printf("Error: Cannot populate!\nReason: Data Structure was destroyed.\n\n");
		break;
	default:
		printf("Error: Cannot populate!\nReason: Data Structure not initialized.\n\n");
		break;
	}
}

void populateVector(void *v, int limiter) {
	((vector *)v)->parent.populate(&(((vector *)v)->parent), limiter);
}

void printMatrix(void *m) {
	int i, j;
	switch (((matrix *)m)->status) {
	case INITIALIZED:
		for (i = 0; i < ((matrix *)m)->columns; i++) {
			printf("\n");
			for (j = 0; j < ((matrix *)m)->rows; j++) {
				printf("\t%d", ((matrix *)m)->array[i * ((matrix *)m)->columns + j]);
			}
		}
		printf("\n\n");
		break;
	case DESTROYED:
		printf("Error: Cannot print!\nReason: Data Structure was destroyed.\n\n");
		break;
	default:
		printf("Error: Cannot print!\nReason: Data Structure not initialized.\n\n");
		break;
	}
}

void printVector(void *v) {
	((vector *)v)->parent.print(&(((vector *)v)->parent));
}

matrix addMatrix(void *m, void *n) {
	matrix result = new_matrix_with_args(((matrix *)m)->rows, ((matrix *)m)->columns);
	result.populate(&result, 0);
	if (((matrix *)m)->rows == ((matrix *)n)->rows &&
		((matrix *)m)->columns == ((matrix *)n)->columns) {
		int i, j;
		for (i = 0; i < result.columns; i++) {
			for (j = 0; j < result.rows; j++) {
				result.array[i * result.columns + j] = ((matrix *)m)->array[i * ((matrix *)m)->columns + j]
					+ ((matrix *)n)->array[i * ((matrix *)n)->columns + j];
			}
		}
	}
	else {
		printf("Error: Addition not possible!\nReason: Uneven order of data structures.\n\n");
	}
	return result;
}

vector addVector(void *u, void *v) {
	vector result = new_vector_with_args(((vector *)(u))->parent.columns, ((vector *)(u))->min_elem, ((vector *)(u))->max_elem);
	matrix m = ((vector *)(u))->parent;
	matrix n = ((vector *)(v))->parent;
	result.parent = result.parent.add(&m, &n);
	return result;
}

matrix multiplyMatrix(void *m, void *n) {
	matrix result = new_matrix_with_args(((matrix *)m)->rows, ((matrix *)n)->columns);
	result.populate(&result, 0);
	if (((matrix *)m)->columns == ((matrix *)n)->rows) {
		int i, j, k;
		for (i = 0; i < ((matrix *)m)->rows; i++) {
			for (j = 0; j < ((matrix *)n)->columns; j++) {
				for (k = 0; k < ((matrix *)n)->rows; k++) {
					result.array[i * result.columns + j] = result.array[i * result.columns + j]
						+ ((matrix *)m)->array[i * ((matrix *)m)->columns + k]
						* ((matrix *)n)->array[k * ((matrix *)n)->columns + j];
				}
			}
		}
	}
	else {
		printf("Error: Multiplication not possible!\nReason: Uneven order of data structures.\n\n");
	}
	return result;
}

int multiplyVector(void *u, void *v) {
	int result = 0;
	if (((vector *)(u))->parent.rows == ((vector *)(v))->parent.rows) {
		int i;
		for (i = 0; i < ((vector *)(u))->parent.rows; i++) {
			result += ((vector *)(u))->parent.array[i] * ((vector *)(v))->parent.array[i];
		}
	}
	else {
		printf("Error: Multiplication not possible!\nReason: Uneven order of data structures.\n\n");
	}
	return result;
}

int l1normOfMatrix(void *m) {
	int i, j, sum = 0, max_ = 0;
	for (i = 0; i < ((matrix *)(m))->columns; i++) {
		for (j = 0; j < ((matrix *)(m))->rows; j++) {
			sum += ((matrix *)(m))->array[i * ((matrix *)(m))->columns + j];
		}
		if (sum > max_) {
			max_ = sum;
		}
	}
	return max_;
}

int l1normOfVector(void *v) {
	int i, sum = 0;
	for (i = 0; i < ((vector *)(v))->parent.rows; i++) {
		sum += ((vector *)(v))->parent.array[i];
	}
	return sum;
}
