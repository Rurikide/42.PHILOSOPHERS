/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:21:25 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/06 13:14:59 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
		printf(ARGUMENT);
		return (0);
	}
	if (bool_is_valid_input(ac, av) == false)
	{
		printf("Please enter only positive numerical values/integers.\n");
		return (0);
	}
	if (init_container(&cont, ac, av) == -1)
		return (-1);
	if (bool_is_less_than_1(&cont) == true)
	{
		end_simulation(&cont);
		return (0);
	}
	if (cont.param->nb_philo == 1)
		simulation_one(&cont);
	else
		init_pthreads(&cont);
	end_simulation(&cont);
	return (0);
}
