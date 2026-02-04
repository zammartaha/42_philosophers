/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzammar <tzammar@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:08:14 by tzammar           #+#    #+#             */
/*   Updated: 2026/02/04 20:14:00 by tzammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_action(philo, "has taken a fork");
}

static void	eat(t_philo *philo)
{
	sem_wait(philo->meal_lock);
	philo->lte = ct();
	philo->me++;
	sem_post(philo->meal_lock);
	print_action(philo, "is eating");
	ft_usleep(philo->data->tte);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	if (philo->data->mr != -1 && philo->me >= philo->data->mr)
		exit(0);
}

static void	go_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->tts);
}

static void	think(t_philo *philo)
{
	print_action(philo, "is thinking");
	usleep(500);
}

void	routine(void *arg)
{
	t_philo		*philo;
	pthread_t	monitor_thread;

	philo = (t_philo *)arg;
	pthread_create(&monitor_thread, NULL, self_monitor, philo);
	pthread_detach(monitor_thread);
	if (philo->id % 2 == 0)
		usleep (1500);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		go_sleep(philo);
		think(philo);
	}
}
