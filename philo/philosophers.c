#include "philosophers.h"

int	parser_arguments(int argc, char **argv)
{
    int	i;
    int	j;

    if (argc < 5 || argc > 6)
        return (0);
    j = 0;
    while (argv[++j])
    {
        i = -1;
        while (argv[j][++i])
        {
            if (argv[j][i] < '0' || argv[j][i] > '9')
                return (0);
        }
    }
    if (!ft_atoi(argv[1]) || !ft_atoi(argv[2]) || !ft_atoi(argv[3])
        || !ft_atoi(argv[4]))
        return (0);
    if (argc == 6 && !ft_atoi(argv[5]))
        return (0);
    return (1);
}

int	init_mutex(char **argv, t_philo *philo, int n_philos)
{
    int				i;
    pthread_mutex_t	*m_fork;
    pthread_mutex_t	*m_print;
    pthread_mutex_t	*m_finish;

    m_print = malloc(1 * sizeof(pthread_mutex_t));
    m_finish = malloc(1 * sizeof(pthread_mutex_t));
    m_fork = malloc((ft_atoi(argv[1])) * sizeof(pthread_mutex_t));
    if (!m_fork || !m_print || !m_finish)
        return (0);
    i = -1;
    pthread_mutex_init(m_print, NULL);
    pthread_mutex_init(m_finish, NULL);
    while (++i < ft_atoi(argv[1]))
    {
        pthread_mutex_init(&m_fork[i], NULL);
        philo[i].fork[0] = &m_fork[i];
        philo[i].fork[1] = &m_fork[(i + 1) % n_philos];
        philo[i].printf = m_print;
        philo[i].finished = m_finish;
    }
    return (1);
}

t_philo	*init_struct(int argc, char **argv, t_philo *philo)
{
    int	i;
    int	*died;
    int	*all_eat;

    philo = malloc(ft_atoi(argv[1]) * sizeof(t_philo));
    if (!philo)
        return (NULL);
    died = malloc(sizeof(int));
    all_eat = malloc(sizeof(int));
    if (!died || !all_eat)
        return (NULL);
    *died = 0;
    *all_eat = 0;
    i = -1;
    while (++i < ft_atoi(argv[1]))
    {
        philo[i].id = i + 1;
        philo[i].nbr_philo = ft_atoi(argv[1]);
        philo[i].meals_eaten = 0;
        philo[i].t_die = ft_atoi(argv[2]);
        philo[i].t_eat = ft_atoi(argv[3]);
        philo[i].t_sleep = ft_atoi(argv[4]);
        philo[i].died = died;
        philo[i].all_eat = all_eat;
        if (argc == 6)
            philo[i].must_eat = ft_atoi(argv[5]);
        else
            philo[i].must_eat = -1;
    }
    if (!init_mutex(argv, philo, ft_atoi(argv[1])))
        return (NULL);
    return (philo);
}

int	main(int argc, char **argv)
{
    t_philo		*philo;
    pthread_t	*threads;
    int			i;
    int			n;
    long long	start;

    philo = NULL;
    if (!parser_arguments(argc, argv))
        return (printf("Error\n"), 1);
    philo = init_struct(argc, argv, philo);
    if (!philo)
        return (1);
    n = ft_atoi(argv[1]);
    threads = malloc(n * sizeof(pthread_t));
    if (!threads)
        return (1);
    pthread_mutex_lock(philo[0].finished);
    i = -1;
    while (++i < n)
        pthread_create(&threads[i], NULL, philosopher_routine, &philo[i]);
    start = get_time();
    i = -1;
    while (++i < n)
    {
        philo[i].start_time = start;
        philo[i].last_time = start;
    }
    pthread_mutex_unlock(philo[0].finished);
    monitor(philo, argv);
    i = -1;
    while (++i < n)
        pthread_join(threads[i], NULL);
    free_struct(philo, threads, n);
    return (0);
}
