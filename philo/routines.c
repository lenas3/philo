/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:11:36 by asay              #+#    #+#             */
/*   Updated: 2026/02/15 21:11:38 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int death_ctrl_5(t_main *main, t_philo *ptr)
{
    long past_time;

    pthread_mutex_lock(&main->meal_mutex);
    past_time = convert_time() - ptr->last_meal;
    pthread_mutex_unlock(&main->meal_mutex);
    if(past_time >= main->die_time)
        return 1;
    return 0;
}

int death_ctrl_6(t_main *main, t_philo *ptr)
{
    long past_time;

    pthread_mutex_lock(&main->meal_mutex);
    past_time = convert_time() - ptr->last_meal;
    pthread_mutex_unlock(&main->meal_mutex);
    if(past_time >= main->die_time || main->all_eat >= main->eat_time)
        return 1;
    return 0;
}

void *monitor_routine_5(void *arg)
{
    t_main *main;
    int i;
    
    main = (t_main *)arg;
    while(1)
    {
        i = 0;
        while(i < main->philo_num)
        {
            pthread_mutex_lock(&main->dead_mutex);
            if(!main->rudead && death_ctrl_5(main, &main->philos[i]))
            {
                main->rudead = 1;
                pthread_mutex_lock(&main->write_mutex);
                printf("%ld \t%d died.\n", elapsed_time(main), main->philos[i].philo_id);
                pthread_mutex_unlock(&main->write_mutex);
                pthread_mutex_unlock(&main->dead_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&main->dead_mutex);
            i++;
        }
        usleep(1000);
    }
    return NULL;
}

void *monitor_routine_6(void *arg)
{
    t_main *main;
    int i;
    
    main = (t_main *)arg;
    while(1)
    {
        i = 0;
        while(i < main->philo_num)
        {
            pthread_mutex_lock(&main->dead_mutex);
            if(!main->rudead && death_ctrl_6(main, &main->philos[i]))
            {
                main->rudead = 1;
                pthread_mutex_lock(&main->write_mutex);
                printf("%ld \t%d died.\n", elapsed_time(main), main->philos[i].philo_id);
                pthread_mutex_unlock(&main->write_mutex);
                pthread_mutex_unlock(&main->dead_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&main->dead_mutex);
            i++;
        }
        usleep(1000);
    }
    return NULL;
}