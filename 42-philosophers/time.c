/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminga <mminga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:12:59 by mminga            #+#    #+#             */
/*   Updated: 2023/10/20 11:13:00 by mminga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

uint64_t	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

uint64_t	time_from_start(t_env *env)
{
	return (current_time() - env->time);
}

void	time_usleep(uint16_t micsec)
{
	uint64_t	current;

	current = current_time();
	while (1)
	{
		if (current_time() - current >= micsec)
			break ;
		usleep(100);
	}
}
