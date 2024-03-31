#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void	*routine()
{
	int	val = (rand() % 6) + 1;
	int	*result = malloc(sizeof(int));
	*result = val;
	printf("%d\n", val);
	printf("%p\n", result);
	return ((void *) result);
}

int	main(int ac, char **av)
{
	int	*res;
	srand(time(NULL));
	pthread_t th;

	if (pthread_create(&th, NULL, routine, NULL) != 0)
		return (1);
	if (pthread_join(th, (void **) &res) != 0)
		return (1);
	printf("%p\n", res);
	printf("Result: %d\n", *res);
	free (res);
}