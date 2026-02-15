/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:49:09 by asay              #+#    #+#             */
/*   Updated: 2026/02/15 20:01:08 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

long elapsed_time(t_main *main)
{
	long elapsed;

	elapsed = convert_time() - main->start;
	return (elapsed);
}

long convert_time(void)
{
    struct timeval time;
    long total_ms;

    total_ms = 0;
    gettimeofday(&time, NULL); //NULL yazılmazsa tz yani timezone yazılması gerekir.
    total_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000); 
    return (total_ms);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	sum;
	int		sign;

	i = 0;
	sum = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	if(is_valid((char *)str))
		return -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10) + (str[i] - '0');
		if ((sign == 1 && sum > 2147483647) || (sign == -1 && sum > 2147483648))
            return(-1);
        i++;
	}
	return (sign * sum);
}

int is_valid(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(!(str[i] >= '0' && str[i] <= '9') && str[i] != ' ')  
            return 1;
        i++;
    }
    return 0;
}


