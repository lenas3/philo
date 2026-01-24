/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:33:41 by asay              #+#    #+#             */
/*   Updated: 2026/01/24 20:48:27 by asay             ###   ########.fr       */
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
    return NULL;
}