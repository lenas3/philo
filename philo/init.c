/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:04:21 by asay              #+#    #+#             */
/*   Updated: 2026/02/16 21:16:10 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_args(t_main *main, char **argv)
{
    main->philo_num = ft_atoi(argv[1]);
    main->die_time = ft_atoi(argv[2]);
    main->eat_time = ft_atoi(argv[3]);
    main->sleep_time = ft_atoi(argv[4]);
    main->all_eat = -1;
}

void threads(t_main *main)
{
    int i;

    i = 0;
    while(i < main->philo_num)
    {
        pthread_create(&main->philos[i].thread, NULL, routine, (void *)&main->philos[i]);
        i++;
    }
    if(main->philo_num == 1)
    {
        pthread_join(main->philos[0].thread, NULL);
        return ;
    }    
    pthread_create(&main->monitor, NULL, monitor_routine, main);
    i = 0;
    while(i < main->philo_num)
    {
        pthread_join(main->philos[i].thread, NULL);
        i++;
    }
    pthread_join(main->monitor, NULL);
    printf("threads\n");
}

int init_philos(t_main *main)
{
    int i ;

    main->philos = malloc((main->philo_num) * sizeof(t_philo)); //her philo için kendi bilgilerini tutacak struct yeri ayırdık.
    if(!main->philos)
        return 1;
    i = 0;
    while(i < main->philo_num)
    {
        // her philo'nun (thread'in) bazı özellikleri olucak, kaçıncı philo oldukları ya da thread id'leri gibi
        // burada o bilgilerin olduğu struct'ın doldurulması gerek.
        main->philos[i].philo_id = i + 1; //1. philodan numaralandırma başlıyo.  
        main->philos[i].left_fork = &main->forks[i]; 
        main->philos[i].right_fork = &main->forks[(i + 1) % main->philo_num];
        main->philos[i].data = main; //bu sayede tüm philolar main struct'ına erişebilecek
        main->philos[i].eat_num = 0;
        main->philos[i].last_meal = main->start;
        i++;
    }
    main->rudead = 0;
    return 0;
}    

int  init_forks(t_main *main)
{
    int i;

    i = 0;
    main->forks = malloc((main->philo_num) * sizeof(pthread_mutex_t));
    if(!main->forks)
        return 1;
    while(i < main->philo_num)
    {
        pthread_mutex_init(&main->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&main->dead_mutex, NULL);
    pthread_mutex_init(&main->write_mutex, NULL);
    pthread_mutex_init(&main->meal_mutex, NULL);
    return 0;
}
