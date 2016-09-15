#define RESULTFIFO "Client_%d_FIFO"
struct client1
{
	pid_t pid;
        char oper;
        int opr1;
        int opr2;
};
struct client4
{
	pid_t pid;
        char mydata[100];
};

