#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*f1(int *i)
{
	write(1, "je mange\n", 9);
	printf("%d\n", *i);
	return (NULL);
}

void	*f2(int *j)
{
	write(1, "je dors\n", 8);
	printf("%d\n", *j);
	return (NULL);
}

// printf cause un data race car il n'est pas fait pour
// etre utiliser en multithreading
int	main()
{
	pthread_t t1;
	int	i = 1;
	int	j = 2;

	pthread_create(&t1, NULL, &f1, &i);
	pthread_join(t1, NULL);
	usleep(200);
	pthread_create(&t1, &i, &f2, NULL);
	pthread_join(t1, NULL);
	return (0);
}