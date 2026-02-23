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

int is_digit(char *str)
{
    int i;

    i = 0;
    if(!str[i])
        return 0; 
    if(str[i] == '+')
        i++;
    while(str[i])
    {
        if(str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

int arg_check(int argc, char **argv, t_main *main)
{
    int i;

    i = 1;
    if(argc != 6 && argc != 5)
    {
        printf("Error, Wrong number of arguments!\n");
        return 0;
    }
    while(argv[i])
    {
        if(!is_digit(argv[i]))
        {
            printf("Error, Invalid argument!\n");
            return 0;
        }
        i++;
    }
    if(init_args(main, argv) == 1)
    {
        printf("Error, Invalid argument!\n");
        return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    t_main main;

    if(arg_check(argc, argv, &main) == 0)
        return 0;
    init_forks(&main);
    init_philos(&main);
    main.rudead = 0;
    main.ac = argc;
    main.start = convert_time();
    threads(&main);
    return(0);
}
