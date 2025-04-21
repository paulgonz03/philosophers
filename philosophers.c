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
    return(1);
}

t_philo insert_data(int argc, char **argv)
{
    pthread_mutex_t *forks = ft_calloc(sizeof(pthread_mutex_t), ft_atoi(argv[1]));

}

void *philosopher_routine(void *arg)
{
    t_philo *philo_struc = arg;
    
}

int main(int argc, char **argv)
{
    int i = 0;

    if (!check_arguments(argc, argv))
        return(printf("Error\n"), 0);
    t_philo *philo = ft_calloc(sizeof(t_philo), ft_atoi(argv[1]));
    while(i)
    {
        philo[i] = insert_data(argc, argv);
        i++;
    }
    pthread_mutex_t *threads = ft_calloc(sizeof(pthread_t), ft_atoi(argv[1]));
    while ()
    {
        pthread_create(&threads[i], NULL, philosopher_routine, (void *)&philo[i]);
        // inicializar los hilos
    }

}