/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:25:02 by tshimoda          #+#    #+#             */
/*   Updated: 2022/01/30 18:13:19 by tshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long	ft_get_time_in_ms(void)
{
	struct timeval	tv;
	long long		timecode;

	gettimeofday(&tv, NULL);
	timecode = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (timecode);
}
