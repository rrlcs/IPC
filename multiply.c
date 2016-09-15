#include"header.h"
#include"client.h"
#include"declarations.h"

int main(int argc, char *argv[])
{
	struct client1 mul;
	int rfd,wfd, ret, res, byt;

	if(argc != 3)
        {
                printf("Error");
        }

        rfd = atoi(argv[1]);
        wfd = atoi(argv[2]);
        printf("File: %s\t rfd = %d\n",__FILE__, rfd);
        printf("File: %s\t wfd = %d\n",__FILE__, wfd);

	ret = read(rfd, &mul, sizeof(struct client1));
	printf("File: %s Read %d bytes from rfd\n",__FILE__, ret);

	printf("File: %s mul.pid = %d\n",__FILE__,(int)mul.pid);
	printf("File: %s mul.oper = %c\n",__FILE__,(char)mul.oper);
        printf("File: %s mul.opr1 = %d\n",__FILE__, (int)mul.opr1);
        printf("File: %s mul.opr2 = %d\n",__FILE__, (int)mul.opr2);

        res =mul.opr1 * mul.opr2;

        printf("File: %s res = %d\n",__FILE__, res);

        byt = write(wfd, &res, sizeof(int));
        printf("File: %s Wrote %d bytes\n", __FILE__, byt);
//	kill(getppid(),SIGALRM);	
}
