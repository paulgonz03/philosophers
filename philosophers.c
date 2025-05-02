#include "philosophers.h"

int check_arguments(int argc, char **argv)
{
    int i;
    int j;

    i = 0;
    j = 1;
    if (argc < 5 || argc > 6)
        return(0);
    while (argv[j])
    {
        i = 0;
        while (argv[j][i])
        {
            if(!(argv[j][i] >= '0' && argv[j][i] <= '9'))
                return(0);
            i++;
        }
        j++;
    }
    if(!atoi(argv[1]) || !atoi(argv[2]) || !atoi(argv[3]) || !atoi(argv[4]))
        return(0);
    if (argc == 6)
        if(!atoi(argv[5]))  
            return(0);
    return(1);
}

t_philo *init_data(int argc, char **argv)
{
    int i = 0;
    int nbr_philos = atoi(argv[1]);

    t_philo *philo = calloc(sizeof(t_philo), nbr_philos);
    if (!philo)
        return (NULL);
    pthread_mutex_t *forks = calloc(sizeof(pthread_mutex_t), nbr_philos);
    if (!forks)
        return (NULL);
    while(i < nbr_philos)
    {
        pthread_mutex_init(&forks[i], NULL);
        philo[i].id = i + 1;
        philo[i].t_die = atoi(argv[2]);
        philo[i].t_eat = atoi(argv[3]);
        philo[i].t_sleep = atoi(argv[4]);
        if (argc == 6)
            philo[i].must_eat = atoi(argv[5]);
        philo[i].fork[0] = &forks[i];
        if (i == nbr_philos - 1)
            philo[i].fork[1] = &forks[0];
        else
            philo[i].fork[1] = &forks[i + 1];
        i++;
    }
    return(philo);
}

long long	get_time(void)
{
    struct timeval	timev;

    gettimeofday(&timev, NULL);
    return ((timev.tv_sec * 1000) + (timev.tv_usec / 1000));
}
void *philosopher_routine(void *arg)
{
    t_philo *philo = arg;

    while(1)
    {
        if (philo->must_eat)
            if (philo->count_eat == philo->must_eat)
                return NULL;
        pthread_mutex_lock(philo->fork[0]);
        printf("%lld ", get_time() - philo->start_time);
        printf("%d has taken a fork\n", philo->id);
        pthread_mutex_lock(philo->fork[1]);
        printf("%lld ", philo->start_time);
        printf("%d has taken a fork\n", philo->id);
        printf("%lld ", get_time() - philo->start_time);
        printf("%d is eating\n", philo->id);
        usleep(philo->t_eat * 1000);
        philo->last_time_eat = get_time();
        philo->count_eat += 1;
        pthread_mutex_unlock(philo->fork[0]);
        pthread_mutex_unlock(philo->fork[1]);
        printf("%lld ", get_time() - philo->start_time);
        printf("%d is sleeping\n", philo->id);
        usleep(philo->t_sleep * 1000);
        printf("%lld ", get_time() - philo->start_time);
        printf("%d is thinking\n", philo->id);
    }
    return(NULL);
}


int main(int argc, char **argv)
{
    int i = 0;
    long long start_time;

    if (!check_arguments(argc, argv))
        return(printf("Error check arguments\n"), 0);
    t_philo *philo = init_data(argc, argv);
    if (!philo)
        return(printf("Error init_data\n"), 0);
    pthread_t *threads = calloc(sizeof(pthread_t), atoi(argv[1]));
    if (!threads)
        return(printf("Error create threads\n"), 0);
    start_time = get_time();
    while(i < atoi(argv[1]))
    {
        philo[i].start_time = start_time;
        philo[i].last_time_eat = start_time;
        if((pthread_create(&threads[i], NULL, philosopher_routine, (void *)&philo[i])) == -1)
            return(printf("Error"), 0);
        i++;
    }
    while (1)
    {
        i = -1;
        while(++i < atoi(argv[1]))
        {
            if(get_time() - philo[i].last_time_eat > philo[i].t_die) 
                return(printf("%lld ", get_time() - philo[i].last_time_eat), printf("%d die\n", philo->id), 0);
        }
    }
}


/* TODO 
-poner bien los printfs - HECHO
-poner el tiempo de cada cosa en el printf
-buen parseo de cada dato - HECHO
-control de errores en cada funcion (check que devuelven) - hecho 
-investigar sobre getitme()
-leer el man de todas las funciones que hemos usado -hecho
-apuntar cuantas veces ha comido cada filo- HECHO
-poner un printf para cada tenedor - hecho
*/