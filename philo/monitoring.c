/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:11:36 by asay              #+#    #+#             */
/*   Updated: 2026/02/16 15:44:07 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int death_ctrl(t_main *main, t_philo *ptr)
{
    long past_time;
    long last_meal_count;
    int all_eat_count;

    pthread_mutex_lock(&main->meal_mutex);
    last_meal_count = ptr->last_meal;
    all_eat_count = main->all_eat;
    pthread_mutex_unlock(&main->meal_mutex);
    past_time = convert_time() - last_meal_count;
    if(main->ac == 6)
    {
        if(past_time >= main->die_time || all_eat_count >= main->eat_time)
            return 1;   
    }
    else if(main->ac == 5)
    {
        if(past_time >= main->die_time)
            return 1;
    }
    return 0;
}

void *monitor_routine(void *arg)
{
    t_main *main;
    int i;
    int is_dead;
    
    main = (t_main *)arg;
    while(1)
    {
        i = 0;
        pthread_mutex_lock(&main->dead_mutex);
        is_dead = main->rudead;
        pthread_mutex_unlock(&main->dead_mutex);
        if(is_dead)
            return NULL;
        while(i < main->philo_num)
        {
            if(!is_dead && death_ctrl(main, &main->philos[i]))
            {
                is_dead = 1;
                pthread_mutex_lock(&main->write_mutex);
                printf("%ld \t%d died.\n", elapsed_time(main), main->philos[i].philo_id);
                pthread_mutex_unlock(&main->write_mutex);
                return NULL;
            }
            i++;
        }
        usleep(1000);
    }
    return NULL;
}
