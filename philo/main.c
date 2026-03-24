/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:23:41 by asay              #+#    #+#             */
/*   Updated: 2026/03/24 18:48:42 by asay             ###   ########.fr       */
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

	i = 0;
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

int	value_ctrl(t_main *main, int argc)
{
	if (main->philo_num < 1 || main->philo_num > 500)
		return (printf("Error: Invalid philosopher count\n"), 0);
	if (main->die_time < 0 || main->eat_time < 0
		|| main->sleep_time < 0)
		return (printf("Error: Negative time values\n"), 0);
	if (argc == 6 && main->must_eat <= 0)
	{
		if (main->must_eat == 0)
			return (0);
		return (printf("Error: Negative meal count\n"), 0);
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
		return (0);
	return (value_ctrl(main, argc));
}

int	main(int argc, char **argv)
{
	t_main	main;

	if (arg_check(argc, argv, &main) == 0)
		return (0);
	main.start = convert_time();
	if (init_forks(&main) == 1)
		return (printf("Error: Malloc failed for forks\n"), 1);
	if (init_philos(&main) == 1)
	{
		free(main.forks);
		return (printf("Error: Malloc failed for philos\n"), 1);
	}
	main.rudead = 0;
	thread_create(&main);
	monitoring(&main);
	thread_join(&main);
	cleaning(&main);
	return (0);
}
