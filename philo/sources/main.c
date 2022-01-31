/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:21:25 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/30 19:55:12 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	check_forks(t_philo *philo)
{
	if (philo->lefty->fork_state == there && philo->righty->fork_state == there)
	{
		printf("Hello\n");
		usleep(1000000);
		printf("Bye\n");
	}
}

void	*routine(void *cont_philo)
{
	t_philo	*philo;

	philo = (t_philo *)cont_philo;
	check_forks(philo);
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
