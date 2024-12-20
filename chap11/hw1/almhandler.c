#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void mySignal(int signo, void (*handler)(int))
{
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	if (sigaction(signo, &action, NULL) == -1)
	{
		perror("error");
		exit(1);
		}
}

void alarmHandler(int signo)
{
	printf("Wake up\n");
	exit(0);
}

int main()
{
	mySignal(SIGALRM, alarmHandler);
	alarm(5);
	
	short i = 0;
	while(1)
	{
		sleep(1);
		i++;
		printf("%d second\n", i);
	}
	printf("end\n");
	return 0;
}
