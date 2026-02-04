/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzammar <tzammar@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:46:29 by tzammar           #+#    #+#             */
/*   Updated: 2026/02/04 20:13:46 by tzammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	all_ate(t_philo *philos, t_data *data)
{
	int	i;

	if (data->mr <= 0)
		return (0);
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&(philos)[i].meal_lock);
		if (philos[i].me < data->mr)
		{
			pthread_mutex_unlock(&(philos)[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&(philos)[i].meal_lock);
		i++;
	}
	return (1);
}

int	is_dead(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->state_lock);
	i = data->died;
	pthread_mutex_unlock(&data->state_lock);
	return (i);
}

static void	set_dead(t_data *data)
{
	pthread_mutex_lock(&data->state_lock);
	data->died = 1;
	pthread_mutex_unlock(&data->state_lock);
}

static suseconds_t	get_lte(t_philo	*philo)
{
	suseconds_t	i;

	pthread_mutex_lock(&philo->meal_lock);
	i = ct() - philo->lte;
	pthread_mutex_unlock(&philo->meal_lock);
	return (i);
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	t_data	*data;
	int		i;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (!is_dead(data))
	{
		i = 0;
		while (i < data->nb_philo && !is_dead(data))
		{
			if (get_lte(&philos[i]) >= data->ttd)
			{
				set_dead(data);
				pthread_mutex_lock(&data->print_lock);
				printf("%ld %d died\n", ct() - data->st, philos[i].id);
				return (pthread_mutex_unlock(&data->print_lock), NULL);
			}
			i++;
		}
		if (all_ate(philos, data))
			return (set_dead(data), NULL);
		usleep(500);
	}
	return (NULL);
}
