/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:22:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/27 12:16:17 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t		mutex_t;

typedef enum e_result
{
	unavailable = -1,
	false = 0,
	true = 1,
}	t_result;

typedef enum e_fork
{
	taken,
	there
}	t_fork;

typedef enum e_act
{
	binging,
	dreaming,
	pondering,
	dead
}	t_act;

typedef struct s_philo
{
	pthread_mutex_t		mutex_fork;
	struct t_container	*cont;
	int					id;
	int					spag_plate;
	t_act				act;
}	t_philo;

typedef struct s_param
{
	int		nb_philo;
	long	tt_die;
	long	tt_eat;
	long	tt_sleep;
	int		nb_serving;
}	t_param;

typedef	struct s_container
{
	pthread_mutex_t	print;
	pthread_mutex_t	sudden_death;
	t_param			*param;
	t_philo			*philo;
	int				*queue;
	int				odd_one;
	long long		start_time;
}	t_container;

t_result	bool_isdigit(char *str);
t_result	bool_is_valid_input(int	ac, char **ag);
int			ft_atoi(const char *str);

void	init_container(t_container *cont, int ac, char **av);
t_param	*set_parameters(int ac, char **av);
t_philo *get_philosophers(t_container cont);

#endif
