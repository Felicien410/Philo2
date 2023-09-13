#include "Includes/philo.h"

int number_of_philosophers = 4;
long time_to_die = 300;
long time_to_eat = 200;
long time_to_sleep = 200;
long max_meal = 2147483647;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void init_philo(t_all *all_data) {
    int i = 0;
    all_data->philosophers = malloc(all_data->global.number_of_philosophers * sizeof(t_philo));
    while (i < all_data->global.number_of_philosophers) {
        all_data->philosophers[i].id = i;
        all_data->philosophers[i].global_info = &all_data->global;
        all_data->philosophers[i].left_fork = &all_data->global.mut[i];
        all_data->philosophers[i].right_fork = &all_data->global.mut[(i + 1) % all_data->global.number_of_philosophers];
        all_data->philosophers[i].number_meal_eat = 0;
        all_data->philosophers[i].finish_philo = 0;
        i++;
    }
    all_data->global.the_start = actual_time();
    all_data->global.number_of_philosophers = number_of_philosophers;
    all_data->global.time_to_die = time_to_die;
    all_data->global.time_to_eat = time_to_eat;
    all_data->global.time_to_sleep = time_to_sleep;
    all_data->global.max_meal = max_meal;
    all_data->global.have_to_stop = 0;
    all_data->global.all_finish_philo = 0;
}

void	write_status(char *str, t_philo *philo)
{
	long int		time;

	time = -1;
	time = actual_time() - philo->global_info->the_start;
	if (time >= 0 && time <= 2147483647 && !check_death(philo, 0))
	{
		printf("%ld ", time);
		printf("%d %s", philo->id, str);
	}
}

void init_threads(t_all *all_data) {
    int i = 0;
    all_data->global.threads = (pthread_t *)malloc(all_data->global.number_of_philosophers * sizeof(pthread_t));
    while (i < all_data->global.number_of_philosophers) {
        pthread_create(&all_data->global.threads[i], NULL, philosopher_routine, &all_data->philosophers[i]);
        i++;
    }
    i = 0;
    //ft_putstr_fd("iCI\n",2);

    while (i < all_data->global.number_of_philosophers) {
        pthread_join(all_data->global.threads[i], NULL);
        i++;
    }
    free(all_data->global.threads);
}

void init_mut(t_all *all_data) {
    int i;

    i = 0;
    while (i < number_of_philosophers) {
        pthread_mutex_init(&(all_data->global.mut[i]), NULL);
        i++;
    }
    pthread_mutex_init(&all_data->global.enable_writing, NULL);
    pthread_mutex_init(&all_data->global.the_dead, NULL);
    pthread_mutex_init(&all_data->global.finish, NULL);
    pthread_mutex_init(&all_data->global.last_meal_enable, NULL);
}

void free_destroy (t_all *all_data)
{
    int i;
    
    i = 0;
    while (i < number_of_philosophers) {
        pthread_mutex_destroy(&(all_data->global.mut[i]));

        i++;
    }
}

int main() {
    t_all all_data;
    int i;

    all_data.global.mut = (pthread_mutex_t *)malloc(number_of_philosophers * sizeof(pthread_mutex_t));
    all_data.global.number_of_philosophers = number_of_philosophers;
    init_mut(&all_data);
    init_philo(&all_data);
    init_threads(&all_data);
   i = 0;
   while (i < all_data.global.number_of_philosophers) {
      pthread_mutex_destroy(&all_data.global.mut[i]);
        i++;
    }
    free(all_data.philosophers);
    free(all_data.global.mut);
}

