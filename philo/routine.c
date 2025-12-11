#include "philosophers.h"

void	thinking_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->finished);
	if (*(philo->died) || *(philo->all_eat))
	{
		pthread_mutex_unlock(philo->finished);
		return ;
	}
	pthread_mutex_unlock(philo->finished);
	ft_printf(philo, "is thinking");
}

void	sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->finished);
	if (*(philo->died) || *(philo->all_eat))
	{
		pthread_mutex_unlock(philo->finished);
		return ;
	}
	pthread_mutex_unlock(philo->finished);
	ft_printf(philo, "is sleeping");
	ft_usleep(philo->t_sleep, philo);
}

void	forks_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[0]);
	ft_printf(philo, "has taken a fork");
	pthread_mutex_lock(philo->fork[1]);
	ft_printf(philo, "has taken a fork");
	ft_printf(philo, "is eating");
	pthread_mutex_lock(philo->finished);
	philo->last_time = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->finished);
	ft_usleep(philo->t_eat, philo);
	pthread_mutex_unlock(philo->fork[0]);
	pthread_mutex_unlock(philo->fork[1]);
	sleep_routine(philo);
	thinking_routine(philo);
}

void	only_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[0]);
	ft_printf(philo, "has taken a fork");
	ft_usleep(philo->t_die, philo);
	pthread_mutex_unlock(philo->fork[0]);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->nbr_philo == 1)
	{
		only_one_philo(philo);
		return (NULL);
	}
	pthread_mutex_lock(philo->finished);
	pthread_mutex_unlock(philo->finished);
	if (philo->id % 2 == 0)
		ft_usleep(100, philo);
	while (1)
	{
		pthread_mutex_lock(philo->finished);
		if (*(philo->died) || *(philo->all_eat))
		{
			pthread_mutex_unlock(philo->finished);
			return (NULL);
		}
		pthread_mutex_unlock(philo->finished);
		forks_routine(philo);
	}
	return (NULL);
}
