/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:25:02 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/01 21:51:53 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_result	bool_is_dead(t_philo *philo)
{
	long long current_time;
	
	current_time = timecode_in_ms();
	if (current_time - philo->last_meal >= philo->cont->param->tt_die)
	{
		pthread_mutex_lock(&philo->cont->death_mutex);
		philo->cont->simulation = OVER;
		philo->act = dead;
		printf("%lld philo #%d has died in bool_is_dead()\n", (current_time - philo->cont->start_time), philo->id);
		pthread_mutex_unlock(&philo->cont->death_mutex);
		return (true);
	}
	return (false);
}

t_result	bool_usleep(long long time_param, t_philo *philo)
{
	long long current_time;

	current_time = timecode_in_ms();
	while (timecode_in_ms() - current_time < time_param)
	{
		if (timecode_in_ms() - philo->last_meal >= philo->cont->param->tt_die)
		{
			//printf("%lld philo #%d has died\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
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
