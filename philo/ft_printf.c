#include "philosophers.h"

void ft_printf(t_philo *philo, char *message)
{
    pthread_mutex_lock(philo->printf);
    pthread_mutex_lock(philo->finished);
    if (*philo->died)
        printf("%lld %d %s\n", get_time() - philo->start_time, philo->id, message);
    pthread_mutex_unlock(philo->finished);   
    pthread_mutex_unlock(philo->printf);
}
