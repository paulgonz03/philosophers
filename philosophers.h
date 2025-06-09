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
    int t_die;
    int t_eat;
    int t_sleep;
    int must_eat;
    int count_eat;
    long long last_time_eat;
    long long start_time;
    pthread_mutex_t *fork[2];
    pthread_mutex_t *print_mutex;
    int *finished;
    pthread_mutex_t *finished_mutex;
} t_philo;

int check_arguments(int argc, char **argv);


#endif