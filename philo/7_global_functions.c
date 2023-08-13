/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_global_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 14:05:12 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/08/09 20:48:56 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_actual_time(void)
{
	struct timeval	time;

	gettimeofday(&time, 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	global_print(long time, t_philo *philo, char *action)
{
	if (!is_someone_dead(philo->table))
	{
		pthread_mutex_lock(&philo->table->someone_is_talking);
		if (!is_someone_dead(philo->table))
			printf("%9ld %d %s\n", time - philo->table->start_time,
				philo->numb + 1, action);
		pthread_mutex_unlock(&philo->table->someone_is_talking);
	}
}

void	update_finished_to_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->eat_checker);
	philo->table->philos_that_finished_to_eat++;
	pthread_mutex_unlock(&philo->table->eat_checker);
}

int	everyone_eated(t_table *table, int total)
{
	int	everyone;

	pthread_mutex_lock(&table->eat_checker);
	everyone = table->philos_that_finished_to_eat;
	pthread_mutex_unlock(&table->eat_checker);
	return (everyone == total);
}

void	observer(t_table *table, t_philo *philo, int total)
{
	int	i;

	i = 0;
	while (!is_someone_dead(table) && !everyone_eated(table, total))
	{
		if (am_i_dead(&philo[i]))
			set_someone_die(table);
		i++;
		if (i == total)
			i = 0;
		usleep(100);
	}
}
