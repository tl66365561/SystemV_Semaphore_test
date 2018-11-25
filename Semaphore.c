
//exit和return的差别？
//return 是语言级别的，意味着堆栈调用的返回 ；exit是系统级别的，意味着进程的结束；



//信号量的使用

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<error.h>

#define IPC_KEY 0x12345678
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};


void sem_P(int id)
{
	struct sembuf buf;
	buf.sem_num=0;                
	buf.sem_op=-1;
	buf.sem_flg=SEM_UNDO;
	semop(id,&buf,1);

	
	}
								

void sem_V(int id)
{
	struct sembuf buf;
	buf.sem_num=0;
	buf.sem_op=1;
	buf.sem_flg=SEM_UNDO;
	semop(id,&buf,1);
}





int main()
{
  
   int semid=semget(IPC_KEY , 1 ,IPC_CREAT|0664 );          //信号量的创建
   if(semid<0)
   {
	   perror("create error");
	   return -1;
	   }


    union semun Val;
    Val.val=0;
    semctl(semid,0,SETVAL,Val);                                  //信号量设初值
    
	int pid=fork();		
	if(pid<0)
	{
		perror("fork error");
		return -1;
		}
     else if(pid==0)
	 {
		 while(1)
		 {
	    	printf("A");
            fflush(stdout);
		    sleep(1);
//		    printf("A");
//			fflush(stdout);
		    sem_V(semid);
		 
		 }
	 }
     else
	 {

		 while(1)
		 {
			sem_P(semid); 
	    	printf("B");
            fflush(stdout);
		    sleep(1);
//			printf("B");
//			fflush(stdout);

			 }


}
	
	return 0;
	}
