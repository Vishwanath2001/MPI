#include "mpi.h"
#include <stdio.h>
int main(argc,argv)
int argc;
char *argv[];
{
 int nump,rk,des,src,rc,c,tag=1;
 char inmsg, outmsg='x';
 MPI_Request send_req, recv_req;
 MPI_Init(&argc,&argv);
 MPI_Comm_size(MPI_COMM_WORLD, &nump);
 MPI_Comm_rank(MPI_COMM_WORLD, &rk);
 if(rk == 0) 
 {
 des = 1;
 src = 1;
 rc =
MPI_Isend(&outmsg,1,MPI_CHAR,des,tag,MPI_COMM_WORLD,&send_req);
 printf("Process %d: pinged Process 1\n",rk);
 rc = MPI_Irecv(&inmsg,1,MPI_CHAR,src,tag,MPI_COMM_WORLD,&recv_req);
 printf("Process %d: got a ping from Process 1\n",rk);


 }
 else if(rk == 1)
 {
 des = 0;
 src = 0;
 rc = MPI_Irecv(&inmsg,1,MPI_CHAR,src,tag,MPI_COMM_WORLD,&recv_req);
 printf("Process %d: got a ping from Process 0\n",rk);
 rc =
MPI_Isend(&outmsg,1,MPI_CHAR,des,tag,MPI_COMM_WORLD,&send_req);
 printf("Process %d: pinged Process 0\n",rk);
 }
 MPI_Finalize();
}
