#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	x = 0;
pthread_mutex_t mutex;

void*	routine()
{
	int	i = 0;

	pthread_mutex_lock(&mutex);
	while (i++ < 2000000)
	{
		x++;
	}
	pthread_mutex_unlock(&mutex);
	return (NULL);
}

int	main()
{
	pthread_t t1;
	pthread_t t2;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, routine, NULL) != 0)
		return (2);
	if (pthread_create(&t2, NULL, routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (2);
	if (pthread_join(t2, NULL) != 0)
		return (2);
	pthread_mutex_destroy(&mutex);
	printf("x = %d\n", x);
}