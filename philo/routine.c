#include "philosophers.h"

int meel_routine(t_philo *philo)
{
    pthread_mutex_lock(philo->finished);
    if (*(philo->died))
    {
        pthread_mutex_unlock(philo->finished);
        pthread_mutex_unlock(philo->fork[1]);
        pthread_mutex_unlock(philo->fork[0]);
        return (0);
    }
    philo->last_time = get_time();
    pthread_mutex_unlock(philo->finished);
    pthread_mutex_lock(philo->printf);
    if (*(philo->died) == 0)
        printf("%lld %d is eating\n", get_time() - philo->start_time, philo->id);
    pthread_mutex_unlock(philo->printf);
    ft_usleep(philo->t_eat * 1000);
    pthread_mutex_lock(philo->finished);
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->finished);
    return (1);
}

int forks_routine(t_philo *philo)
{
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
    if (!meel_routine(philo))
        return (0);
    pthread_mutex_unlock(philo->fork[0]);
    pthread_mutex_unlock(philo->fork[1]);
    return (1);
}

void sleep_routine(t_philo *philo)
{
    pthread_mutex_lock(philo->printf);
    if (*(philo->died) == 0)
        printf("%lld %d is sleeping\n", get_time() - philo->start_time, philo->id);
    pthread_mutex_unlock(philo->printf);
    ft_usleep(philo->t_sleep * 1000);
}

void thinking_routine(t_philo *philo)
{
    pthread_mutex_lock(philo->printf);
    if (*(philo->died) == 0)
        printf("%lld %d is thinking\n", get_time() - philo->start_time, philo->id);
    pthread_mutex_unlock(philo->printf);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = arg;
    while (1)
    {
        // bloquear y desbloquear mutex
        pthread_mutex_lock(philo->finished);
        pthread_mutex_unlock(philo->finished);
        if (philo->nbr_philo%2 == 0) // gestionar los pares para que los pares coman a la vez y los impares a la vez
            usleep(200);
        pthread_mutex_lock(philo->finished);
        if (*(philo->died) || *(philo->all_eat))
        {
            pthread_mutex_unlock(philo->finished);
            return (NULL);
        }
        pthread_mutex_unlock(philo->finished);
        if (!forks_routine(philo))
            return (NULL);
        sleep_routine(philo);
        thinking_routine(philo);
    }
    return (NULL);
}
