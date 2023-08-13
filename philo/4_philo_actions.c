/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_philo_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:38:23 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/08/11 17:51:57 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think(t_philo *philo)
{
	global_print(get_actual_time(), philo, "is thinking");
	usleep(999);
}

void	philo_sleep(t_philo *philo)
{
	global_print(get_actual_time(), philo, "is sleeping");
	usleep(philo->table->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	set_last_feeding(philo);
	global_print(get_actual_time(), philo, "is eating");
	if (philo->remaing_times_to_eat > 0)
		philo->remaing_times_to_eat--;
	usleep(philo->table->time_to_eat * 1000);
}

void	try_to_eat(t_philo *philo)
{
	if (philo->numb & 1)
	{
		lock_fork(philo, philo->left_fork);
		lock_fork(philo, philo->right_fork);
	}
	else
	{
		lock_fork(philo, philo->right_fork);
		lock_fork(philo, philo->left_fork);
	}
	if (philo->left_fork >= 0 && philo->right_fork >= 0
		&& !is_someone_dead(philo->table))
		eating(philo);
	unlock_fork(philo, philo->left_fork);
	unlock_fork(philo, philo->right_fork);
}
