#include "Includes/philo.h"

int	check_death(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->global_info->the_dead);
	if (i != 0)
		philo->global_info->have_to_stop = i;
	if (philo->global_info->have_to_stop == 1)
	{
		pthread_mutex_unlock(&philo->global_info->the_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->global_info->the_dead);
	return (0);
}

void *is_dead(void *arg)
{
    t_philo *philo = (t_philo*)arg;
    ft_usleep(philo->global_info->time_to_die + 1);
    pthread_mutex_lock(&philo->global_info->last_meal_enable);
    pthread_mutex_lock(&philo->global_info->finish);
    //printf("THREAD DEAAD %d\n", philo->id);
    //printf("actual_time -> %ld\nphilo last meal >= %ld\ntime to die: %ld\n", actual_time(), philo->last_meal_time, philo->global_info->time_to_die );
    //printf ("actual time - last meal = %ld\n" , actual_time()- philo->last_meal_time);
    if (!check_death(philo, 0) && !philo->finish_philo && 
        (actual_time() - philo->last_meal_time) >= philo->global_info->time_to_die) 
    {
        pthread_mutex_unlock(&philo->global_info->last_meal_enable);
        pthread_mutex_unlock(&philo->global_info->finish);
        pthread_mutex_lock(&philo->global_info->enable_writing);
        write_status("died", philo);
        pthread_mutex_unlock(&philo->global_info->enable_writing);
        check_death(philo, 1);
    }
    pthread_mutex_unlock(&philo->global_info->last_meal_enable);
    pthread_mutex_unlock(&philo->global_info->finish);
    pthread_exit(NULL);
}


void philosopher_routine_the_end(t_philo *philo)
{
    struct timeval current_time;
    
    gettimeofday(&current_time, NULL);
    pthread_mutex_lock(&philo->global_info->enable_writing);
    write_status("is sleeping\n", philo);
    pthread_mutex_unlock(&philo->global_info->enable_writing);

    ft_usleep(philo->global_info->time_to_sleep);

    gettimeofday(&current_time, NULL);

    pthread_mutex_lock(&philo->global_info->enable_writing);
    write_status("is thinking\n", philo);
    pthread_mutex_unlock(&philo->global_info->enable_writing);
  
}

void philosopher_routine_start(t_philo *philo)
{
    struct timeval current_time;

    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(&philo->global_info->enable_writing);
    write_status("has taken a fork\n", philo);
    pthread_mutex_unlock(&philo->global_info->enable_writing);
    if (!philo->right_fork)
    {
        ft_putstr_fd("\n\n AHHHHHHHHHHHHH \n\n ", 2);
        pthread_mutex_unlock(philo->left_fork);
        ft_usleep(philo->global_info->time_to_die * 2);
        //return NULL;
    }
    pthread_mutex_lock(philo->right_fork);
    gettimeofday(&current_time, NULL);
    pthread_mutex_lock(&philo->global_info->enable_writing);
    write_status("has taken a fork\n", philo);
    pthread_mutex_unlock(&philo->global_info->enable_writing);
    gettimeofday(&current_time, NULL);
    pthread_mutex_lock(&philo->global_info->enable_writing);
    write_status("is eating\n", philo);
    pthread_mutex_lock(&philo->global_info->last_meal_enable);

    gettimeofday(&current_time, NULL);

    philo->last_meal_time = actual_time();
    pthread_mutex_unlock(&philo->global_info->last_meal_enable);
    pthread_mutex_unlock(&philo->global_info->enable_writing);
    ft_usleep(philo->global_info->time_to_eat);

    // Libérer lacrim
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    philosopher_routine_the_end(philo);

}


void* philosopher_routine(void *arg)
{
    struct timeval current_time;
    t_philo *philo;
    philo = (t_philo*)arg;
    if (philo->id % 2 == 0) //&& philo->global_info)
        ft_usleep(philo->global_info->time_to_eat / 10);
    while(check_death(philo, 0) == 0)
    {
        pthread_create(&philo->thread_death_id, NULL, is_dead, philo);
        philosopher_routine_start(philo);
        pthread_detach(philo->thread_death_id);
        philo->number_meal_eat = philo->number_meal_eat + 1;
        if(philo->number_meal_eat == philo->global_info->max_meal)
        {
            pthread_mutex_lock(&philo->global_info->finish);
            philo->finish_philo = 1;
            philo->global_info->all_finish_philo++;
            if (philo->global_info->all_finish_philo 
                == philo->global_info->number_of_philosophers)
            {
                pthread_mutex_unlock(&philo->global_info->finish);
                check_death(philo, 2);
            }
            pthread_mutex_unlock(&philo->global_info->finish);
            return(NULL);
        }
    }
      //  pthread_join(philo->thread_death_id, NULL); // Assurez-vous que le thread est bien terminé
    pthread_exit(NULL);
    return (NULL);
}

