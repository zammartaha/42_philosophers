/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzammar <tzammar@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:03:15 by tzammar           #+#    #+#             */
/*   Updated: 2026/02/04 20:13:58 by tzammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	loop_init(t_data *data, t_philo **philos)
{
	int		i;
	char	*meal;

	i = 0;
	while (i < data->nb_philo)
	{
		meal = creat_sem_name("meal", i);
		sem_unlink(meal);
		(*philos)[i].meal_lock = sem_open(meal, O_CREAT, 0666, 1);
		free(meal);
		(*philos)[i].id = i + 1;
		(*philos)[i].lte = ct();
		(*philos)[i].me = 0;
		(*philos)[i].data = data;
		i++;
	}
}

static void	create_childs(t_data *data, t_philo **philos)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->nb_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			routine(&(*philos)[i]);
			exit(0);
		}
		(*philos)->pids[i] = pid;
		i++;
	}
	monitor(*philos);
}

static int	init_philos(t_data *data, t_philo **philos)
{
	int		i;

	i = 0;
	sem_unlink("/print_sem");
	sem_unlink("/forks_sem");
	data->forks = sem_open("/forks_sem", O_CREAT, 0666, data->nb_philo);
	data->print_lock = sem_open("/print_sem", O_CREAT, 0666, 1);
	*philos = malloc(sizeof(t_philo) * data->nb_philo);
	(*philos)->pids = malloc(sizeof(pid_t) * data->nb_philo);
	if (!*philos)
		return (printf("malloc error\n"), 1);
	loop_init(data, philos);
	create_childs(data, philos);
	return (0);
}

static void	close_sems(t_data *data, t_philo **philos)
{
	int		i;
	char	*meal;

	i = 0;
	while (i < data->nb_philo)
	{
		sem_close((*philos)[i].meal_lock);
		meal = creat_sem_name("meal", i);
		sem_unlink(meal);
		free(meal);
		i++;
	}
	sem_close(data->forks);
	sem_unlink("/forks_sem");
	sem_close(data->print_lock);
	sem_unlink("/print_sem");
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
	close_sems(&data, &philos);
	free(philos->pids);
	free(philos);
	return (0);
}
