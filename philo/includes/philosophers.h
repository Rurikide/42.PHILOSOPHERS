/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:22:15 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/05 19:11:43 by tshimoda         ###   ########.fr       */
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
# define OVER 0
# define START 1
# define ARGUMENT "Enter: ./philo [nb_of_philo] [time_to_die] [time_to_eat] \
[time_to_sleep] :optional: [nb_of_serving]\n"

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
	int		nb_done_eat;
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
	int				simulation;
	long long		start_time;
}	t_container;

t_result	bool_isdigit(char *str);
t_result	bool_is_valid_input(int ac, char **ag);
t_result	bool_is_less_than_1(t_container *cont);
t_result	bool_usleep(long long time_param, t_philo *philo);
t_result	bool_is_dead(t_philo *philo);
t_result	bool_is_full(t_philo *p);
t_result	bool_service_done(t_philo *p);
long long	timecode_in_ms(void);
int			ft_atoi(const char *str);
int			init_container(t_container *cont, int ac, char **av);
void		init_philosophers(t_container *cont);
int			set_parameters(t_container *cont, int ac, char **av);
int			err_integer_limits(t_container *cont);
void		init_pthreads(t_container *cont);
void		init_queue(t_container *cont);
void		update_queue(t_container *cont);
void		update_queue(t_container *cont);
void		*routine(void *cont_philo);
void		act_check_forks(t_philo *p);
void		pick_up_forks(t_philo *p);
void		replace_forks(t_philo *p);
void		act_fall_asleep(t_philo *p);
void		act_wake_up(t_philo *p);
void		print_act(t_philo *p);
void		print_eat(t_philo *p, long long current_time);
void		simulation_one(t_container *cont);
void		end_simulation(t_container *cont);

#endif
