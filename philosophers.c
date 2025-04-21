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
    // if(!atoi(1))
    // hcaer atoi para parsear los max y mint int 
    return(1);
}

t_philo *insert_data(int argc, char **argv)
{
    int i = 0;
    int nbr_philos = atoi(argv[1]);

    t_philo *philo = calloc(sizeof(t_philo), nbr_philos);
    pthread_mutex_t *forks = calloc(sizeof(pthread_mutex_t), nbr_philos);
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
        pthread_mutex_lock(philo->fork[0]);
        pthread_mutex_lock(philo->fork[1]);
        printf("philo %d is eating\n", philo->id);
        usleep(philo->t_eat * 1000);
        philo->last_time_eat = get_time();
        pthread_mutex_unlock(philo->fork[0]);
        pthread_mutex_unlock(philo->fork[1]);
        printf("philo %d is sleeping\n", philo->id);
        usleep(philo->t_sleep * 1000);
        printf("philo %d is thinking\n", philo->id);
    }
    return(NULL);
}


int main(int argc, char **argv)
{
    int i = 0;
    long long starting_time = get_time();
    if (!check_arguments(argc, argv))
        return(printf("Error\n"), 0);
    t_philo *philo = insert_data(argc, argv);
    pthread_t *threads = calloc(sizeof(pthread_t), atoi(argv[1]));
    while(i < atoi(argv[1]))
    {
        pthread_create(&threads[i], NULL, philosopher_routine, (void *)&philo[i]);
        i++;
    }
    while (1)
    {
        i = 0;
        while(i < atoi(argv[1]))
        {
            if(philo[i].last_time_eat - starting_time > philo[i].t_die)
            {
                printf("philo %d die\n", philo->id);   
                return(0);
            }
            i++;
        }
    }
}