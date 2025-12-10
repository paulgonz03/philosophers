#include "philosophers.h"

int meel_routine(t_philo *philo)
{
    ft_printf(philo, "is eating");
    pthread_mutex_lock(philo->finished);
    philo->last_time = get_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->finished);
    if (!ft_usleep(philo->t_eat * 1000, philo))
        return (0);
    return (1);
}

int try_lock_with_check(pthread_mutex_t *mutex, t_philo *philo) // bloquea el hilo hasta que llega el mutex
{
    int died;
    
    while (pthread_mutex_trylock(mutex) != 0)
    {
        pthread_mutex_lock(philo->finished);
        died = *(philo->died);
        pthread_mutex_unlock(philo->finished);
        if (died)
            return (0);
        usleep(100);
    }
    return (1);
}

int forks_routine(t_philo *philo)
{
    int died;
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;

    if (philo->fork[0] < philo->fork[1]) // filosofos cogen el tenedor de la izq al principio
    {
        first_fork = philo->fork[0];
        second_fork = philo->fork[1];
    }
    else
    {
        first_fork = philo->fork[1];
        second_fork = philo->fork[0];
    }

    if (!try_lock_with_check(first_fork, philo))
        return (0);

    ft_printf(philo, "has taken a fork");

    if (!try_lock_with_check(second_fork, philo))
    {
        pthread_mutex_unlock(first_fork);
        return (0);
    }
    pthread_mutex_lock(philo->finished);
    died = *(philo->died);
    pthread_mutex_unlock(philo->finished);
    if (died)
    {
        pthread_mutex_unlock(second_fork);
        pthread_mutex_unlock(first_fork);
        return (0);
    }

    ft_printf(philo, "has taken a fork");

    if (!meel_routine(philo))
    {
        pthread_mutex_unlock(second_fork);
        pthread_mutex_unlock(first_fork);
        return (0);
    }
    pthread_mutex_unlock(second_fork);
    pthread_mutex_unlock(first_fork);
    return (1);
}

void sleep_thinking_routine(t_philo *philo)
{
    ft_printf(philo, "is sleeping");
    ft_usleep(philo->t_sleep * 1000, philo);
    ft_printf(philo, "is thinking");

}


void *philosopher_routine(void *arg)
{
    t_philo *philo;
    int should_stop;

    philo = arg;
    pthread_mutex_lock(philo->finished);
    pthread_mutex_unlock(philo->finished);
    if (philo->id % 2 == 0)
        usleep(1000);
    while (1)
    {
        pthread_mutex_lock(philo->finished);
        should_stop = *(philo->died) || *(philo->all_eat);
        pthread_mutex_unlock(philo->finished);
        if (should_stop)
            return (NULL);
        if (!forks_routine(philo))
            return (NULL);
        sleep_thinking_routine(philo);
        if (philo->nbr_philo % 2 == 1)
            usleep(1000);
    }
    return (NULL);
}
