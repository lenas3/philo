/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:23:41 by asay              #+#    #+#             */
/*   Updated: 2026/02/07 20:21:11 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_args(t_main *main, char **argv)
{
    if(is_valid(argv[1]) || is_valid(argv[2]) || is_valid(argv[3]) 
        || is_valid(argv[4]) || is_valid(argv[5]))
    {
        write(2, "Invalid Argument!\n", 19);
        return 1;
    }
    main->philo_num = ft_atoi(argv[1]);
    main->die_time = ft_atoi(argv[2]);
    main->eat_time = ft_atoi(argv[3]);
    main->sleep_time = ft_atoi(argv[4]);
    main->all_eat = ft_atoi(argv[5]); // [TODO] optional arguement
    return 0;
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
    pthread_create(&main->monitor, NULL, monitor_routine, main);
    pthread_join(main->monitor, NULL);
    i = 0;
    while(i < main->philo_num)
    {
        pthread_join(main->philos[i].thread, NULL);
        i++;
    }
}

int init_philos(t_main *main)
{
    int i ;
    /*
    philos için şu tarz bi heap düşünülebilir:
    philos (heap):
    +---------+---------+---------+---------+
    | philo 0 | philo 1 | philo 2 | philo 3 |
    +---------+---------+---------+---------+
    */
    forks(main);
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

int  forks(t_main *main)
{
    int i;

    main->forks = malloc((main->philo_num) * sizeof(pthread_mutex_t));
    if(!main->forks)
        return 1;
    i = 0;
    while(i < main->philo_num)
    {
        pthread_mutex_init(&main->forks[i], NULL);
        i++;
    }
    main->som1died = malloc(sizeof(pthread_mutex_t));
    if(!main->som1died)
        return 1;
    pthread_mutex_init(main->som1died, NULL);
    return 0;
}
 
int main(int argc, char **argv)
{
    if(argc == 6)
    {
        t_main main;
    
        if(ft_atoi(argv[1]) == -1 || ft_atoi(argv[2]) == -1 
            || ft_atoi(argv[3])  == -1|| ft_atoi(argv[4])  == -1 || ft_atoi(argv[5])  == -1)
        {
            write(2, "Error\nOverflow!\n", 17);
            return 0;
        }
        if(init_args(&main, argv))
            return 0;
        init_philos(&main);
        main.start = convert_time();
        threads(&main);
        // free_all(&main);
        return 0;    
    }
    else 
        write(2, "Wrong number of arguments!\n", 28);
    return(0);
}
