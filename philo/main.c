/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:23:41 by asay              #+#    #+#             */
/*   Updated: 2026/02/21 16:33:27 by asay             ###   ########.fr       */
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
    if(!ft_atoi(argv[1]) || !ft_atoi(argv[2]) || !ft_atoi(argv[3]) || !ft_atoi(argv[4]))
    {
        write(2, "Error\nInvalid argument!\n", 24);
        return 0;
    }
    init_args(&main, argv);
    if(argc == 6)
    {
        if(ft_atoi(argv[5]))
            main.must_eat = ft_atoi(argv[5]);
        else 
            return 0;
    }
    init_forks(&main);
    init_philos(&main);
    main.rudead = 0;
    main.ac = argc;
    main.start = convert_time();
    threads(&main);
    return(0);
}
