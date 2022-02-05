/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:10:43 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/05 15:44:27 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	end_simulation(t_container *cont)
{
	int	i;

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
	free(pt);
}

int	set_parameters(t_container *cont, int ac, char **av)
{
	cont->param = (t_param *)malloc(sizeof(t_param));
	cont->param->nb_philo = ft_atoi(av[1]);
	cont->param->tt_die = ft_atoi(av[2]);
	cont->param->tt_eat = ft_atoi(av[3]);
	cont->param->tt_sleep = ft_atoi(av[4]);
	if (cont->param->nb_philo == -1 || cont->param->tt_die == -1 || \
	cont->param->tt_eat == -1 || cont->param->tt_sleep == -1)
		return (err_integer_limits(cont));
	if (ac == 6)
	{
		cont->param->nb_serving = ft_atoi(av[5]);
		if (cont->param->nb_serving == -1)
			return (err_integer_limits(cont));
		cont->param->nb_done_eat = 0;
	}
	else
		cont->param->nb_serving = unavailable;
	return (0);
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
		cont->philo[i].righty = &cont->forks[(i + 1) % cont->param->nb_philo];
		cont->philo[i].cont = cont;
		cont->philo[i].id = i + 1;
		cont->philo[i].spag_bowl = 0;
		cont->philo[i].last_meal = cont->start_time;
		cont->philo[i].act = pondering;
		i++;
	}
}

int	init_container(t_container *cont, int ac, char **av)
{
	if (set_parameters(cont, ac, av) == -1)
		return (-1);
	pthread_mutex_init(&cont->print_mutex, NULL);
	pthread_mutex_init(&cont->death_mutex, NULL);
//	set_parameters(cont, ac, av);
	init_philosophers(cont);
	init_queue(cont);
	cont->simulation = START;
	cont->start_time = timecode_in_ms();
	return (0);
}
