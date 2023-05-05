# MNIST Digit Recognition

This program aims to recognize the number 1 from the MNIST dataset. It uses a similarity approach between two matrices and outputs the five closest images. 

## Files
* `X.matrix`: the matrix containing the images.
* `ones.matrix`: the matrix containing the values of the number 1.
* `main.c`: the source code file.

## Functions
### `Matrix read_matrix(char *filename)`

Reads a matrix from a file.

#### Parameters
* `filename`: the file containing the matrix.

#### Return
Returns a matrix structure containing the matrix.

### `int flat_index(int i, int j, int numcol)`

Converts a 2D index to flattened 1D index.

#### Parameters
* `i`: the row of the element.
* `j`: the column of the element.
* `numcol`: the number of columns.

#### Return
Returns the flattened index.

### `int get_elem(Matrix M, int i, int j)`

Retrieves an element from a matrix.

#### Parameters
* `M`: the matrix.
* `i`: the row of the element.
* `j`: the column of the element.

#### Return
Returns the element at row `i` and column `j`.

### `int * get_row(Matrix M, int i, int j)`

Retrieves the pointer to a matrix element.

#### Parameters
* `M`: the matrix.
* `i`: the row of the element.
* `j`: the column of the element.

#### Return
Returns the pointer to the element at row `i` and column `j`.

### `void set_elem(Matrix M, int i, int j, int value)`

Assigns a value to an element in a matrix.

#### Parameters
* `M`: the matrix.
* `i`: the row of the element.
* `j`: the column of the element.
* `value`: the value to be assigned.

### `void image2char(int image[], int Height, int Width)`

Prints an image to the console.

#### Parameters
* `image`: an array that stores the flattened image stored in column-major order.
* `Height`: the height of the image.
* `Width`: the width of the image.

### `int dist2(int * a, int * b, int len)`

Computes the squared Euclidean distance.

#### Parameters
* `a`: an integer array.
* `b`: an integer array.
* `len`: the length of the two arrays.

#### Return
Returns the total squared Euclidean distance.

### `void pairwise_dist2(Matrix M1, Matrix M2, Matrix D)`

Computes the pairwise squared distance of the `i`-th row of `M1` and the `j`-th row of `M2`.

#### Parameters
* `M1`: the first matrix.
* `M2`: the second matrix.
* `D`: a matrix `D` where `D_ij` is the squared distance between the `i`-th row of `M1` and the `j`-th row of `M2`.

### `int find_min_index(int a[], int len)`

Finds the index of the minimum element in an array.

#### Parameters
* `a`: an integer array.
* `len`: the length of the array.

#### Return
Returns the index of the minimum element in the array.

### `void minimum5(int len, int a[], int indices[])`

Finds the indices of the 5 minimum elements in an array.

#### Parameters
* `len`: the length of the array.
* `a`: an integer array.
* `indices`: an
