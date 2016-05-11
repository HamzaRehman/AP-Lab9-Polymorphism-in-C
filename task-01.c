#include <stdio.h>
#include "classes.h"

int main() {

	// matrix m = new_matrix();
	// vector v = new_vector();

	matrix m = new_matrix_with_args(2, 2);
	vector v = new_vector_with_args(4, 4, 4);

	// m.init(&m, 2, 2);
	m.populate(&m, 100);
	printf("Matrix 'm',\n");
	m.print(&m);

	// v.init(&v, 4, 4, 4);
	v.populate(&v, 100);
	printf("Vector 'v',");
	v.print(&v);

	matrix addResult = m.add(&m, &m);
	matrix mulResult = m.multiply(&m, &m);
	int l1normM = m.l1norm(&m);
	vector addResult_ = v.add(&v, &v);
	int mulResult_ = v.multiply(&v, &v);
	int l1normV = v.l1norm(&v);

	printf("Matrix addition answer,\n");
	addResult.print(&addResult);
	printf("Matrix multiplication answer,\n");
	mulResult.print(&mulResult);
	printf("Matrix L1 Norm answer: %d\n", l1normM);

	printf("Vector addition answer: ");
	addResult_.print(&addResult_);
	printf("Vector multiplication answer: %d\n", mulResult_);
	printf("Vector L1 Norm answer: %d\n", l1normV);

	return 0;
}
