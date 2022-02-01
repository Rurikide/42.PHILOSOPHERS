/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:25:02 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/01 17:19:59 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_result	bool_usleep(long long ms, t_philo *philo)
{
	long long current_time;

	current_time = timecode_in_ms();
	while (timecode_in_ms() - current_time < ms)
	{
		if (timecode_in_ms() - philo->last_meal >= philo->cont->param->tt_die)
		{
			printf("Philo #%d died\n", philo->id);
			return (true);
		}
		else
			usleep(30);
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
