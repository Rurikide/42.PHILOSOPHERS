/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:21:25 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/01 17:23:23 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_result	act_check_forks(t_philo *philo)
{
	if (philo->cont->queue[0] == philo->id)
	{
		if (philo->lefty->fork_state == there && philo->righty->fork_state == there)
		{
			pthread_mutex_lock(&philo->lefty->fork_mutex);
			philo->lefty->fork_state = taken;
			printf("%lld philo #%d picks left fork\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
			pthread_mutex_lock(&philo->righty->fork_mutex);
			philo->righty->fork_state = taken;
			printf("%lld philo #%d picks right fork\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
			printf("%lld philo #%d is eating\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
			philo->act = binging;
			philo->spag_bowl++;
			update_queue(philo->cont);
			philo->last_meal = timecode_in_ms();
			if (bool_usleep(philo->cont->param->tt_eat, philo))
			{
				pthread_mutex_unlock(&philo->lefty->fork_mutex);
				pthread_mutex_unlock(&philo->righty->fork_mutex);
				philo->lefty->fork_state = there;
				philo->righty->fork_state = there;
				philo->cont->simulation = OVER;
				return (true);
			}
			pthread_mutex_unlock(&philo->lefty->fork_mutex);
			pthread_mutex_unlock(&philo->righty->fork_mutex);
			philo->lefty->fork_state = there;
			philo->righty->fork_state = there;
		}
	}
	return (false);
}

void act_fall_asleep(t_philo *philo)
{

	printf("%lld philo #%d is sleeping\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
	bool_usleep(philo->cont->param->tt_eat, philo);
	philo->act = dreaming;
}

void act_wake_up(t_philo *philo)
{
	printf("%lld philo #%d is thinking\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
	bool_usleep(philo->cont->param->tt_eat, philo);
	philo->act = pondering;
}

void	*routine(void *cont_philo)
{
	t_philo	*philo;

	philo = (t_philo *)cont_philo;

	while (philo->cont->simulation != OVER)
	{
		if (philo->act == pondering)
			if (act_check_forks(philo) == true)
				return (NULL);
		if (philo->act == binging)
			act_fall_asleep(philo);
		if (philo->act == dreaming)
			act_wake_up(philo);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_container	cont;

	if (ac < 5 || ac > 6)
	{
		printf("Error incorrect input. Enter: ./philo [nb_of_philo] [time_to_die] [time_to_eat] [time_to_sleep] :optional: [nb_of_serving]\n");
		return (0);
	}
	if (bool_is_valid_input(ac, av) == false)
	{
		printf("Please enter only positive numerical values/characters.\n");
		return (0);
	}
	init_container(&cont, ac, av);
	init_pthreads(&cont);
	return (0);
}
