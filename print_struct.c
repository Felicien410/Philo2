#include"Includes/philo.h"

void print_single_philo(t_philo *philo)
{
    printf("---- Philosopher %d ----\n", philo->id);
    printf("Time to die: %ld\n", philo->global_info->time_to_die);
    printf("Time to eat: %ld\n", philo->global_info->time_to_eat);
    printf("Time to sleep: %ld\n", philo->global_info->time_to_sleep);
    printf("Left fork address: %p\n", philo->left_fork);
    printf("Right fork address: %p\n", philo->right_fork);
    printf("mac meal %ld", philo->global_info->max_meal);
    printf("\n");
}

void print_all_philos(t_all *allo) {
    for (int i = 0; i < allo->global.number_of_philosophers; i++) {
        print_single_philo(&allo->philosophers[i]);
    }
}