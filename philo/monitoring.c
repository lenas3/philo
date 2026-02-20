/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:11:36 by asay              #+#    #+#             */
/*   Updated: 2026/02/20 13:29:20 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int death_ctrl(t_main *main, t_philo *ptr)
{
    long past_time;

    pthread_mutex_lock(&main->meal_mutex);
    past_time = convert_time() - ptr->last_meal;
    pthread_mutex_unlock(&main->meal_mutex);
    if(past_time >= main->die_time) 
            return 1;
    return 0;
}

int eat_count_ctrl(t_main *main)
{
    pthread_mutex_lock(&main->meal_mutex);
    if(main->all_eat == main->philo_num)
    {
        pthread_mutex_unlock(&main->meal_mutex);
        return 1;
    }   
    pthread_mutex_unlock(&main->meal_mutex);
    return 0;
}

void *monitor_routine(void *arg)
{
    t_main *main;
    int i;
    
    main = (t_main *)arg;
    while(1)
    {
        i = 0;  
        while(i < main->philo_num)
        {
            if(death_ctrl(main, &main->philos[i])) //to be or not to be?
            {
                pthread_mutex_lock(&main->dead_mutex);
                main->rudead = 1;
                pthread_mutex_unlock(&main->dead_mutex);
                pthread_mutex_lock(&main->write_mutex);
                printf("%ld\t%d died\n", convert_time() - main->start, main->philos[i].philo_id);
                pthread_mutex_unlock(&main->write_mutex);
                return NULL;
            }
            if(eat_count_ctrl(main))
            {
                pthread_mutex_lock(&main->dead_mutex);
                main->rudead = 1;
                pthread_mutex_unlock(&main->dead_mutex);                
                return NULL;
            }
            i++;
        }
        usleep(1000);
    }
    return NULL;
}
