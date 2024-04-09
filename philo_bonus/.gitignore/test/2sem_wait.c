#include <semaphore.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main()
{
	sem_t *sema;
	pid_t	pid1;
	pid_t	pid2;

	sema = sem_open("/sema", O_CREAT, 0644, 2);
	pid1 = fork();
	if (pid1 < 0)
		return (printf("error fork\n"), 2);
	if (pid1 == 0)
	{
		sem_wait(sema);
		sem_wait(sema);
		printf("jai mes fourchettes\n");
		sem_post(sema);
		sem_post(sema);
	}
	else
	{
		printf("parent pid1\n");
	}
	pid2 = fork();
	if (pid2 < 0)
		return (printf("error fork\n"), 2);
	if (pid2 == 0)
	{
		sem_wait(sema);
		sem_wait(sema);
		printf("jai mes fourchettes\n");
		sem_post(sema);
		sem_post(sema);
	}
	else
	{
		printf("parent pid2\n");
	}
	sem_unlink("/sema");
}