/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:22:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/23 17:34:55 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_bool
{
	false = 0,
	true = 1,
	fail = -1
}	t_bool;

typedef enum e_fork
{
	taken = 0,
	there = 1
}	t_fork;

typedef enum e_routine
{
	binging,
	dreaming,
	pondering,
	dead
}	t_routine;

typedef struct s_philo
{
	int				id;
	int				spag_plate;
	t_routine		act;
	pthread_mutex_t mutex_dead;
	pthread_mutex_t mutex_fork;
	pthread_mutex_t mutex_print;
}	t_philo;

typedef struct s_param
{
	int		nb_philo;
	double	tt_die;
	double	tt_eat;
	double	tt_sleep;
	double	tt_think;
	int		nb_serving;
}	t_param;

int	ft_atoi(const char *str);

#endif