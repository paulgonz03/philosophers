#include "philosophers.h"

int ft_atoi(char *str)
{
    long res;
    int sign;

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

long long get_time(void)
{
    struct timeval timev;

    gettimeofday(&timev, NULL);
    return ((timev.tv_sec * 1000LL) + (timev.tv_usec / 1000LL));
}

void free_struct(t_philo *philo)
{ // FREE ALL THE MUTEXS
    int i;

    i = 0;
    while (i < philo[i].nbr_philo)
    {
        pthread_mutex_destroy(philo[i].fork[0]);
        pthread_mutex_destroy(philo[i].fork[1]);
        pthread_mutex_destroy(philo[i].printf);
        pthread_mutex_destroy(philo[i].finished);
        i++;
    }
    free(philo);
}
