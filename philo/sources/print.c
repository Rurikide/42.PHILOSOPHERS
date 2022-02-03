/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 09:51:16 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/03 17:52:40 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_act(t_philo *philo)
{
	long long current_time;
	
	current_time = (timecode_in_ms() - philo->cont->start_time);

	pthread_mutex_lock(&philo->cont->print_mutex);
	if (philo->cont->simulation == OVER)
	{
		pthread_mutex_unlock(&philo->cont->print_mutex);
		return ;
	}
	if (philo->act == pondering)
		printf("%lld philo #%d is thinking\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
	else if (philo->act == binging)
	{
		printf("%lld philo #%d has taken a fork\n", current_time, philo->id);
		printf("%lld philo #%d has taken a fork\n", current_time, philo->id);
		printf("%lld philo #%d is eating\n", current_time, philo->id);
	}
	else if (philo->act == dreaming)
		printf("%lld philo #%d is sleeping\n", current_time, philo->id);
	else if (philo->act == dead)
	{
		printf("%lld philo #%d died\n", current_time, philo->id);
		philo->cont->simulation = OVER;
	}
	pthread_mutex_unlock(&philo->cont->print_mutex);
}