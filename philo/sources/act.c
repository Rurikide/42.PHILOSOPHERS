/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 09:25:22 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/03 11:09:47 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	act_check_forks(t_philo *philo)
{
	if (bool_is_dead(philo) == true)
	{
		print_act(philo);
		return ;
	}
	if (philo->cont->queue[0] == philo->id)
	{
		if (philo->lefty->fork_state == there && philo->righty->fork_state == there)
		{
			pthread_mutex_lock(&philo->lefty->fork_mutex);
			philo->lefty->fork_state = taken;
			pthread_mutex_lock(&philo->righty->fork_mutex);
			philo->righty->fork_state = taken;
			philo->act = binging;
			print_act(philo);
			if (philo->cont->param->nb_serving != unavailable)
			{
				philo->spag_bowl++;
			}
			update_queue(philo->cont);
			philo->last_meal = timecode_in_ms();
			if (bool_usleep(philo->cont->param->tt_eat, philo) == true)
				return ;
			pthread_mutex_unlock(&philo->lefty->fork_mutex);
			pthread_mutex_unlock(&philo->righty->fork_mutex);
			philo->lefty->fork_state = there;
			philo->righty->fork_state = there;
		}
	}
	else
		usleep(25);
}

void act_fall_asleep(t_philo *philo)
{
	philo->act = dreaming;
	print_act(philo);
	if (bool_usleep(philo->cont->param->tt_sleep, philo) == true)
	{
		print_act(philo);
		return ;
	}
	if (bool_is_dead(philo) == true)
	{
		print_act(philo);
		return ;
	}
}

void act_wake_up(t_philo *philo)
{
	if (bool_usleep(philo->cont->param->tt_sleep, philo) == true)
	{
		print_act(philo);
		return ;
	}
	// if (bool_is_dead(philo) == true)
	// {
	// 	print_act(philo);
	// 	return ;
	// }
	philo->act = pondering;
	print_act(philo);
}