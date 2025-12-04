#include "philosophers.h"

int parser_arguments(int argc, char **argv)
{
    int i;
    int j;

    if (argc < 5 || argc > 6)
        return (0);
    j = 0;
    while (argv[++j])
    {
        i = -1;
        while (argv[j][++i])
            if (argv[j][i] < '0' || argv[j][i] > '9')
                return (0);
    }
    if (!ft_atoi(argv[1]) || !ft_atoi(argv[2]) || !ft_atoi(argv[3]) || !ft_atoi(argv[4]))
        return (0);
    if (argc == 6)
        if (!ft_atoi(argv[5]))
            return (0);
    return (1);
}

int init_mutex(char **argv, t_philo *philo, int n_philos)
{
    int i;
    pthread_mutex_t *m_fork;
    pthread_mutex_t *m_print;
    pthread_mutex_t *m_finish;

    m_print = malloc(1 * sizeof(pthread_mutex_t));
    m_finish = malloc(1 * sizeof(pthread_mutex_t));
    m_fork = malloc((ft_atoi(argv[1])) * sizeof(pthread_mutex_t));
    if (!m_fork)
        return (0);
    i = -1;
    pthread_mutex_init(m_print, NULL);
    pthread_mutex_init(m_finish, NULL);
    while (++i < ft_atoi(argv[1]))
    {
        philo[i].finished = m_finish;
        philo[i].printf = m_print;
        pthread_mutex_init(&m_fork[i], NULL);
        philo[i].fork[0] = &m_fork[i];
        if (i == ft_atoi(argv[1]) - 1) // LAST PHILO
            philo[i].fork[1] = &m_fork[0];
        else
            philo[i].fork[1] = &m_fork[i + 1];
    }
    return (1);
}

t_philo *init_struct(int argc, char **argv, t_philo *philo)
{
    int i;
    int n_philos;
    int *m_dead;
    int *m_all_eat;

    n_philos = ft_atoi(argv[1]);
    philo = malloc(n_philos * sizeof(t_philo));
    if (!philo)
        return (NULL);
    m_dead = malloc(sizeof(int));
    m_all_eat = malloc(sizeof(int));
    if (!m_dead || !m_all_eat)
        return (NULL);
    *m_dead = 0;
    *m_all_eat = 0;
    i = -1;
    while (++i < n_philos)
    {
        philo[i].id = i + 1;
        philo[i].nbr_philo = n_philos;
        philo[i].died = m_dead;
        philo[i].all_eat = m_all_eat;
        philo[i].t_die = ft_atoi(argv[2]);
        philo[i].t_eat = ft_atoi(argv[3]);
        philo[i].t_sleep = ft_atoi(argv[4]);
        philo[i].meals_eaten = 0;
        philo[i].must_eat = -1;
        if (argc == 6)
            philo[i].must_eat = ft_atoi(argv[5]);
    }
    if (!init_mutex(argv, philo, n_philos))
        return (NULL);
    return (philo);
}

int main(int argc, char **argv)
{
    t_philo *philo;
    pthread_t *threads;
    int i;
    long long time;

    i = -1;
    philo = NULL;
    if (!parser_arguments(argc, argv))
        return (printf("parser_arguments error\n"));
    philo = init_struct(argc, argv, philo);
    if (!philo)
        return (printf("init_struct error\n"));
    threads = malloc(ft_atoi(argv[1]) * sizeof(pthread_t));
    time = get_time();
    i = -1;
    pthread_mutex_lock(philo[0].finished);
    while (++i < ft_atoi(argv[1]))
    {
        philo[i].start_time = time;
        philo[i].last_time = time;
        if (pthread_create(&threads[i], NULL, philosopher_routine, (void *)&philo[i]) != 0)
            return (printf("pthread_create error\n"), 0);
    }
    pthread_mutex_unlock(philo[0].finished);
    if (!monitor(philo, argv))
    {
        i = -1;
        while (++i < ft_atoi(argv[1]))
            pthread_join(threads[i], NULL);
        free_struct(philo, threads, ft_atoi(argv[1]));
        return (0);
    }
}
