/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminga <mminga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:12:02 by mminga            #+#    #+#             */
/*   Updated: 2023/10/20 11:12:03 by mminga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_global_mutexes(t_env *env) //başlatılan mutex sayısını döndürür
{
	int	result;

	result = 0;
	if (!pthread_mutex_init(&env->m_stop, NULL))//başlatıldıysa +1
		result++;
	if (result == 1 && !pthread_mutex_init(&env->m_eat_count, NULL))
		result++;
	if (result == 2 && !pthread_mutex_init(&env->m_last_eat, NULL))
		result++;
	if (result == 3 && !pthread_mutex_init(&env->m_write, NULL))
		result++;
	if (result == 4 && !pthread_mutex_init(&env->m_die, NULL))
		result++;
	return (result);//5
}

int	init_mutexes(t_env *env)
{
	int	mutex_count;

	mutex_count = init_global_mutexes(env);
	if (mutex_count == 5)
	{
		mutex_count += init_philo_or_fork(env, init_philo);
		if ((env->number_of_philo + 5) == mutex_count)
			init_philo_or_fork(env, init_forks);
	}
	return (mutex_count);
}

void	destroy_mutexes(t_env *env, int mutex_count)
{
	int	i;

	i = 0;
	if (mutex_count >= 1)
		pthread_mutex_destroy(&env->m_stop);
	if (mutex_count >= 2)
		pthread_mutex_destroy(&env->m_eat_count);
	if (mutex_count >= 3)
		pthread_mutex_destroy(&env->m_last_eat);
	if (mutex_count >= 4)
		pthread_mutex_destroy(&env->m_write);
	if (mutex_count >= 5)
		pthread_mutex_destroy(&env->m_die);
	while (i < (mutex_count - 5) && i < env->number_of_philo)
		pthread_mutex_destroy(&env->m_forks[i++]);
}
