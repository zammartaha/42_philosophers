/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzammar <tzammar@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 18:01:34 by tzammar           #+#    #+#             */
/*   Updated: 2026/02/04 20:13:59 by tzammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/types.h>
# include <semaphore.h>

typedef struct s_data
{
	int				mr;
	suseconds_t		st;
	suseconds_t		ttd;
	suseconds_t		tte;
	suseconds_t		tts;
	int				died;
	sem_t			*forks;
	int				nb_philo;
	sem_t			*print_lock;
}	t_data;

typedef struct s_philo
{
	int				me;
	int				id;
	suseconds_t		lte;
	sem_t			*lf;
	sem_t			*rf;
	pid_t			*pids;
	t_data			*data;
	sem_t			*meal_lock;
}	t_philo;

suseconds_t	ct(void);
char		*ft_itoa(int n);
void		routine(void *arg);
void		monitor(t_philo	*philos);
int			ft_atoi(const char *str);
void		*self_monitor(void *arg);
void		ft_usleep(suseconds_t ms);
void		print_action(t_philo *philo, char *msg);
char		*creat_sem_name(const char *prefix, int num);

#endif
