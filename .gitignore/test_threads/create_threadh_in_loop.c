#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	x = 0;
pthread_mutex_t mutex;

void	*function()
{
	int	i = 0;

	pthread_mutex_lock(&mutex);
	while (x < 400000 && i++ < 40000000)
	{
		x++;
	}
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main()
{
	pthread_t	th[4];
	int			i = 0;

	pthread_mutex_init(&mutex, NULL);
	while (i < 4)
	{
		printf("thread %d created\n", i);
		pthread_create(&th[i], NULL, function, NULL);
		// printf("thread %d finished\n", i);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		printf("thread %d started\n", i);
		pthread_join(th[i], NULL);
		printf("thread %d finish\n", i);
		i++;
	}
	printf("x = %d\n", x);
	pthread_mutex_destroy(&mutex);
}