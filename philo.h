#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stddef.h>
#include <unistd.h>

// Structure représentant un philosophe
typedef struct s_global {
    int number_of_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long max_meal;
    long the_start; 
    int have_to_stop;
    pthread_t *threads;
    pthread_mutex_t enable_writing;
    pthread_mutex_t the_dead;
    pthread_mutex_t *mut;
    pthread_mutex_t			finish;
    pthread_mutex_t			last_meal_enable;
    long all_finish_philo;

} t_global;

typedef struct s_philo {
    int id;
    long last_meal_time;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t thread_death_id;
    t_global *global_info;
    long number_meal_eat;
    int finish_philo;
} t_philo;

typedef struct s_all {
    t_philo *philosophers;
    t_global global;
} t_all;

// Ici, je suppose que vous avez une fonction qui renvoie le temps actuel en ms
long actual_time(void);

// Et une fonction pour "dormir"
void ft_usleep(long time);
void	write_status(char *str, t_philo *philo);
void *is_dead(void *arg);

int	check_death(t_philo *philo, int i);
void print_single_philo(t_philo *philo);
void print_all_philos(t_all *allo);

void* philosopher_routine(void *arg);

void	ft_putstr_fd(char *s, int fd);

#endif // PHILO_H
