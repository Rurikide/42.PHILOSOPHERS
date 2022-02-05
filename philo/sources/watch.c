/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:20:19 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/05 13:34:51 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_result	bool_is_dead(t_philo *philo)
{
	if (timecode_in_ms() - philo->last_meal >= philo->cont->param->tt_die)
	{
		pthread_mutex_lock(&philo->cont->death_mutex);
		philo->act = dead;
		pthread_mutex_unlock(&philo->cont->death_mutex);
		return (true);
	}
	return (false);
}

t_result	bool_usleep(long long time_param, t_philo *philo)
{
	long long	current_time;

	current_time = timecode_in_ms();
	while (timecode_in_ms() - current_time < time_param)
	{
		if (timecode_in_ms() - philo->last_meal >= philo->cont->param->tt_die)
		{
			pthread_mutex_lock(&philo->cont->death_mutex);
			philo->act = dead;
			print_act(philo);
			pthread_mutex_unlock(&philo->cont->death_mutex);
			pthread_mutex_unlock(&philo->lefty->fork_mutex);
			pthread_mutex_unlock(&philo->righty->fork_mutex);
			philo->lefty->fork_state = there;
			philo->righty->fork_state = there;
			return (true);
		}
		else
			usleep(24);
	}
	return (false);
}
