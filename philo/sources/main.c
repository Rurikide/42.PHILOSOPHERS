/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:21:25 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/26 16:30:16 by tshimoda         ###   ########.fr       */
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

void	ft_parse_command_line(t_param *set, int ac, char **av)
{
	set->nb_philo = ft_atoi(av[1]);
	set->tt_die = ft_atoi(av[2]);
	set->tt_eat = ft_atoi(av[3]);
	set->tt_sleep = ft_atoi(av[4]);
	printf("nb_philo = %d\n", set->nb_philo);
	printf("time to die = %ld\n", set->tt_die);
	printf("time to eat = %ld\n", set->tt_eat);
	printf("time to sleep = %ld\n", set->tt_sleep);

	if (ac == 6)
	{
		set->nb_serving = ft_atoi(av[5]);
		printf("nb of serving = %d\n", set->nb_serving);
	}
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

int main(int ac, char **av)
{
	t_param	set;
	if (ac == 5 || ac == 6)
	{
		if (bool_is_valid_input(ac, av) == false)
		{
			printf("Error : Non digit argument\n");
			return (0);
		}
		ft_parse_command_line(&set, ac, av);
	}
	else
		printf("Error incorrect input. Enter: ./philo [nb_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] :::optional::: [nb_of_serving]\n");
    return (0);
}
