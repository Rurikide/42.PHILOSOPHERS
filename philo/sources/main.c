/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:21:25 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/27 12:17:56 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_result	bool_is_valid_input(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (bool_isdigit(av[i]) == true)
			i++;
		else
			return (false);
	}
	return (true);
}

t_param	*set_parameters(int ac, char **av)
{
	t_param *param;

	param = (t_param *)malloc(sizeof(t_param));
	param->nb_philo = ft_atoi(av[1]);
	param->tt_die = ft_atoi(av[2]);
	param->tt_eat = ft_atoi(av[3]);
	param->tt_sleep = ft_atoi(av[4]);
	printf("nb_philo = %d\n", param->nb_philo);
	printf("time to die = %ld\n", param->tt_die);
	printf("time to eat = %ld\n", param->tt_eat);
	printf("time to sleep = %ld\n", param->tt_sleep);

	if (ac == 6)
	{
		param->nb_serving = ft_atoi(av[5]);
		printf("nb of serving = %d\n", param->nb_serving);
	}
	else 
		param->nb_serving = unavailable;

	return (param);
}

void    *test()
{
    printf("Hello\n");
    usleep(1000000);
    printf("Bye\n");
    return 0;
}

//void	create_thread(void)
//{
//	pthread__t	p1;
//
//	pthread_create(&p1, NULL, &test, NULL);
//	pthread_join(p1, NULL);
//}

void	init_container(t_container *cont, int ac, char **av)
{

	pthread_mutex_init(&cont->print, NULL);
	pthread_mutex_init(&cont->sudden_death, NULL);
	cont->param = set_parameters(ac, av);
	cont->philo = get_philosophers(cont);
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
    return (0);
}
