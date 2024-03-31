#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	ft_modif_i(int *i)
{
	*i = 1;
}

void	ft_print_i(int	*arg)
{
	int	*i = arg;
	printf("i = %d\n", *i);
}

int	main()
{
	int	i = 0;
	pthread_t	th;

	ft_modif_i(&i);
	pthread_create(&th, NULL, (void *) &ft_print_i, (void *) &i);
	pthread_join(th, NULL);
	return (0);
}