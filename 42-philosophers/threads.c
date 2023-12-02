/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminga <mminga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:12:55 by mminga            #+#    #+#             */
/*   Updated: 2023/10/20 11:12:56 by mminga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_threads(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->number_of_philo)
	{
		if (pthread_create(&env->philos[i].thread, NULL, \
			routine, &env->philos[i])) //eğer pthread_create Başarılı bi şekilde çalışırsa false alır ve block çalışmaz
		{
			pthread_mutex_lock(&env->m_stop);
			env->stop = 1;
			pthread_mutex_unlock(&env->m_stop);
			return (i);
		}
	}
	die_controller(env);
	return (env->number_of_philo);
}

void	destroy_threads(t_env *env, int thread_count)
{
	int	i;

	i = -1;
	while (++i < thread_count)
		pthread_join(env->philos[i].thread, NULL);
}
