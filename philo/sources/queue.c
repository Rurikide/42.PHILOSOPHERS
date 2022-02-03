/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:08:31 by tshimoda          #+#    #+#             */
/*   Updated: 2022/02/03 10:02:30 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	update_queue(t_container *cont)
{
	int	temp;
	int	i;

	i = 0;
	temp = cont->queue[0];
	while (i < cont->param->nb_philo - 1)
	{
		cont->queue[i] = cont->queue[i + 1];
		i++;
	}
	cont->queue[i] = temp;
}

void	init_queue(t_container *cont)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	cont->queue = malloc(sizeof(int) * cont->param->nb_philo);
	while (i < cont->param->nb_philo)
	{
		cont->queue[pos] = cont->philo[i].id;
		pos++;
		i += 2;
	}
	i = 1;
	while (i < cont->param->nb_philo)
	{
		cont->queue[pos] = cont->philo[i].id;
		pos++;
		i += 2;
	}
}
