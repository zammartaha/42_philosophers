/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzammar <tzammar@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:03:15 by tzammar           #+#    #+#             */
/*   Updated: 2026/02/04 20:13:47 by tzammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	loop_init(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&(*philos)[i].meal_lock, NULL);
		(*philos)[i].id = i + 1;
		(*philos)[i].lf = &data->forks[i];
		(*philos)[i].rf = &data->forks[(i + 1) % data->nb_philo];
		(*philos)[i].lte = ct();
		(*philos)[i].me = 0;
		(*philos)[i].data = data;
		i++;
	}
}

static void	create_threads(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_create(&(*philos)[i].thread, NULL, routine, &(*philos)[i]);
		i++;
	}
}

static int	init_philos(t_data *data, t_philo **philos)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->state_lock, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	*philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->forks || !*philos)
	{
		if (data->forks)
			free(data->forks);
		if (*philos)
			free(*philos);
		return (printf("malloc error\n"), 1);
	}
	loop_init(data, philos);
	create_threads(data, philos);
	pthread_create(&monitor_thread, NULL, monitor, *philos);
	while (i < data->nb_philo)
		pthread_join((*philos)[i++].thread, NULL);
	pthread_join(monitor_thread, NULL);
	return (0);
}

static void	destroy_mutex(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&(*philos)[i].meal_lock);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->state_lock);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	if (ac < 5 || ac > 6)
		return (printf("invalid arguments\n"), 1);
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[2]) <= 0 || ft_atoi(av[3]) <= 0
		|| ft_atoi(av[4]) <= 0 || (ac == 6 && ft_atoi(av[5]) <= 0))
		return (printf("invalid arguments\n"), 1);
	if (ac == 6)
		data.mr = ft_atoi(av[5]);
	else
		data.mr = -1;
	data.ttd = ft_atoi(av[2]);
	data.tte = ft_atoi(av[3]);
	data.tts = ft_atoi(av[4]);
	data.nb_philo = ft_atoi(av[1]);
	data.died = 0;
	data.st = ct();
	if (init_philos(&data, &philos))
		return (1);
	destroy_mutex(&data, &philos);
	free(data.forks);
	free(philos);
	return (0);
}
