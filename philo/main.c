/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:23:41 by asay              #+#    #+#             */
/*   Updated: 2025/12/20 18:51:59 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    if(argc == 6)
    {
        t_main ptr;

        if(is_valid(argv[1]) || is_valid(argv[2]) || is_valid(argv[3]) 
            || is_valid(argv[4]) || is_valid(argv[5]))
        {
            write(2, "Invalid Argument!\n", 19);
            return 1;
        }
        ptr.philo_num = ft_atoi(argv[1]);
        ptr.die_time = ft_atoi(argv[2]);
        ptr.eat_time = ft_atoi(argv[3]);
        ptr.sleep_time = ft_atoi(argv[4]);
        ptr.eat_all = ft_atoi(argv[5]);
        init_philos(ptr);
    }
    else
        return(write(2, "Wrong number of arguments!\n", 28));
}
