/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_forks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:42:05 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/08/04 15:51:35 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork(t_philo *philo, int fork_num)
{
	if (fork_num >= 0)
	{
		pthread_mutex_lock(&philo->table->forks[fork_num]);
		global_print(get_actual_time(), philo, "has taken a fork");
	}
}

void	unlock_fork(t_philo *philo, int fork_num)
{
	if (fork_num >= 0)
		pthread_mutex_unlock(&philo->table->forks[fork_num]);
}
