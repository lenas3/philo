/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:25:22 by asay              #+#    #+#             */
/*   Updated: 2025/12/20 19:04:23 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
    int             philo_id; //masadaki kacıncı philo oldugunu tutucaz
    int             eat_num; //kaç kez yediklerini sayıyoruz.
    pthread_mutex_t *left_forks;
    pthread_mutex_t *right_forks;
    pthread_t       tid;
    pthread_t       thread;
    struct s_main   *data;
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
}t_main;

// main struct'ının philolara erişimi: tüm filozofları yönetmek için
// philo struct'ının main'e erişimi: paylaşılan verileri kullanmak için

void init_philos(t_main *ptr);
int	ft_atoi(const char *str);

#endif
