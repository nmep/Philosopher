#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	main()
{
	struct timeval	start;
	struct timeval	end;
	struct timeval	test;
	long int		wall_time;

	gettimeofday(&start, NULL);
	usleep(500);
	gettimeofday(&end, NULL);
	wall_time = (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
	printf("1\n");
	printf("avant gtod %ld\n", start.tv_usec);
	printf("apres gtod %ld\n", end.tv_usec);
	printf("temp gtod %ld\n", wall_time);

}