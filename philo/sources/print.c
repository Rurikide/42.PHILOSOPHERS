/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 09:51:16 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/06 13:15:16 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_result	bool_is_full(t_philo *p)
{
	if (p->spag_bowl == p->cont->param->nb_serving)
	{
		p->cont->param->nb_done_eat++;
		return (true);
	}
	return (false);
}

t_result	bool_service_done(t_philo *p)
{
	if (p->cont->param->nb_done_eat == p->cont->param->nb_philo)
	{
		p->cont->simulation = OVER;
		return (true);
	}
	return (false);
}

void	simulation_one(t_container *cont)
{
	long long	current_time;

	current_time = timecode_in_ms() - cont->start_time;
	printf("%lld philo 1 has taken a fork\n", current_time);
	bool_usleep(cont->param->tt_die, cont->philo);
	current_time = timecode_in_ms() - cont->start_time;
	printf("%lld philo 1 died\n", current_time);
	return ;
}

void	print_eat(t_philo *p, long long current_time)
{
	printf("%lld philo %d has taken a fork\n", current_time, p->id);
	printf("%lld philo %d has taken a fork\n", current_time, p->id);
	printf("%lld philo %d is eating\n", current_time, p->id);
}

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
		printf("%lld philo %d is thinking\n", \
		(timecode_in_ms() - p->cont->start_time), p->id);
	else if (p->act == binging)
		print_eat(p, current_time);
	else if (p->act == dreaming)
		printf("%lld philo %d is sleeping\n", current_time, p->id);
	else if (p->act == dead)
	{
		printf("%lld philo %d died\n", current_time, p->id);
		p->cont->simulation = OVER;
	}
	pthread_mutex_unlock(&p->cont->print_mutex);
}
