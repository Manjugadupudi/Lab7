#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <math.h> 

void sample_rand(const double a, const double b ,const int dim, double *x) {
  for(int i=0;i<dim;++i) {
    double tmp = ((double) rand())/((double) RAND_MAX);
    x[i] = (b-a)*tmp + a;
  }
}
double logL(double x1,double x2) {
  return -(1.-x1)*(1.-x1) -100.*(x2-x1*x1)*(x2-x1*x1);
}


int main(int argc, char **argv)
{
  int rank, size;
  MPI_Init (&argc, &argv);
  // initializes MPI
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  // get current MPI-process ID. O, 1, ...
  MPI_Comm_size (MPI_COMM_WORLD, &size);

  long N = atol( argv[1] );
  srand(time(NULL));
  // each MPI process gets a unique seed
  const int dim = 2;
  double x[dim];
  // array of random numbers
  // search for the function’s maximum
  double min = -1;
    for(long int i=1; i<=N; ++i) {
      sample_rand(-5.,5.,dim,x);
      double f_i = exp(logL(x[0],x[1]));
      if( f_i > max) {
        max = f_i;
}
  printf("local max = %1.5e, from process %d of %d %d\n",max,rank,size,N);
  MPI_Finalize();
return 0;
}
}
