/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mminga <mminga@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:11:55 by mminga            #+#    #+#             */
/*   Updated: 2023/10/20 11:11:56 by mminga           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	finish(t_env *env, int mutex_count, int thread_count)
{ 
	int	result;

	result = 0;
	if ((env->number_of_philo + 5) != mutex_count)
		result = !print_error("Mutex initialization error!\n");
	else if (env->number_of_philo != thread_count)
		result = !print_error("Thread creation error!\n");
	free(env->m_forks);
	free(env->philos);
	free(env);
	return (result);
}

int	main(int argc, char **argv)
{
	int		mutex_count;
	int		thread_count;
	t_env	*env;

	if (!arg_control(argc, argv))
		return (1);//Hata kodu
	env = init_args(argc, argv); //argümanları yerleştirir
	env = init_params(env);//yer açar
	if (env != NULL)
	{
		mutex_count = init_mutexes(env);
		thread_count = 0;
		if ((env->number_of_philo + 5) == mutex_count)
		{
			thread_count = init_threads(env);
			destroy_threads(env, thread_count);
		}
		destroy_mutexes(env, mutex_count);
		return (finish(env, mutex_count, thread_count));
	}
	return (0);
}
