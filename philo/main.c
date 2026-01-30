/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:23:41 by asay              #+#    #+#             */
/*   Updated: 2026/01/30 20:04:08 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_args(t_main *main, char **argv)
{
    if(is_valid(argv[1]) || is_valid(argv[2]) || is_valid(argv[3]) 
        || is_valid(argv[4]) || is_valid(argv[5]))
    {
        write(2, "Invalid Argument!\n", 19);
        return ;
    }
    main->philo_num = ft_atoi(argv[1]);
    main->die_time = ft_atoi(argv[2]);
    main->eat_time = ft_atoi(argv[3]);
    main->sleep_time = ft_atoi(argv[4]);
    main->all_eat = ft_atoi(argv[5]);

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
    i = 0;
    while(i < main->philo_num)
    {
        pthread_join(main->philos[i].thread, NULL);
        i++;
    }
}

void init_philos(t_main *main)
{
    int i ;
    /*
    philos için şu tarz bi heap düşünülebilir:
    philos (heap):
    +---------+---------+---------+---------+
    | philo 0 | philo 1 | philo 2 | philo 3 |
    +---------+---------+---------+---------+
    */      
    main->philos = malloc((main->philo_num) * sizeof(t_philo)); //her philo için kendi bilgilerini tutacak struct yeri ayırdık.
    if(!main->philos)
        return ;
    i = 0;
    forks(main); 
    while(i < main->philo_num)
    {
        // her philo'nun (thread'in) bazı özellikleri olucak, kaçıncı philo oldukları ya da thread id'leri gibi
        // burada o bilgilerin olduğu struct'ın doldurulması gerek.
        main->philos[i].philo_id = i + 1; //1. philodan numaralandırma başlıyo.  
        main->philos[i].left_fork = &main->forks[i]; 
        main->philos[i].right_fork = &main->forks[(i + 1) % main->philo_num];
        main->philos[i].data = main; //bu sayede tüm philolar main struct'ına erişebilecek
        main->philos[i].eat_num = 0;
        i++;
    }
}    

void  forks(t_main *main)
{
    int i;

    main->forks = malloc((main->philo_num) * sizeof(pthread_mutex_t));
    if(!main->forks)
        return ;
    i = 0;
    while(i < main->philo_num)
    {
        pthread_mutex_init(&main->forks[i], NULL);
        i++;
    }
}
 
int main(int argc, char **argv)
{
    if(argc == 6)
    {
        t_main main;

        if(ft_atoi(argv[1]) == -1 || ft_atoi(argv[2]) == -1 
            || ft_atoi(argv[3])  == -1|| ft_atoi(argv[4])  == -1 || ft_atoi(argv[5])  == -1)
        	return 0;
        init_args(&main, argv);
        init_philos(&main);
        main.start = convert_time();
        printf("%ld\n", main.start);
        threads(&main);
        return 0;    
    }
    else 
        write(2, "Wrong number of arguments!\n", 28);
    return(0);
}
