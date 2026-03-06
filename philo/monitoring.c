/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:11:36 by asay              #+#    #+#             */
/*   Updated: 2026/03/06 12:40:44 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int death_ctrl(t_main *main)
{
    int i;
    long past_time;

    i = 0;
    while(i < main->philo_num)
    {
        pthread_mutex_lock(&main->meal_mutex);
        past_time = convert_time() - main->philos[i].last_meal;
        pthread_mutex_unlock(&main->meal_mutex);
        if(past_time > main->die_time)
        {
            pthread_mutex_lock(&main->dead_mutex);
            if(main->rudead == 1)
            {
                pthread_mutex_unlock(&main->dead_mutex);
                return 1;
            }
            main->rudead = 1;
            pthread_mutex_unlock(&main->dead_mutex);
            pthread_mutex_lock(&main->write_mutex);
            printf("%ld\t%d died.\n", elapsed_time(main), main->philos[i].philo_id);
            pthread_mutex_unlock(&main->write_mutex);
            return 1;
        }
        i++;
    }
    return 0;
}

int eat_count_ctrl(t_main *main)
{
    int i;
    int full_philos;

    i = 0;
    full_philos = 0;
    pthread_mutex_lock(&main->meal_mutex);
    if(main->must_eat <= 0)
    {
        pthread_mutex_unlock(&main->meal_mutex);
        return 0;
    }
    pthread_mutex_unlock(&main->meal_mutex);
    while(i < main->philo_num)
    {
        pthread_mutex_lock(&main->meal_mutex);
        if(main->philos[i].eat_num >= main->must_eat)
            full_philos++;
        pthread_mutex_unlock(&main->meal_mutex);
        i++;
    }
    if(full_philos == main->philo_num)
        return 1;
    return 0;
}

void monitoring(t_main *main)
{
    while (1)
    {
        if (death_ctrl(main) == 1)
            return ;
        
        if (eat_count_ctrl(main) == 1)
        {
            pthread_mutex_lock(&main->dead_mutex);
            main->rudead = 1;
            pthread_mutex_unlock(&main->dead_mutex);
            return;
        }
        usleep(1000);
    }
}
