/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_and_setters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:03:05 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/07/29 18:14:20 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_last_feeding(t_philo *philo)
{
	long	last_feeding;

	pthread_mutex_lock(&philo->table->someone_is_eating);
	last_feeding = philo->last_feeding;
	pthread_mutex_unlock(&philo->table->someone_is_eating);
	return (last_feeding);
}

void	set_last_feeding(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->someone_is_eating);
	philo->last_feeding = get_actual_time();
	pthread_mutex_unlock(&philo->table->someone_is_eating);
}
