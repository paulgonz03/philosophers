#include "philosophers.h"

int monitor(t_philo *philo, char **argv)
{
    int i;
    int n;
    long long now;
    long long last;
    int all_finished;
    int t_die;

    n = ft_atoi(argv[1]);
    while (1)
    {
        i = 0;
        all_finished = 1;
        while (i < n)
        {
            pthread_mutex_lock(philo[i].finished);
            if (*(philo[i].died))
            {
                pthread_mutex_unlock(philo[i].finished);
                return (0);
            }
            if (philo[i].must_eat != -1 && philo[i].meals_eaten < philo[i].must_eat)
                all_finished = 0;
            last = philo[i].last_time;
            t_die = philo[i].t_die;
            pthread_mutex_unlock(philo[i].finished);
            now = get_time();
            if (now - last >= t_die)
            {
                ft_printf(philo, "died");
                pthread_mutex_lock(philo[i].finished);
                *(philo[i].died) = 1;
                pthread_mutex_unlock(philo[i].finished);
                return (1);
            }
            i++;
        }
        if (all_finished && philo[0].must_eat != -1)
        {
            pthread_mutex_lock(philo[0].finished);
            *(philo[0].all_eat) = 1;
            pthread_mutex_unlock(philo[0].finished);
            return (0);
        }
        usleep(500);
    }
    return (1);
}
