/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:22:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/26 16:16:45 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_result
{
	fail = -1,
	false = 0,
	true = 1
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
	struct t_container	*data;
	int					id;
	int					spag_plate;
	t_act				act;
	pthread_mutex_t		mutex_fork;
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
	t_philo			*philo;
	t_param			*param;
}	t_container;

t_result	bool_isdigit(char *str);
t_result	bool_is_valid_input(int	ac, char **ag);
int			ft_atoi(const char *str);
#endif
