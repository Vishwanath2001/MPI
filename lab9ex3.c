#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
void srandom (unsigned seed);
double pi_board (int darts); 
#define DARTS 5000
#define ROUNDS 500
#define MASTER 0
int main (int argc, char *argv[])
{
double homepi, pisum,pi,avepi;
int taskid,numtasks, rc,i;
MPI_Status status;
MPI_Init(&argc,&argv); //Initializing MPI
MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
printf ("MPI task %d has started...\n", taskid);
srandom (taskid);
avepi = 0;
for (i = 0; i < ROUNDS; i++)
{
 homepi = pi_board(DARTS);
 rc = MPI_Reduce(&homepi, &pisum, 1, MPI_DOUBLE, MPI_SUM,MASTER,
MPI_COMM_WORLD); //MPI_Reduce is used to sum the values of pi across all tasks
 if (rc != MPI_SUCCESS)
 printf("%d: mpc_reduce failed ! \n", taskid);
 if (taskid == MASTER) {
 pi = pisum/numtasks; 
 avepi = ((avepi * i) + pi)/(i + 1);
 printf("Round : %d , average value of pi = %10.8f\n",i,avepi);
 }
}
if (taskid == MASTER)
 printf ("\nReal value of PI: 3.1415926535897 \n");
MPI_Finalize();
return 0;
}
double pi_board(int darts) //Function for cal PI
{
#define sqr(x) ((x)*(x))
long random(void);
double x_coord, y_coord, pi, r;
int score, n;
unsigned int cconst;
 cconst = 2 << (31 - 1);
 score = 0;
 for (n = 1; n <= darts; n++) {
 r = (double)random()/cconst;
 x_coord = (2.0 * r) - 1.0;
 r = (double)random()/cconst;
 y_coord = (2.0 * r) - 1.0;
 if ((sqr(x_coord) + sqr(y_coord)) <= 1.0) 
 score++;
 }
pi = 4.0 * (double)score/(double)darts; //Calculating PI
return(pi);
}
