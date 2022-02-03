/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:21:25 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/02 20:52:12 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	end_simulation(t_container *cont)
{
	int i;

	i = 0;
	while (i < cont->param->nb_philo)
	{
		pthread_mutex_destroy(&cont->forks[i].fork_mutex);
		i++;
	}
	pthread_mutex_destroy(&cont->death_mutex);
	pthread_mutex_destroy(&cont->print_mutex);
	free(cont->param);
	free(cont->forks);
	free(cont->philo);
	free(cont->queue);
	return ;
}

void	act_check_forks(t_philo *philo)
{
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
			philo->spag_bowl++;
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
	if (bool_is_dead(philo) == true)
	{
		print_act(philo);
		return ;
	}
}
void	print_act(t_philo *philo)
{
	// long long current_time;
	
	// current_time = timecode_in_ms();
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
		printf("%lld philo #%d has taken a fork\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
		printf("%lld philo #%d has taken a fork\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
		printf("%lld philo #%d is eating\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
	}
	else if (philo->act == dreaming)
		printf("%lld philo #%d is sleeping\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
	else if (philo->act == dead)
	{
		printf("%lld philo #%d has died HERE\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
		philo->cont->simulation = OVER;
	}
	pthread_mutex_unlock(&philo->cont->print_mutex);
}

void act_fall_asleep(t_philo *philo)
{
	// if (bool_is_dead(philo) == true)
	// {
	// 	print_act(philo);
	// 	return ;
	// }
	philo->act = dreaming;
	print_act(philo);
	bool_usleep(philo->cont->param->tt_sleep, philo);
	if (bool_is_dead(philo) == true)
	{
		print_act(philo);
		return ;
	}
}

void act_wake_up(t_philo *philo)
{
	philo->act = pondering;
	print_act(philo);
}

void	*routine(void *cont_philo)
{
	t_philo	*philo;

	philo = (t_philo *)cont_philo;

	while (philo->cont->simulation != OVER)
	{
		if (bool_is_dead(philo) == true)
		{
			print_act(philo);
			return (NULL);
		}
		if (philo->act == pondering)
			act_check_forks(philo);
		else if (philo->act == binging)
			act_fall_asleep(philo);
		else if (philo->act == dreaming)
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
	// IF NB PHILO == 1 !!!
	init_pthreads(&cont);
	end_simulation(&cont);
	return (0);
}
