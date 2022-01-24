/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:13:55 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/24 11:32:20 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		minus;
    long	nombre;

	i = 0;
	minus = 1;
    nombre = 0;
	while ((9 <= str[i] && str[i] <= 13) || (str[i] == 32))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
    while (str[i] >= '0' && str[i] <= '9')
    {
	    nombre = (nombre * 10) + (str[i] - 48);
	    i++;
    }
	nombre = nombre * minus;
	if (nombre < -2147483648 || nombre > 2147483647)
		return (-1);
	return ((int)nombre);
}

t_bool	bool_isdigit(char *str)
{
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			str++;
		else
			return (false);
	}
	return (true);
}

