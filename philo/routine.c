/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzammar <tzammar@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:08:14 by tzammar           #+#    #+#             */
/*   Updated: 2026/02/04 20:13:50 by tzammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->lf;
	second = philo->rf;
	if (philo->id % 2 == 0)
	{
		first = philo->rf;
		second = philo->lf;
	}
	pthread_mutex_lock(first);
	print_action(philo, "has taken a fork");
	if (first == second)
		return (pthread_mutex_unlock(first), 1);
	if (is_dead(philo->data))
		return (pthread_mutex_unlock(first), 1);
	pthread_mutex_lock(second);
	print_action(philo, "has taken a fork");
	return (0);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->lte = ct();
	philo->me++;
	pthread_mutex_unlock(&philo->meal_lock);
	print_action(philo, "is eating");
	ft_usleep(philo->data->tte, philo->data);
	pthread_mutex_unlock(philo->lf);
	pthread_mutex_unlock(philo->rf);
}

static void	go_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo->data->tts, philo->data);
}

static void	think(t_philo *philo)
{
	print_action(philo, "is thinking");
	usleep(500);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1500);
	while (!is_dead(philo->data))
	{
		if (take_forks(philo))
			break ;
		eat(philo);
		if (is_dead(philo->data))
			break ;
		go_sleep(philo);
		if (is_dead(philo->data))
			break ;
		think(philo);
	}
	return (NULL);
}
