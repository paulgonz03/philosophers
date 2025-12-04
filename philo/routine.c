#include "philosophers.h"

void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = arg;
    while (1)
    {
        pthread_mutex_lock(philo->finished);
        if (*(philo->died))
        {
            pthread_mutex_unlock(philo->finished);
            return (NULL);
        }
        pthread_mutex_unlock(philo->finished);

        pthread_mutex_lock(philo->fork[0]);
        pthread_mutex_lock(philo->printf);
        if (*(philo->died) == 0)
            printf("%lld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
        pthread_mutex_unlock(philo->printf);

        pthread_mutex_lock(philo->fork[1]);
        pthread_mutex_lock(philo->printf);
        if (*(philo->died) == 0)
            printf("%lld %d has taken a fork\n", get_time() - philo->start_time, philo->id);
        pthread_mutex_unlock(philo->printf);

        pthread_mutex_lock(philo->finished);
        if (*(philo->died))
        {
            pthread_mutex_unlock(philo->finished);
            pthread_mutex_unlock(philo->fork[1]);
            pthread_mutex_unlock(philo->fork[0]);
            return (NULL);
        }
        philo->last_time = get_time();
        pthread_mutex_unlock(philo->finished);
        
        pthread_mutex_lock(philo->printf);
        if (*(philo->died) == 0)
            printf("%lld %d is eating\n", get_time() - philo->start_time, philo->id);
        pthread_mutex_unlock(philo->printf);

        ft_usleep(philo->t_eat * 1000);

        pthread_mutex_unlock(philo->fork[0]);
        pthread_mutex_unlock(philo->fork[1]);

        pthread_mutex_lock(philo->printf);
        if (*(philo->died) == 0)
            printf("%lld %d is sleeping\n", get_time() - philo->start_time, philo->id);
        pthread_mutex_unlock(philo->printf);

        ft_usleep(philo->t_sleep * 1000);
        
        pthread_mutex_lock(philo->printf);
        if (*(philo->died) == 0)
            printf("%lld %d is thinking\n", get_time() - philo->start_time, philo->id);
        pthread_mutex_unlock(philo->printf);
    }
    return (NULL);
}
