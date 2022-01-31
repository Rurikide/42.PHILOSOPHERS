/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:22:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/30 19:54:10 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define SUCCESS 0

typedef pthread_mutex_t		t_mutex;

typedef enum e_result
{
	unavailable = -1,
	false = 0,
	true = 1,
}	t_result;

enum e_ustensil
{
	taken,
	there
};

typedef struct s_fork
{
	pthread_mutex_t		fork_mutex;
	enum e_ustensil		fork_state;
}	t_fork;

typedef enum e_act
{
	binging,
	dreaming,
	pondering,
	dead
}	t_act;

typedef struct s_param
{
	int		nb_philo;
	long	tt_die;
	long	tt_eat;
	long	tt_sleep;
	int		nb_serving;
}	t_param;

typedef struct s_philo
{
	struct s_container	*cont;
	int					id;
	int					spag_bowl;
	long				last_meal;
	t_act				act;
	t_fork				*lefty;
	t_fork				*righty;
}	t_philo;

typedef struct s_container
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	t_param			*param;
	t_philo			*philo;
	t_fork			*forks;
	int				*queue;
	int				odd_one;
	long long		start_time;
}	t_container;

t_result	bool_isdigit(char *str);
t_result	bool_is_valid_input(int ac, char **ag);
int			ft_atoi(const char *str);
void		init_container(t_container *cont, int ac, char **av);
void		init_philosophers(t_container *cont);
void		set_parameters(t_container *cont, int ac, char **av);
void		init_pthreads(t_container *cont);
void		init_queue(t_container *cont);
void		update_queue(t_container *cont);
void		update_queue(t_container *cont);
void		*routine(void *cont_philo);
long long	ft_get_time_in_ms(void);
void		check_forks(t_philo *philo);
#endif
