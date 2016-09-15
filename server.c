#include"header.h"
#include"client.h"
#include"declarations.h"
static int alarm_fired = 0;
void check(int signo)
{
	printf("signal recieved!\n");
	alarm_fired = 1;
}

int main()
{
	int fd, cl_fd, ret, res,cnt, fret, arr[2], NOC=0;
	char rfdp1[4], wfdp1[4];
	char client_fifo[256];
	struct client1 r;
	if(access(REQUESTFIFO, F_OK) == -1)
	{
		ret = mkfifo(REQUESTFIFO, 777);
	}
	else
	{
		printf("No Permission to create the FIFO\n");
	}
	printf("File: %s ret = %d\n",__FILE__,ret);
	while(1)
	{
		fd = open(REQUESTFIFO, O_RDONLY);
		ret = read(fd, &r, sizeof(struct client1));
		printf("File: %s Read = %d bytes\n",__FILE__,ret);
		if(pipe(arr)!=0)
		{
			printf("program faile \n");
			exit(EXIT_SUCCESS);
		}
		printf("File: %s fd's created by the pipe 1 are arr[0] = %d arr[1] = %d\n", __FILE__, arr[0], arr[1]);
		
		sprintf(rfdp1,"%d", arr[0]);
		sprintf(wfdp1,"%d", arr[1]);
		fret = fork();
		switch(fret)
		{
		case -1:
			perror("fork");
			break;
		case 0:
			switch(r.oper)
			{
				case '+':
					execl("./adder", "adder",rfdp1,wfdp1, NULL);
					break;
				case '-':
					execl("./substract", "substract",rfdp1,wfdp1, NULL);
					break;
				case '*':
					execl("./multiply", "multiply",rfdp1,wfdp1, NULL);
					break;
			}
			break;
		default:
			cnt = write(arr[1], &r, sizeof(struct client1));
			printf("File: %s Wrote %d bytes TO ADDER\n",__FILE__,cnt);

			signal(SIGALRM, check);
			wait();
			if(alarm_fired)
			{
			ret = read(arr[0], &res, sizeof(int));
			printf("File: %s Read %d bytes FROM ADDER\n",__FILE__,ret);
			printf("File: %s Result from ADDER.c =  %d \n",__FILE__,res);
			alarm_fired = 0;
			}
			sprintf(client_fifo, RESULTFIFO, r.pid);
			cl_fd = open(client_fifo, O_WRONLY);
			ret = write(cl_fd, &res, sizeof(int));
			printf("File: %s Wrote %d bytes TO CLIENT1\n",__FILE__,ret);
		}
	close(arr[0]);
	close(arr[1]);
	close(fd);
	close(cl_fd);
	int i;
/*	for(i=0;i<2;i++)
	{
	NOC++;
	printf("No. Of Clients Running = %d\n", NOC);
	}
*/	}


	return 0;
}
