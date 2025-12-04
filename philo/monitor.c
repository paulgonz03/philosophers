#include "philosophers.h"

int monitor(t_philo *philo, char **argv)
{
    int i;
    
    while (1)
    {
        i = -1;
        while (++i < ft_atoi(argv[1]))
        {
            pthread_mutex_lock(philo[i].finished); // MIRAR SI HA MUERTO
            if (*(philo[i].died) == 1)
            {
                pthread_mutex_unlock(philo[i].finished);
                exit(0);
            }
            pthread_mutex_unlock(philo[i].finished);
            if (get_time() - philo[i].last_time > philo[i].t_die)
            {
                pthread_mutex_lock(philo[i].finished);
                *(philo[i].died) = 1;
                pthread_mutex_unlock(philo[i].finished);
                pthread_mutex_lock(philo[i].printf);
                printf("%lld %d died\n", get_time() - philo[i].start_time, philo[i].id);
                pthread_mutex_unlock(philo[i].printf);
                exit(0);
            }
        }
        usleep(1000);
    }
    return (1);
}
