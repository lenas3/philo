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

pthread_create(&t1, NULL, print_hello, argument); 
-print_hello is the function we assign to the thread. it needs to take void * argument and needs to return void *.
-"argument" is the argument we send to the print_hello function.

------------------------Mutexes----------------------------
there is a struct that comes with #include <pthread.h>;
typedef struct data_s
{
    int num;
    pthread_mutext_t mutex;
}data_t
!!after using the mutex, DO NOT forget to destroy mutexes. 
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


//fork fonksiyonu yanlış.
void create_forks(t_main *ptr)
{
    int i;

    ptr->forks = malloc((ptr->philo_num) * sizeof(pthread_mutex_t));
    i = 0;
    while(i < ptr->philo_num)
    {
        pthread_mutex_init(&ptr->forks[i], NULL);
        i++;
    }
}

void init_philos(t_main *ptr)
{
    int i ;

    ptr->philos = malloc((ptr->philo_num) * sizeof(pthread_t));
    if(!ptr->philos)
        return ;
    i = 0;
    while(i < ptr->philo_num)
    {
        // her philo'nun (thread'in) bazı özellikleri olucak, kaçıncı philo oldukları ya da thread id'leri gibi
        // burada o bilgilerin olduğu struct'ın doldurulması gerekç
        ptr->philos[i].philo_id = i + 1; //1. philodan numaralandırma başlıyo.  
        ptr->philos[i].left_forks = ; 
        ptr->philos[i].right_forks = ; 
        ptr->philos[i].tid = ; 
        pthread_create(&ptr->philos[i].thread,NULL, routine, ptr->philos[i]);
        i++;
    }
}

void *routine(void *ptr)
{
    
}