#include "philosophers.h"

int	parser_arguments(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (0);
	j = 0;
	while (argv[++j])
	{
		i = -1;
		while (argv[j][++i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				return (0);
		}
	}
	if (!ft_atoi(argv[1]) || !ft_atoi(argv[2]) || !ft_atoi(argv[3])
		|| !ft_atoi(argv[4]))
		return (0);
	if (argc == 6 && !ft_atoi(argv[5]))
		return (0);
	return (1);
}

int	check_philo_death(t_philo *philo, int i)
{
	int			t_die;
	long long	now;
	long long	last;

	pthread_mutex_lock(philo[i].finished);
	last = philo[i].last_time;
	t_die = philo[i].t_die;
	pthread_mutex_unlock(philo[i].finished);
	now = get_time();
	if (now - last >= t_die)
	{
		ft_printf(&philo[i], "died");
		pthread_mutex_lock(philo[i].finished);
		*(philo[i].died) = 1;
		pthread_mutex_unlock(philo[i].finished);
		return (1);
	}
	return (0);
}

int	check_all_finished(t_philo *philo, int i, int *all_finished)
{
	pthread_mutex_lock(philo[i].finished);
	if (*(philo[i].died))
	{
		pthread_mutex_unlock(philo[i].finished);
		return (1);
	}
	if (philo[i].must_eat != -1 && philo[i].meals_eaten < philo[i].must_eat)
		*all_finished = 0;
	pthread_mutex_unlock(philo[i].finished);
	return (0);
}

void	monitor(t_philo *philo, char **argv)
{
	int	i;
	int	nbr;
	int	all_finished;

	nbr = ft_atoi(argv[1]);
	while (1)
	{
		i = -1;
		all_finished = 1;
		while (++i < nbr)
		{
			if (check_all_finished(philo, i, &all_finished))
				return ;
			if (check_philo_death(philo, i))
				return ;
		}
		if (all_finished && philo[0].must_eat != -1)
		{
			pthread_mutex_lock(philo[0].finished);
			*(philo[0].all_eat) = 1;
			pthread_mutex_unlock(philo[0].finished);
			return ;
		}
	}
}
