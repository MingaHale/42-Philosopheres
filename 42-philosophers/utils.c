/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminga <mminga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:13:02 by mminga            #+#    #+#             */
/*   Updated: 2023/10/20 11:13:03 by mminga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	print_error(char *str)
{
	printf("%s", str);
	return (0);
}

unsigned int	ft_atoi(char *str)
{
	unsigned int	res;
	int				i;

	i = 0;
	res = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res);
}

void	message(t_philo *philo, char *str)
{
	uint64_t	time;

	time = time_from_start(philo->env);
	pthread_mutex_lock(&philo->env->m_write);
	pthread_mutex_lock(&philo->env->m_stop);
	if (!philo->env->stop)
		printf("%llu %llu %s\n", time, philo->id, str); // unsigned long long türü için, (sadece u olsa olmazmıydı)?
	pthread_mutex_unlock(&philo->env->m_stop);
	pthread_mutex_unlock(&philo->env->m_write);
}



