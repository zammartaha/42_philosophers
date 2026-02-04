/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzammar <tzammar@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:01:34 by tzammar           #+#    #+#             */
/*   Updated: 2026/02/04 20:13:48 by tzammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				mr;
	suseconds_t		st;
	suseconds_t		ttd;
	suseconds_t		tte;
	suseconds_t		tts;
	int				died;
	pthread_mutex_t	*forks;
	int				nb_philo;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	print_lock;
}	t_data;

typedef struct s_philo
{
	int				me;
	int				id;
	suseconds_t		lte;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
}	t_philo;

suseconds_t	ct(void);
void		*routine(void *arg);
void		*monitor(void *arg);
int			is_dead(t_data *data);
int			ft_atoi(const char *str);
void		ft_usleep(suseconds_t ms, t_data *data);
void		print_action(t_philo *philo, char *msg);

#endif
