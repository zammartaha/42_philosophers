/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzammar <tzammar@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:20:07 by tzammar           #+#    #+#             */
/*   Updated: 2026/02/04 20:13:51 by tzammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

suseconds_t	ct(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_action(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->state_lock);
	if (!philo->data->died)
	{
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%ld %d %s\n", ct() - philo->data->st, philo->id, msg);
		pthread_mutex_unlock(&philo->data->print_lock);
	}
	pthread_mutex_unlock(&philo->data->state_lock);
}

void	ft_usleep(suseconds_t ms, t_data *data)
{
	suseconds_t	start;

	start = ct();
	while ((ct() - start) < ms && !is_dead(data))
		usleep(100);
}
