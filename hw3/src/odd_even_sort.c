#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <mpi.h>

#define geq(a,x) ((a) > (x) ? (1) : (0))

// A utility function to swap two elements
void swap(double* a, double* b)
{
    double t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (double arr[], int low, int high)
{
    double pivot = arr[high];    // pivot
    int i = (low - 1);  // Index of smaller element
    //printf("%f\n",pivot );

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(double arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/* Function to print an array */
void printArray(double arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%f ", arr[i]);
    printf("\n");
}

void takeHigh(double *x, double *a, int num_x, int num_a){
  double temp[num_x];
  int i = num_x-1;
  int j = num_a-1;
  for (int n = num_x-1; n >= 0; --n) {
    if (x[i] >= a[j]) {
      temp[n] = x[i];
      i--;
    }else{
      temp[n] = a[j];
      j--;
    }
  }
  for (int n = 0; n < num_x; ++n) {
    x[n] = temp[n];
  }
  //printf("%s","High: " );
  for (int n = 0; n < num_x; n++) {
    //printf("%f, ", x[n]);
  }
  //printf("\n" );
  return;
}

void takeLow(double *x, double *a, int num_x, int num_a){
  double temp[num_x];
  int i = 0;
  int j = 0;

  for (int n = 0; n < num_x; ++n) {
    if (x[i] < a[j]) {
      temp[n] = x[i];
      i++;
    }else{
      temp[n] = a[j];
      j++;
    }
  //  printf("i: %d, j: %d\n", i, j );
  }
  //printf("%s","Low: " );
  for (int n = 0; n < num_x; ++n) {
    x[n] = temp[n];
    //printf("%f, ", x[n]);
  }
  //printf("\n" );

  return;
}


int main(int argc, char **argv)
{
  int P, p, N, I, i, step, upsize, downsize, is_odd, upper_bound, lower_bound;
  bool evenprocess, evenphase;
  double *x;
  double *a;
  int tag = 100;
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &P);
  MPI_Comm_rank(MPI_COMM_WORLD, &p);
  MPI_Status status;

  /* Find problem size N from command line */
  if (argc < 2) fprintf(stderr, "No size of N given");
  N = atoi(argv[1]);

  /* local size. Modify if P does not divide N */
  //I = (N+P-p-1)/P;

  I = (N+P-p-1)/P;

  /* random number generator initialization */
  srandom(p+1);
  x = malloc(sizeof(x) * I);
  a = malloc((sizeof(x)+1)*2);
  /* data generation */
  //printf("%s", "Unsorted list: ");
  for (i = 0; i < I; i++){
    x[i] = ((double) random())/(RAND_MAX);
  }
  //printArray(x, I);

  int right_I = (N+P-(p+1)-1)/P;
  int left_I = (N+P-(p-1)-1)/P;

  quickSort(x, 0, I-1);
  is_odd = P % 2;
  evenprocess = ((p % 2) == 0);
  evenphase = 1;

  for (step = 0; step < I; step++) {
    printf("%s%d%s\n", "Process ", p, ": ");
    if (evenphase == evenprocess) {
      if (p != P-1 /*-is_odd*evenphase*/) {
        MPI_Send(x, I, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD);
        MPI_Recv(a, I, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD, &status);
        takeLow(x, a, I, I);
      }
    }else{
      if (p != 0 /*+ is_odd*!evenphase*/) {
        MPI_Recv(a, I, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD, &status);
        MPI_Send(x, I, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
        takeHigh(x, a, I, I);
      }
    }
    evenphase = !evenphase;
  }


  //printf("%s%d%s","Process ", p, ": " );
  //printArray(x, I);
  int g = 1;
  if (p == 0) {

    for (i = 0; i < I; i++) {
        printf("%f\n ",x[i]);
    }
    MPI_Send(&g, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD);

  }else{

    MPI_Recv(&g, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD, &status);

    for (i = 0; i < I; i++) {
        printf("%f ", x[i]);
    }
    if (p != P-1) {
      MPI_Send(&g, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD);
    }
  }
  MPI_Finalize();
  return 0;
}
