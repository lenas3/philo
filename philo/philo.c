/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:33:41 by asay              #+#    #+#             */
/*   Updated: 2025/12/20 19:27:32 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
------------------------Threads----------------------------
-threads don't work at the same speed.

pthread_create(&t1, NULL, print_hello, NULL); 
-print_hello is the function we assign to the thread. it needs to take void * argument and needs to return void *.


------------------------Time-------------------------------
-gets the current time.
int gettimeofday(struct timeval *tv, struct timezone *tz);

1 second = 1 000 000 microseconds.
1 second = 1 000 miliseconds.

struct timeval{
    time_t          tv_sec; //seconds from january 1, 1970
    suseconds_t     tv_usec; //microseconds
};

*/
void init_philos(t_main *ptr)
{
    int i;
    pthread_t *philos;

    philos = malloc((ptr->philo_num) * sizeof(pthread_t));
    
    i = 0;
    while(i < ptr->philo_num)
    {
        pthread_create(&philos[i],NULL, routine, NULL);
        i++;
    }
}
void *routine(void *ptr)
{
    
}