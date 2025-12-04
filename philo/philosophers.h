#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
    int id;
    int nbr_philo;
    int t_die;
    int t_eat;
    int t_sleep;
    int must_eat;
    pthread_mutex_t *fork[2];
    pthread_mutex_t *printf;
    pthread_mutex_t *finished;
    int *died;
    long long start_time;
    long long last_time;
} t_philo;

//PHILOSOPHERS.C
int parser_arguments(int argc, char **argv);
int init_mutex(char **argv, t_philo *philo, int n_philos);
t_philo *init_struct(int argc, char **argv, t_philo *philo);
int main(int argc, char **argv);

//UTILS_PHILOSOPHERS.C
int ft_atoi(char *str);
long long get_time(void);
void free_struct(t_philo *philo, pthread_t *threads, int n);
void ft_usleep(long long time);

//ROUTINE.C
void *philosopher_routine(void *arg);

//MONITOR.C
int monitor(t_philo *philo, char **argv);

#endif