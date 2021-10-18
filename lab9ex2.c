#include "mpi.h"
#include <stdio.h>
int main(argc,argv)
int argc;
char *argv[];
{
int nump,rk,des,src,rc,c,tag=1;
char inmsg, outmsg='x';
MPI_Status Stat;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &nump);
MPI_Comm_rank(MPI_COMM_WORLD, &rk);
des = rk+1;
src = rk-1;
if(des > 9)
{
des = 0;
}
if(src < 0)
{
src = 9;
}
rc = MPI_Send(&outmsg,1,MPI_CHAR,des,tag,MPI_COMM_WORLD);
printf("Node %d: pinged Process %d\n",rk,des);
rc = MPI_Recv(&inmsg,1,MPI_CHAR,src,tag,MPI_COMM_WORLD,&Stat); 
printf("Node %d: got a ping from Node %d\n",rk,src);
MPI_Finalize();
}
