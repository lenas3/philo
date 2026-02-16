/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:33:41 by asay              #+#    #+#             */
/*   Updated: 2026/02/16 21:19:16 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void one_philo(t_main *main, t_philo *ptr)
{
    long start;

    pthread_mutex_lock(ptr->left_fork);
    pthread_mutex_lock(&main->write_mutex);
    printf("%ld\t1 has taken a fork.\n", elapsed_time(main));
    pthread_mutex_unlock(&main->write_mutex);
    pthread_mutex_unlock(ptr->left_fork);
    start = elapsed_time(main);
    while (elapsed_time(main) - start < main->die_time)
        usleep(100);
    pthread_mutex_lock(&main->dead_mutex);
    main->rudead = 1;
    pthread_mutex_unlock(&main->dead_mutex);
    pthread_mutex_lock(&main->write_mutex);
    printf("%ld\t1 died.\n", elapsed_time(main));
    pthread_mutex_unlock(&main->write_mutex);
}

/* routine void * alır çünkü thread'ler tarafından çağrıldığında 
hangi türde bir değişken ile çağrılacağını bilmez. */
void *routine(void *arg)
{
    t_philo *ptr;
    t_main  *main;
    int     i;

    i = 0;
    ptr = (t_philo *)arg;
    main = ptr->data;
    if(main->philo_num == 1)
    {
        one_philo(main, ptr);
        return NULL;
    }
    while(1)
    {
        pthread_mutex_lock(&main->dead_mutex);
        if(main->rudead == 1)
        {
            pthread_mutex_unlock(&main->dead_mutex);
            return NULL ;
        }
        eating(main, ptr);
        pthread_mutex_lock(&main->write_mutex);
        printf("%ld\t%d is sleeping.\n", elapsed_time(main), ptr->philo_id);
        pthread_mutex_unlock(&main->write_mutex);
        usleep(main->sleep_time * 1000);
        thinking(main, ptr);
        i++;
    }
    return NULL;
}

void eating(t_main *main, t_philo *ptr)
{   
    if(ptr->philo_id % 2 == 0)
    {
        pthread_mutex_lock(ptr->right_fork);
        pthread_mutex_lock(&main->write_mutex);
        printf("%ld\t%d has taken a fork.\n", elapsed_time(main), ptr->philo_id);
        pthread_mutex_unlock(&main->write_mutex);
        pthread_mutex_unlock(ptr->right_fork);
        pthread_mutex_lock(ptr->left_fork);
        pthread_mutex_lock(&main->write_mutex);
        printf("%ld\t%d has taken a fork.\n", elapsed_time(main), ptr->philo_id);
        pthread_mutex_unlock(&main->write_mutex);
        pthread_mutex_unlock(ptr->left_fork);
    }
    else
    {
        pthread_mutex_lock(ptr->left_fork);
        pthread_mutex_lock(&main->write_mutex);
        printf("%ld\t%d has taken a fork.\n", elapsed_time(main), ptr->philo_id);
        pthread_mutex_unlock(&main->write_mutex);
        pthread_mutex_unlock(ptr->left_fork);
        pthread_mutex_lock(ptr->right_fork);
        pthread_mutex_lock(&main->write_mutex);
        printf("%ld\t%d has taken a fork.\n", elapsed_time(main), ptr->philo_id);
        pthread_mutex_unlock(&main->write_mutex);
        pthread_mutex_unlock(ptr->left_fork);
    }
    pthread_mutex_lock(&main->write_mutex);
    printf("%ld\t%d is eating.\n", elapsed_time(main), ptr->philo_id);
    pthread_mutex_unlock(&main->write_mutex);
    pthread_mutex_lock(&main->meal_mutex);  
    ptr->last_meal = convert_time();
    pthread_mutex_unlock(&main->meal_mutex);
    usleep(main->eat_time * 1000);
    pthread_mutex_lock(&main->meal_mutex);  
    ptr->eat_num++;
    pthread_mutex_unlock(&main->meal_mutex); 
    pthread_mutex_unlock(ptr->left_fork);
    pthread_mutex_unlock(ptr->right_fork); 
}

void thinking(t_main *main, t_philo *ptr)
{
    pthread_mutex_lock(&main->write_mutex);
    printf("%ld\t%d is thinking.\n", elapsed_time(main), ptr->philo_id);        
    pthread_mutex_unlock(&main->write_mutex);
}