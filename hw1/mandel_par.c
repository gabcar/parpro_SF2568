#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <math.h>
#include <complex.h>

unsigned char cal_pix(double complex d, double b, int N){
  unsigned char count = 0;
  double complex z = 0;
  while((cabs(z)<b) && (count < N)){
    z = z*z+d;
    count++;
    if (count == 100) {
    }
  }
  //printf("count returned: %d\n",count);
  return count;
}

int main(int argc, char **argv){
  int rank, size, tag, rc, i, j;
  MPI_Status status;

  rc = MPI_Init(&argc, &argv);
  rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
  rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  tag = 100;

  double b = 2;
  int w = 512;
  int h = 512;
  int max_iterations = 256;

  int w_split = w/(size+1);

  double dx = 2*b/(w-1);
  double dy = 2*b/(h-1);

  unsigned char M[h][w_split];
  
  for (int x = 0; x<w_split; x++){
    double dreal = (x+rank*w_split)*dx-b;
    for (int y = 0; y < h; y++){
      double dimg = y*dy-b;
      double complex d = dreal + I*dimg;
      unsigned char pix_val = cal_pix(d,b,max_iterations);
      M[x][y] = pix_val;
    }
  }
  printf("Node %d done. \n",rank );

  if (rank!=0) {
    rc = MPI_Send(&M, sizeof(int), MPI_INT, rank, tag, MPI_COMM_WORLD);
  }
  if (rank==0) {
    unsigned char big_M[h][w];
    //first root node
    for (int x = 0; x < w_split; x++) {
      for (int y = 0; y < h; y++) {
        big_M[y][x] = M[y][x];
      }
    }
    for (int i = 1; i < size; i++) {
      rc = MPI_Recv(&M, sizeof(int), MPI_INT, i, tag, MPI_COMM_WORLD, &status);
      for (int x = 0; x < w_split; x++) {
        for (int y = 0; y < h; y++) {
          big_M[y][x+w_split*i] = M[y][x];
        }
      }
    }
    FILE *fp;
    fp = fopen("color.txt","w");
    for (int j = 0; j < h; j++) {
      for (int i = 0; i < w; i++){
      fprintf(fp, "%hhu ", big_M[i][j]);
      }
    fprintf(fp, "\n");
    }
  }
}
