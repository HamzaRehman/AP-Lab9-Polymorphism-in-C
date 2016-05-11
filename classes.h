#define INITIALIZED 0
#define DESTROYED 1

// Matrix structure that shall be behaving as a class
typedef struct matrix_ {

	// Data members
	short status;
	int rows;
	int columns;
	int *array;

	// Methods
	void(*init)(void *, int, int);
	void(*populate)(void *, int);
	void(*print)(void *);
	struct matrix_(*add)(void *, void *);
	struct matrix_(*multiply)(void *, void *);
	int(*l1norm)(void *);

} matrix;

// Vector structure that shall be behaving as a class
typedef struct vector_ {

	// Inherited all of matrix here
	matrix parent;
	int min_elem;
	int max_elem;

	// Methods
	void(*init)(void *, int, int, int);
	void(*populate)(void *, int);
	void(*print)(void *);
	struct vector_(*add)(void *, void *);
	int(*multiply)(void *, void *);
	int(*l1norm)(void *);

} vector;

// Function prototypes
matrix new_matrix();
matrix new_matrix_with_args(int rows, int columns);
vector new_vector();
vector new_vector_with_args(int dim, int min_elem, int max_elem);
