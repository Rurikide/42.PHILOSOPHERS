/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:10:43 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/01 17:20:45 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	init_pthreads(t_container *cont)
{
	pthread_t	*pt;
	int			i;

	i = 0;
	pt = malloc(sizeof(pthread_t) * cont->param->nb_philo);
	while (i < cont->param->nb_philo)
	{
		if (pthread_create(&pt[i], NULL, routine, &cont->philo[i]) != SUCCESS)
			printf("Error pthread_create\n");
		i++;
	}
	while (i > 0)
	{
		i--;
		pthread_join(pt[i], NULL);
	}
}

void	set_parameters(t_container *cont, int ac, char **av)
{
	cont->param = (t_param *)malloc(sizeof(t_param));
	cont->param->nb_philo = ft_atoi(av[1]);
	cont->param->tt_die = ft_atoi(av[2]);
	cont->param->tt_eat = ft_atoi(av[3]);
	cont->param->tt_sleep = ft_atoi(av[4]);
	if (cont->param->nb_philo < 1 || cont->param->tt_die < 1 || cont->param->tt_eat < 1 || cont->param->tt_sleep < 1)
	{
		printf("minimum value is 1\n");
		exit (0);
	}
	if (ac == 6)
	{
		cont->param->nb_serving = ft_atoi(av[5]);
		if (cont->param->nb_serving < 1)
		{
			printf("minimum value is 1\n");
			exit (0);
		}
	}
	else
		cont->param->nb_serving = unavailable;
}

void	init_philosophers(t_container *cont)
{
	int		i;

	i = 0;
	cont->philo = (t_philo *)malloc(sizeof(t_philo) * cont->param->nb_philo);
	cont->forks = (t_fork *)malloc(sizeof(t_fork) * cont->param->nb_philo);
	while (i < cont->param->nb_philo)
	{
		pthread_mutex_init(&cont->forks[i].fork_mutex, NULL);
		cont->forks[i].fork_state = there;
		cont->philo[i].lefty = &cont->forks[i];
		// ATTENTION IL FAUT PLUS D'UN PHILO
		cont->philo[i].righty = &cont->forks[(i + 1) % cont->param->nb_philo];
		cont->philo[i].cont = cont;
		cont->philo[i].id = i + 1;
		cont->philo[i].spag_bowl = 0;
		cont->philo[i].last_meal = cont->start_time;
		cont->philo[i].act = pondering;
		i++;
	}
}
	// i = 0;
	// while (i < cont->param->nb_philo)
	// {
	// 	printf("lefty = %d\n", cont->philo[i].lefty->fork_state);
	// 	printf("righty = %d\n", cont->philo[i].righty->fork_state);
	// 	i++;
	// }

void	init_container(t_container *cont, int ac, char **av)
{
	pthread_mutex_init(&cont->print_mutex, NULL);
	pthread_mutex_init(&cont->death_mutex, NULL);
	set_parameters(cont, ac, av);
	init_philosophers(cont);
	init_queue(cont);
	cont->simulation = START;
	cont->start_time = timecode_in_ms();
}
