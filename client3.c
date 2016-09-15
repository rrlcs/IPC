#include"header.h"
#include"client.h"
#include"semun.h"
#include"declarations.h"
static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);
static int sem_id;

int main()
{
	struct client1 cli;
	int fd, ret, res;
	char client_fifo[256];
	fd = open(REQUESTFIFO, O_WRONLY);

	cli.pid = getpid();
	cli.oper = '*';
	cli.opr1 = 50;
	cli.opr2 = 3;	

	printf("File: %s cli.pid = %d\n",__FILE__, cli.pid);	
	printf("File: %s cli.oper = %c\n",__FILE__, cli.oper);	
	printf("File: %s cli.opr1 = %d\n",__FILE__, cli.opr1);	
	printf("File: %s cli.opr2 = %d\n",__FILE__, cli.opr2);

        sem_id = semget((key_t)1234,1,666|IPC_CREAT);
        set_semvalue();
        semaphore_p();
        ret = write(fd, &cli, sizeof(struct client1));
        semaphore_v();
        del_semvalue();

	printf("File: %s Wrote %d bytes to server\n",__FILE__, ret);
	sprintf(client_fifo,RESULTFIFO,cli.pid);
	if(access(client_fifo, F_OK) == -1)
        {
                ret = mkfifo(client_fifo, 777);
        }
        else
        {
                printf("No Permission to create the FIFO\n");
        }
	fd = open(client_fifo, O_RDONLY);
	ret = read(fd, &res, sizeof(int));
	printf("File: %s Read %d bytes from server\n",__FILE__, ret);
	printf("File: %s Result =  %d \n",__FILE__, res);
close(fd);	
}

static int set_semvalue()
{
        union semun sem_union;
        sem_union.val = 1;
        semctl(sem_id, 0, SETVAL, sem_union);
}

static void del_semvalue()
{
        union semun sem_union;
        sem_union.val = 1;
        semctl(sem_id, 0, IPC_RMID, sem_union);
}

static int semaphore_p()
{
        struct sembuf sem_b;
        sem_b.sem_num = 0;
        sem_b.sem_op = -1;
        sem_b.sem_flg = SEM_UNDO;
        semop(sem_id, &sem_b, 1);
}

static int semaphore_v()
{
        struct sembuf sem_b;
        sem_b.sem_num = 0;
        sem_b.sem_op = 1;
        sem_b.sem_flg = SEM_UNDO;
        semop(sem_id, &sem_b, 1);
}

