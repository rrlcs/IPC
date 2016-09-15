#include"header.h"
#include"client.h"
#include"declarations.h"

int main(int argc, char *argv[])
{
	struct client1 add;
	int rfd,wfd, ret, res, byt, ppid;

	if(argc != 3)
        {
                printf("Error");
        }

        rfd = atoi(argv[1]);
        wfd = atoi(argv[2]);
        printf("File: %s\t rfd = %d\n",__FILE__, rfd);
        printf("File: %s\t wfd = %d\n",__FILE__, wfd);

	ret = read(rfd, &add, sizeof(struct client1));
	printf("File: %s Read %d bytes from rfd\n",__FILE__, ret);

	printf("File: %s add.pid = %d\n",__FILE__,(int)add.pid);
	printf("File: %s add.oper = %c\n",__FILE__,(char)add.oper);
        printf("File: %s add.opr1 = %d\n",__FILE__, (int)add.opr1);
        printf("File: %s add.opr2 = %d\n",__FILE__, (int)add.opr2);

        res =add.opr1 + add.opr2;

        printf("File: %s res = %d\n",__FILE__, res);

        byt = write(wfd, &res, sizeof(int));
        printf("File: %s Wrote %d bytes\n", __FILE__, byt);
	ppid = getppid();
//	if(kill(ppid, SIGALRM))
//		printf("signal passed!");
}
