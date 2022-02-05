/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 17:13:55 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/05 14:44:28 by tshimoda         ###   ########.fr       */
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

t_result	bool_isdigit(char *str)
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

t_result	bool_is_valid_input(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (bool_isdigit(av[i]) == true)
			i++;
		else
			return (false);
	}
	return (true);
}

t_result	bool_is_less_than_1(t_container *cont)
{
	if (cont->param->nb_philo < 1 || cont->param->tt_die < 1)
	{
		if (cont->param->nb_philo < 1)
			printf("Error: minimum nb of philo is 1\n");
		if (cont->param->tt_die < 1)
			printf("Error: minimum time_to_die is 1\n");
		return (true);
	}
	if (cont->param->tt_eat < 1 || cont->param->tt_sleep < 1)
	{
		if (cont->param->tt_eat < 1)
			printf("Error: minimum time_to_eat is 1\n");
		if (cont->param->tt_sleep < 1)
			printf("Error: minimum time_to_sleep is 1\n");
		return (true);
	}
	if (cont->param->nb_serving != unavailable)
	{
		if (cont->param->nb_serving < 1)
			printf("Error: minimum nb of serving is 1\n");
		return (true);
	}
	return (false);
}

long long	timecode_in_ms(void)
{
	struct timeval	tv;
	long long		timecode;

	gettimeofday(&tv, NULL);
	timecode = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (timecode);
}
