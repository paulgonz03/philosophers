#include "philosophers.h"

void forks_routine(t_philo *philo)
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
    ft_usleep(philo->t_eat);

    pthread_mutex_unlock(philo->fork[0]);
    pthread_mutex_unlock(philo->fork[1]);


    ft_printf(philo, "is sleeping");
    ft_usleep(philo->t_sleep);
    ft_printf(philo, "is thinking");
}

void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = arg;
    pthread_mutex_lock(philo->finished);
    pthread_mutex_unlock(philo->finished);
    if (philo->id % 2 == 0)
        ft_usleep(1700);
    while (1)
    {
        pthread_mutex_lock(philo->finished);
        if (*(philo->died) || *(philo->all_eat))
        {
            pthread_mutex_unlock(philo->finished);
            return (NULL); // Termina limpiamente
        }
        pthread_mutex_unlock(philo->finished);

        forks_routine(philo);
    }
    return (NULL);
}
