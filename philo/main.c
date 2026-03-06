/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:23:41 by asay              #+#    #+#             */
/*   Updated: 2026/03/06 16:24:42 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleaning(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->philo_num)
	{
		pthread_mutex_destroy(&main->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&main->write_mutex);
	pthread_mutex_destroy(&main->dead_mutex);
	pthread_mutex_destroy(&main->meal_mutex);
	free(main->philos);
	free(main->forks);
}

int	is_digit(char *str)
{
	int	i;

	i = (0);
	if (!str[i])
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	arg_check(int argc, char **argv, t_main *main)
{
	int	i;

	i = 1;
	if (argc != 6 && argc != 5)
	{
		printf("Error, Wrong number of arguments!\n");
		return (0);
	}
	while (argv[i])
	{
		if (!is_digit(argv[i]))
		{
			printf("Error, Invalid argument!\n");
			return (0);
		}
		i++;
	}
	if (init_args(main, argv) == 1)
	{
		printf("Error, Invalid argument!\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (arg_check(argc, argv, &main) == 0)
		return (0);
	main.start = convert_time();
	init_forks(&main);
	init_philos(&main);
	main.rudead = 0;
	thread_create(&main);
	monitoring(&main);
	thread_join(&main);
	cleaning(&main);
	return (0);
}
