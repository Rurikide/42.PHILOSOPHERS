/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:21:25 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/02 18:29:52 by tshimoda         ###   ########.fr       */
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
	if (bool_is_dead(philo) == true)
	{
		print_act(philo, 1);
		return ;
	}
	if (philo->cont->queue[0] == philo->id)
	{
		if (bool_is_dead(philo) == true)
		{
			print_act(philo, 1);
			return ;
		}
		if (philo->lefty->fork_state == there && philo->righty->fork_state == there)
		{
			pthread_mutex_lock(&philo->lefty->fork_mutex);
			philo->lefty->fork_state = taken;

			pthread_mutex_lock(&philo->righty->fork_mutex);
			philo->righty->fork_state = taken;

			print_act(philo, 1);
			
			philo->act = binging;
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
	return ;
}
void	print_act(t_philo *philo, int mode)
{
	pthread_mutex_lock(&philo->cont->print_mutex);
	if (mode == 0 && philo->cont->simulation != OVER)
		printf("%lld philo #%d has taken a fork\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
	else if (mode == 1 && philo->cont->simulation == OVER)
	{
		pthread_mutex_unlock(&philo->cont->print_mutex);
		return ;
	}
	if (mode == 1 && philo->act == pondering)
		printf("%lld philo #%d is thinking\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
	else if (mode == 1 && philo->act == binging)
	{
		printf("%lld philo #%d has taken a fork\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
		printf("%lld philo #%d has taken a fork\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
		printf("%lld philo #%d is eating\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
	}
	else if (mode == 1 && philo->act == dreaming)
		printf("%lld philo #%d is sleeping\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
	else if (mode == 1 && philo->act == dead)
	{
		printf("%lld philo #%d has died\n", (timecode_in_ms() - philo->cont->start_time), philo->id);
		philo->cont->simulation = OVER;
	}
	// if (philo->act != dead)
	// {
	// 	pthread_mutex_unlock(&philo->cont->print_mutex);
	// 	return ;
	// }
	pthread_mutex_unlock(&philo->cont->print_mutex);
}

void act_fall_asleep(t_philo *philo)
{
	if (bool_is_dead(philo) == true)
	{
		print_act(philo, 1);
		return ;
	}
	print_act(philo, 1);
	bool_usleep(philo->cont->param->tt_sleep, philo);
	philo->act = dreaming;
}

void act_wake_up(t_philo *philo)
{
	if (bool_is_dead(philo) == true)
	{
		print_act(philo, 1);
		return ;
	}
	print_act(philo, 1);
	philo->act = pondering;
}

void	*routine(void *cont_philo)
{
	t_philo	*philo;

	philo = (t_philo *)cont_philo;

	while (philo->cont->simulation != OVER)
	{
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
	init_pthreads(&cont);
	end_simulation(&cont);
	return (0);
}
