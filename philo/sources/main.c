/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:21:25 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/24 12:11:14 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_parse_command_line(int ac, char **ag)
{
	
}

void    *test()
{
    printf("Hello\n");
    usleep(1000000);
    printf("Bye\n");
    return 0;
}

int main(int ac, char **av)
{
    pthread_t th;
    pthread_t t2;
	int			i;

	i = 0;
    pthread_create(&th, NULL, &test, NULL);
    pthread_create(&t2, NULL, &test, NULL);
    pthread_join(th, NULL);
    pthread_join(t2, NULL);
	if (ac == 5 || ac == 6)
	{
		while	(i++ < ac - 1)
		{
			if (bool_isdigit(av[i]) == true)
			{
				printf("All characters are digits\n");
				printf("the number is %d\n", ft_atoi(av[i]));
			}
			else
			{
				printf("Error : non digit character found.\n");
				return (0);
			}
		}
	}
	else
		printf("Error incorrect input. Enter: ./philo #of_philosophers #time_to_die #time_to_eat #time_to_sleep [optional] #of_serving.\n");
    return (0);
}
