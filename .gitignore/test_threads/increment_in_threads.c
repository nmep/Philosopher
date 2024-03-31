#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int	x = 2;

void*	routine1()
{
	x++;
	return (NULL);
}

void*	routine2()
{
	usleep(200);
	printf("x = %d\n", x);
	return (NULL);
}


// les threads se font en meme temps, il doit donc y avoir un attente entre les deux pour 
// que l'incrementation se fasse avant l'affchage
int	main()
{
	pthread_t t1;
	pthread_t t2;

	pthread_create(&t1, NULL, routine1, NULL);
	pthread_create(&t2, NULL, routine2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}