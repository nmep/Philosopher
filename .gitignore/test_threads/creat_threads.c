#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void*	function_1()
{
	printf("hello\n");
	sleep(3);
	printf("bye\n");
	return (NULL);
}

int	main()
{
	pthread_t t1;
	pthread_t t2;

	if (pthread_create(&t1, NULL, &function_1, NULL) != 0)
		return (2);
	if (pthread_create(&t2, NULL, &function_1, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (2);
	if (pthread_join(t2, NULL) != 0)
		return (2);
}
