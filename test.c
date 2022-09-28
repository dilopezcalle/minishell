#include <sys/wait.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	num = 100;

int	main(void)
{
	int	pid = fork();
	if (pid == -1)
		return (1);
	else if (!pid)
	{
		num++;
		printf("hijo: %d\n", num);
		exit(0);
	}
	else
	{
		wait(NULL);
		printf("padre: %d\n", num);
	}
}