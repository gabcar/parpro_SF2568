
if (color == 0) {
  if (p != P-1) {
    MPI_Send(&u[I], 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD);
    MPI_Recv(&u[I+1], 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD, &status);
  }
  if (p != 0) {
    MPI_Send(&u[1], 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
    MPI_Recv(&u[0], 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD, &status);
  }
}else{
  MPI_Recv(&u[0], 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD, &status);
  MPI_Send(&u[1], 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
  if (p != P-1) {
    MPI_Recv(&u[I+1], 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD, &status);
    MPI_Send(&u[I], 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD);
  }
}
