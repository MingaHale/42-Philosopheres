/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminga <mminga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:11:49 by mminga            #+#    #+#             */
/*   Updated: 2023/10/20 11:11:50 by mminga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#define MSG_DIED "died"

static int	is_must_eat(t_env *env)
{
	int	i;

	if (env->number_of_must_eat < 0)// Eğer negatif bir değer girilmişse, sınırsız yemek yeme şartı vardır ve fonksiyon hemen 0 döner.
		return (0);
	i = 0;
	while (i < env->number_of_philo)
	{
		pthread_mutex_lock(&env->m_eat_count);
		if (env->philos[i++].eat_count < env->number_of_must_eat)//i kontrolden sonra artar.
		{
			pthread_mutex_unlock(&env->m_eat_count);
			return (0);
		}
		else // yemesi gerektiği kadar yemişse
			pthread_mutex_unlock(&env->m_eat_count);
	}
	return (1);
}

static int	die_event(t_env *env, int i)
{
	while (env->number_of_philo > 0)
	{
		i = -1;
		while (++i < env->number_of_philo)
		{
			pthread_mutex_lock(&env->m_last_eat);
			pthread_mutex_lock(&env->m_die);
			if ((current_time() - env->philos[i].last_eat) >= env->time_to_die)
			{
				message(&env->philos[i], MSG_DIED);
				pthread_mutex_lock(&env->m_stop);
				env->stop = 1;
				pthread_mutex_unlock(&env->m_stop);
				pthread_mutex_unlock(&env->m_last_eat);
				return (0);
			}
			else
				pthread_mutex_unlock(&env->m_last_eat);
			pthread_mutex_unlock(&env->m_die);
		}
		if (is_must_eat(env))
			break ;
	}
	return (1);
}

void	die_controller(t_env *env)
{
	if (!(die_event(env, -1)))
		return ;
	pthread_mutex_lock(&env->m_stop);
	env->stop = 1;
	pthread_mutex_unlock(&env->m_stop);
}
