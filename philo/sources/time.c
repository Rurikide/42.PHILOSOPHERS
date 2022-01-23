/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:25:02 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/23 17:38:54 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long	ft_get_time_in_ms(void)
{
	struct      timeval	tv;
	long long   elapsed_time;

	gettimeofday(&tv, NULL);
	elapsed_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (elapsed_time);
}