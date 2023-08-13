/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_death_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:47:39 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/08/11 17:32:54 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	am_i_dead(t_philo *philo)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&philo->table->someone_died);
	if (get_actual_time() - get_last_feeding(philo) > philo->table->time_to_die)
	{
		if (!is_someone_dead(philo->table)
			&& get_actual_time() - get_last_feeding(philo)
			> philo->table->time_to_die)
		{
			global_print(get_actual_time(), philo, "died");
			set_someone_die(philo->table);
		}
		dead = 1;
	}
	pthread_mutex_unlock(&philo->table->someone_died);
	return (dead);
}

int	is_someone_dead(t_table *table)
{
	int	dead;

	pthread_mutex_lock(&table->death_checker);
	dead = table->someone_is_dead;
	pthread_mutex_unlock(&table->death_checker);
	return (dead);
}

void	set_someone_die(t_table *table)
{
	pthread_mutex_lock(&table->death_checker);
	table->someone_is_dead++;
	pthread_mutex_unlock(&table->death_checker);
}
