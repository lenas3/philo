/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:23:41 by asay              #+#    #+#             */
/*   Updated: 2026/02/15 19:50:39 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_main main;

    if(argc != 6 && argc != 5)
    {
        write(2, "Wrong number of arguments!\n", 28);
        return 0;
    }
    if(ft_atoi(argv[1]) == -1 || ft_atoi(argv[2]) == -1 
        || ft_atoi(argv[3])  == -1|| ft_atoi(argv[4])  == -1 || ft_atoi(argv[5])  == -1)
    {
        write(2, "Error\nInvalid argument!\n", 24);
        return 0;
    }
    init_args(&main, argv);
    if(argc == 6)
        main.all_eat = ft_atoi(argv[5]);
    init_forks(&main);
    init_philos(&main);
    main.start = convert_time();
    main.rudead = 0;
    threads(&main, argc);
    return(0);
}
