/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:21:25 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/30 14:19:01 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	create_pthreads(t_container *cont)
{
	pthread_t	*pt;
	int			i;

	i = 0;
	pt = malloc(sizeof(pthread_t) * cont->param->nb_philo);
	while (i < cont->param->nb_philo)
	{
		if (pthread_create(&pt[i], NULL, routine, &cont->philo[i]) != SUCCESS)
			printf("Error create thread\n");
		i++;
		printf("i = %d\n", i);
	}
	while (i > 0)
	{
		i--;
		pthread_join(pt[i], NULL);
	}
	printf("I'm here\n");
}

void    *routine(void *cont_philo)
{
	t_philo	*philo;
	
	philo = (t_philo *)cont_philo;
	
    printf("Hello\n");
    usleep(1000000);
    printf("Bye\n");
    return 0;
}

void	set_parameters(t_container *cont, int ac, char **av)
{
	cont->param = (t_param *)malloc(sizeof(t_param));
	cont->param->nb_philo = ft_atoi(av[1]);
	cont->param->tt_die = ft_atoi(av[2]);
	cont->param->tt_eat = ft_atoi(av[3]);
	cont->param->tt_sleep = ft_atoi(av[4]);
	// printf("nb_philo = %d\n", cont->param->nb_philo);
	// printf("time to die = %ld\n", cont->param->tt_die);
	// printf("time to eat = %ld\n", cont->param->tt_eat);
	// printf("time to sleep = %ld\n", cont->param->tt_sleep);

	if (ac == 6)
	{
		cont->param->nb_serving = ft_atoi(av[5]);
		printf("nb of serving = %d\n", cont->param->nb_serving);
	}
	else 
		cont->param->nb_serving = unavailable;
}

void	init_philosophers(t_container *cont)
{
	int		i;

	i = 0;
	cont->philo = (t_philo *)malloc(sizeof(t_philo) * cont->param->nb_philo);
	while (i < cont->param->nb_philo)
	{
		pthread_mutex_init(&cont->philo[i].fork_mutex, NULL);
		cont->philo[i].cont = cont;
		cont->philo[i].id = i + 1;
		cont->philo[i].spag_bowl = 0;
		cont->philo[i].last_meal = cont->start_time;
		cont->philo[i].act = pondering;
		i++;
	} 
}

void	init_container(t_container *cont, int ac, char **av)
{
	pthread_mutex_init(&cont->print_mutex, NULL);
	pthread_mutex_init(&cont->death_mutex, NULL);
	set_parameters(cont, ac, av);
	init_philosophers(cont);
	cont->queue = malloc(sizeof(int) * cont->param->nb_philo);
	cont->odd_one = cont->param->nb_philo;
	cont->start_time = ft_get_time_in_ms();
	// printf("odd one = %d\n", cont->odd_one);
	printf("start_time = %lld\n", cont->start_time);
}

int main(int ac, char **av)
{
	t_container cont;

	if (ac < 5 || ac > 6)
	{
		printf("Error incorrect input. Enter: ./philo [nb_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] :::optional::: [nb_of_serving]\n");
    	return (0);
	}
	if (bool_is_valid_input(ac, av) == false)
	{
		printf("Error : Parameter containing non-digit character found\n");
		return (0);
	}
	init_container(&cont, ac, av);
	create_pthreads(&cont);
    return (0);
}
