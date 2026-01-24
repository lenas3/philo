/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asay <asay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 17:49:09 by asay              #+#    #+#             */
/*   Updated: 2026/01/24 18:43:20 by asay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

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
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10) + (str[i] - '0');
		if (sign == 1 && sum > 2147483647)
            return (write(1, "Overflow!\n", 10));
        if (sign == -1 && sum > -2147483648)
            return (write(1, "Overflow!\n", 10));
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
