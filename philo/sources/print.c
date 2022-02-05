/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 09:51:16 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/05 13:40:09 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_act(t_philo *p)
{
	long long	current_time;

	current_time = (timecode_in_ms() - p->cont->start_time);
	pthread_mutex_lock(&p->cont->print_mutex);
	if (p->cont->simulation == OVER)
	{
		pthread_mutex_unlock(&p->cont->print_mutex);
		return ;
	}
	if (p->act == pondering)
		printf("%lld philo #%d is thinking\n", \
		(timecode_in_ms() - p->cont->start_time), p->id);
	else if (p->act == binging)
	{
		printf("%lld philo %d has taken a fork\n", current_time, p->id);
		printf("%lld philo %d has taken a fork\n", current_time, p->id);
		printf("%lld philo %d is eating\n", current_time, p->id);
	}
	else if (p->act == dreaming)
		printf("%lld philo %d is sleeping\n", current_time, p->id);
	else if (p->act == dead)
	{
		printf("%lld philo #%d died\n", current_time, p->id);
		p->cont->simulation = OVER;
	}
	pthread_mutex_unlock(&p->cont->print_mutex);
}
