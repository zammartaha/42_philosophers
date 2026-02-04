/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzammar <tzammar@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:46:29 by tzammar           #+#    #+#             */
/*   Updated: 2026/02/04 20:13:57 by tzammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static suseconds_t	get_lte(t_philo	*philo)
{
	suseconds_t	i;

	sem_wait(philo->meal_lock);
	i = ct() - philo->lte;
	sem_post(philo->meal_lock);
	return (i);
}

static void	kill_all_philos(t_philo	*philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_philo)
		kill(philos->pids[i++], SIGTERM);
	i = 0;
	while (i < philos->data->nb_philo)
		waitpid(philos->pids[i++], NULL, 0);
}

void	monitor(t_philo	*philos)
{
	int		i;
	int		status;
	pid_t	dead_pid;
	int		exit_code;

	i = 0;
	while (i < philos->data->nb_philo)
	{
		dead_pid = waitpid(-1, &status, 0);
		if (dead_pid == -1)
			break ;
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
			if (exit_code == 1)
			{
				kill_all_philos(philos);
				break ;
			}
			else if (exit_code == 0)
				i++;
		}
	}
}

void	*self_monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (1)
	{
		if (get_lte(philo) >= data->ttd)
		{
			sem_wait(data->print_lock);
			printf("%ld %d died\n", ct() - data->st, philo->id);
			exit(1);
		}
		usleep(500);
	}
	return (NULL);
}
