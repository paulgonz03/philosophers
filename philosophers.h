#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define PHILOS 0
#define DIE 1
#define EAT 2
#define SLEEP 3
#define MUST_EAT 4


typedef struct s_philo
{
    int id;
    int number_of[5];
    pthread_mutex_t *fork[2];
} t_philo;

int check_arguments(int argc, char **argv);


#endif