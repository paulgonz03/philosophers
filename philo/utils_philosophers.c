#include "philosophers.h"

int	ft_atoi(char *str)
{
	long	res;
	int		sign;

	sign = 1;
	res = 0;
	if (!str)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if (res * sign > INT_MAX || res * sign < INT_MIN)
			return (0);
		str++;
	}
	return ((int)(res * sign));
}

long long	get_time(void)
{
	struct timeval	timev;

	gettimeofday(&timev, NULL);
	return ((timev.tv_sec * 1000LL) + (timev.tv_usec / 1000LL));
}

void	free_struct(t_philo *philo, pthread_t *threads, int n)
{
	int				i;
	pthread_mutex_t	*forks_base;

	if (!philo)
		return ;
	forks_base = philo[0].fork[0];
	i = -1;
	while (++i < n)
		pthread_mutex_destroy(philo[i].fork[0]);
	pthread_mutex_destroy(philo[0].printf);
	pthread_mutex_destroy(philo[0].finished);
	free(forks_base);
	free(philo[0].printf);
	free(philo[0].finished);
	free(philo[0].died);
	free(philo[0].all_eat);
	free(threads);
	free(philo);
}

int	ft_usleep(long long time, t_philo *philo)
{
    long long	time_wait;
    long long	time_finished;
    long long	time_ms;
    int			died;

    time_ms = time / 1000;
    time_wait = get_time();
    time_finished = time_wait + time_ms;
    while (time_wait < time_finished)
    {
        pthread_mutex_lock(philo->finished);
        died = *(philo->died);
        pthread_mutex_unlock(philo->finished);
        if (died)
            return (0);
        usleep(50);
        time_wait = get_time();
    }
    return (1);
}