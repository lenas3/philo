/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:33:41 by asay              #+#    #+#             */
/*   Updated: 2026/02/01 20:32:12 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long convert_time(void)
{
    struct timeval time;
    long total_ms;

    total_ms = 0;
    gettimeofday(&time, NULL); //NULL yazılmazsa tz yani timezone yazılması gerekir.
    total_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000); 
    return (total_ms);
}

int death_ctrl(t_main *main, t_philo *ptr)
{
    pthread_mutex_lock(main->som1died);
    if(convert_time()- ptr->last_meal >= main->die_time)
        return 0;

    if(!main->rudead)
    {
        main->rudead = 1;
        printf("%ld \t%d died.\n", convert_time() - main->start, ptr->philo_id);
        pthread_mutex_unlock(main->som1died);
        return 1;
    }
    pthread_mutex_unlock(main->som1died);
    return 0;
}

/* routine void * alır çünkü thread'ler tarafından çağrıldığında 
hangi türde bir değişken ile çağrılacağını bilmez. */
void *routine(void *arg)
{
    t_philo *ptr;
    t_main  *main;

    ptr = (t_philo *)arg;
    main = ptr->data;
    if(main->philo_num == 1)
    {
        pthread_mutex_lock(ptr->left_fork);
        printf("%ld 1 has taken a fork.\n", (convert_time() - main->start));
        while((convert_time() - main->start) < main->die_time)
            usleep(100);
        printf("%ld 1 died.\n", (convert_time() - main->start));
        pthread_mutex_unlock(ptr->left_fork);
        return ((void *)0);
    }
    if(main->philo_num % 2 == 0)
        usleep(100);
        
    while(1)
    {   
        
        pthread_mutex_lock(ptr->left_fork);
        printf("%ld \t%d has taken a fork.\n", (convert_time() - main->start), ptr->philo_id);
        pthread_mutex_lock(ptr->right_fork);
        printf("%ld \t%d has taken a fork.\n", (convert_time() - main->start), ptr->philo_id);
        printf("%ld \t%d is eating.\n", (convert_time() - main->start), ptr->philo_id);
        usleep(main->eat_time * 1000);
        ptr->last_meal = convert_time();
        pthread_mutex_unlock(ptr->left_fork);
        pthread_mutex_unlock(ptr->right_fork); 
        printf("%ld \t%d is sleeping.\n", (convert_time() - main->start), ptr->philo_id);
        usleep(main->sleep_time * 1000);
        printf("%ld \t%d is thinking.\n", (convert_time() - main->start), ptr->philo_id); 
    }
    return NULL;
}

void *monitor_routine(void *arg)
{
    t_main *main;
    int i;
    
    main = (t_main *)arg;
    while(!main->rudead)
    {
        i = 0;
        while(i < main->philo_num)
        {
            if(death_ctrl(main, &main->philos[i]))
               return NULL;
            i++;
        }
        usleep(500);
    }
    return NULL;
}
