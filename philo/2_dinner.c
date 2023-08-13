/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_dinner.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  rleite-s < rleite-s@student.42sp.org.b    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 13:54:55 by  rleite-s         #+#    #+#             */
/*   Updated: 2023/08/09 18:37:28 by  rleite-s        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_dinner(t_philo *philo, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		pthread_create(&philo[i].thread, NULL, dinner, &philo[i]);
		i++;
	}
}

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = arg;
	set_last_feeding(philo);
	while (philo->remaing_times_to_eat && !is_someone_dead(philo->table))
	{
		try_to_eat(philo);
		if (philo->remaing_times_to_eat && !is_someone_dead(philo->table))
			philo_sleep(philo);
		if (philo->remaing_times_to_eat && !is_someone_dead(philo->table))
			philo_think(philo);
	}
	update_finished_to_eat(philo);
	return (NULL);
}

void	finish_dinner(t_table *table, t_philo *philo, int total)
{
	int	i;

	i = 0;
	while (i < total)
		pthread_join(philo[i++].thread, 0);
	i = 0;
	while (i < total)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->death_checker);
	pthread_mutex_destroy(&table->someone_is_eating);
	pthread_mutex_destroy(&table->someone_is_talking);
	pthread_mutex_destroy(&table->someone_died);
	free(philo);
	free(table->forks);
}
