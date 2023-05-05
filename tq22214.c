#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<math.h>

struct matrix
{
    int numrow;
    int numcol;
    int *elements;
};

typedef struct matrix Matrix;

/*
Read a matrix from file. Don't change it!
filename: the file that contains the matrix.
return: a matrix structure containing the matrix.
*/
Matrix read_matrix(char *filename)
{

    FILE *f = fopen(filename, "rb");
    // read int variables to the file.
    int numrow = getw(f);
    int numcol = getw(f);
    Matrix M = {numrow, numcol, calloc(numrow * numcol, sizeof(int))};

    for (int i = 0; i < M.numrow; i++)
    {
        for (int j = 0; j < M.numcol; j++)
        {
            M.elements[i*numcol + j] = getc(f);
        }
    }
    fclose(f);
    return M;
}

/*
Function that converts 2D index to flattened 1D index.
i,j: the row and the column of the element 
return: flattened index
*/
int flat_index(int i, int j, int numcol)
{
    return numcol * i + j;
}

/*
Retrieve an element from a matrix.
M: the matrix.
i,j: the row and column of the element.
return: the element at row i and column j.
*/
int get_elem(Matrix M, int i, int j)
{
    return M.elements[flat_index(i,j,M.numcol)];
}

/*
Retrieves the pointer of a Matrix element
M: the matrix
i,j: the row and column of the element.
return: the pointer to element at row i and column j
*/
int * get_row(Matrix M, int i, int j)
{
    return &M.elements[flat_index(i,j,M.numcol)];
}


/*
Assign value to an element in a matrix.
M: the matrix.
i,j: the row and column of the element.
value: the value to be assigned.
*/
void set_elem(Matrix M, int i, int j, int value)
{
    M.elements[flat_index(i,j,M.numcol)] = value;
}

/*
Print an image to the console. 
image: an array that stores the flattened image stored in column major order.
Height: the height of the image.
Width: the width of the image.
*/
void image2char(int image[], int Height, int Width)
{
    for(int y = 0; y < Height; y++)
    {
        for(int x = 0; x < Width; x++)
        {
            int value = image[(Height * y) + x];
            if(value <= 100)  printf(" ");
            else if(value > 100 && value <= 170) printf("I");
            else printf("M"); 
        }
        printf("\n");
    }
}

/*
Compute the squared euclidean distance
a: a int array
b: a int array
len: length of the two arrays
*/
int dist2(int * a, int * b, int len)
{
    int total = 0;
    
    for(int i = 0; i < len; i++)
        total+=pow(a[i] - b[i],2);
    
    return total;
}

/*
Compute the pairwise squared distance of the i-th row of 
M1 and the j-th row of M2.
M1: the first matrix.
M2: the second matrix.
return: a matrix D where D_ij is the squared distance between 
the i-th row of M1 and the j-th row of M2.
*/
void pairwise_dist2(Matrix M1, Matrix M2, Matrix D)
{
    for(int j = 0; j < M2.numrow; j++)
        for(int i = 0; i < M1.numrow ; i++)
            set_elem(D, i, j, dist2(get_row(M1,i,0), get_row(M2,j,0), M1.numcol));
}

/*
Find the index of the minimum element in an array. 
a: the array.
len: the length of the array.
return: the index of the minimum element in the array.
example: [1,2,3,4,5] -> 0
         [5,4,3,2,1] -> 4
*/
int find_min_index(int a[], int len)
{
    //saves the pointer of the value with smallest value
    int * smallest = &a[0];  

    for(int i = 1; i < len; i++)
        if(*smallest > a[i])// checks value at address against a[i]
            smallest = &a[i];
    
    *smallest = INT_MAX; // removes smallest value 

    //This returns the index
    return smallest - a;     
}

/*
Find the indices of 5 minimum elements in an array.
a: the array.
len: the length of the array a.
return: an array of 5 integers containing the indices of the 5 minimum elements in a.
example: [1,2,33,4,5,23,6] -> [0,1,3,4,6]
*/
void minimum5(int len, int a[], int indices[])
{
    for(int i = 0; i < 5; i++)
        indices[i] = find_min_index(a,len);
}

void main()
{
    Matrix X = read_matrix("./X.matrix");
    printf("N: %d, M: %d\n", X.numrow, (int) sqrt(X.numcol));   

    Matrix T = read_matrix("./T.matrix");
    printf("L: %d\n", T.numrow);

    Matrix Y = read_matrix("./Y.matrix");

    int s = 0;
    for (int i = 0; i < Y.numrow; i++)
        if(Y.elements[i*Y.numcol + 0] == 1)
            s++;

    printf("Number of 1 in the training set: %d\n", s);
    

    // initialising lengths of 3 matricies
    int N = X.numrow, M = (int) sqrt(X.numcol), L = T.numrow; 
    
    // instantiating D 
    Matrix D = {L, N, calloc(N * L, sizeof(int))};
    
    //sets D's components to equal the norm of rows in T and X 
    pairwise_dist2(T,X,D);

    for(int i=0; i < L;i++)
    { 
        int count = 0;
        int image[(int)pow(M,2)]; 
        int indices[5];
        int labels[5];

        printf("The %d-th testing image:\n", i);
        
        //Prints out current test image
        image2char(get_row(T,i,0),M,M);

        //populates indices with 5 smallest ints in D's ith row
        minimum5(D.numcol,get_row(D,i,0),indices);
        
        // Adds the values from Y at the given indices
        for(int k = 0; k < 5; k++){
            labels[k] = get_elem(Y,indices[k],0);  
            printf("%d",labels[k]);
          }
        // increments "count" for every "1" in labels
        for(int j = 0; j < 5; j++)
            if(labels[j] == 1) 
                count++;

        printf("The %d-th testing image is classified as ",i);
        
        (count >= 3) ? printf("1\n") : printf("not 1\n");

        printf("\n");
        printf("----------------------------------------\n");
    }

    free(D.elements);
    free(X.elements);
    free(T.elements);
    free(Y.elements);
}
