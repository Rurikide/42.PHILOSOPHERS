/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 09:25:22 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/05 18:24:08 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	act_check_forks(t_philo *p)
{
	if (bool_is_dead(p) == true)
	{
		print_act(p);
		return ;
	}
	if (p->cont->queue[0] == p->id)
	{
		if (p->lefty->fork_state == there && p->righty->fork_state == there)
		{
			pick_up_forks(p);
			print_act(p);
			update_queue(p->cont);
			if (p->cont->param->nb_serving != unavailable)
			{
				if (bool_is_full(p) == true)
					if (bool_service_done(p) == true)
						return ;
			}
			p->last_meal = timecode_in_ms();
			if (bool_usleep(p->cont->param->tt_eat, p) == true)
				return ;
			replace_forks(p);
		}
	}
	usleep(25);
}

void	pick_up_forks(t_philo *p)
{
	pthread_mutex_lock(&p->lefty->fork_mutex);
	p->lefty->fork_state = taken;
	pthread_mutex_lock(&p->righty->fork_mutex);
	p->righty->fork_state = taken;
	p->act = binging;
	p->spag_bowl++;
}

void	replace_forks(t_philo *p)
{
	p->lefty->fork_state = there;
	pthread_mutex_unlock(&p->lefty->fork_mutex);
	p->righty->fork_state = there;
	pthread_mutex_unlock(&p->righty->fork_mutex);
}

void	act_fall_asleep(t_philo *p)
{
	p->act = dreaming;
	print_act(p);
	if (bool_usleep(p->cont->param->tt_sleep, p) == true)
	{
		print_act(p);
		return ;
	}
}

void	act_wake_up(t_philo *p)
{
	if (bool_is_dead(p) == true)
	{
		print_act(p);
		return ;
	}
	p->act = pondering;
	print_act(p);
}
