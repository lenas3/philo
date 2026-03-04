/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:25:22 by asay              #+#    #+#             */
/*   Updated: 2026/02/21 16:09:32 by asay             ###   ########.fr       */
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
    int             must_eat;
    t_philo         *philos; 
    pthread_mutex_t *forks;
    pthread_mutex_t write_mutex;
    pthread_mutex_t dead_mutex;
    pthread_mutex_t meal_mutex;
    long            start;
    int             rudead; 
    pthread_t       monitor;
    int             ac;
    int             full_philos;
      
}t_main;

// main struct'ının philolara erişimi: tüm filozofları yönetmek için
// philo struct'ının main'e erişimi: paylaşılan verileri kullanmak için

int     init_args(t_main *main, char **argv);
int     init_philos(t_main *main);
int     init_forks(t_main *main);
void    thread_create(t_main *main);
void    thread_join(t_main *main);
int	    ft_atoi(const char *str);
void    *routine(void *arg);
long    convert_time(void);
int     death_ctrl(t_main *main);
int     eating(t_main *main, t_philo *ptr);
void    monitoring(t_main *main);
long    elapsed_time(t_main *main);
void    one_philo(t_main *main, t_philo *ptr);
int     thinking(t_main *main, t_philo *ptr);
int     eat_count_ctrl(t_main *main);
int     is_digit(char *str);
int     arg_check(int argc, char **argv, t_main *main);
int     sleeping(t_main *main, t_philo *ptr);
void    sleep_carefully(t_main *main, long start);
int     rudead_checker(t_main *main);
void    printing(t_main *main, int philo_id, char *str);

#endif
