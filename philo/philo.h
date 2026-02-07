/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:25:22 by asay              #+#    #+#             */
/*   Updated: 2026/02/07 19:37:06 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
    int             philo_id; //masadaki kacıncı philo oldugunu tutucaz
    int             eat_num; //kaç kez yediklerini sayıyoruz.
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_t       thread;
    struct s_main   *data;
    long            last_meal;
}t_philo;

typedef struct s_main
{
    int             philo_num;
    int             die_time;
    int             eat_time;
    int             sleep_time;
    int             all_eat;
    t_philo         *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t write_mutex;
    pthread_mutex_t dead_mutex;
    int             died;
    long            start;
    int             rudead;
    pthread_mutex_t *som1died;
    pthread_t       monitor;
    
}t_main;

// main struct'ının philolara erişimi: tüm filozofları yönetmek için
// philo struct'ının main'e erişimi: paylaşılan verileri kullanmak için

int     init_args(t_main *main, char **argv);
int     init_philos(t_main *main);
int     forks(t_main *main);
void    threads(t_main *ptr);
int	    ft_atoi(const char *str);
int     is_valid(char *str);
void    *routine(void *arg);
long    convert_time(void);
int     death_ctrl(t_main *main, t_philo *ptr);
void    eating(t_main *main, t_philo *ptr, int i);
void    *monitor_routine(void *arg);

#endif
