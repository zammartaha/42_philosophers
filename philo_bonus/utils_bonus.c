/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzammar <tzammar@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 01:20:07 by tzammar           #+#    #+#             */
/*   Updated: 2026/02/04 20:14:02 by tzammar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

suseconds_t	ct(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_action(t_philo *philo, char *msg)
{
	sem_wait(philo->data->print_lock);
	printf("%ld %d %s\n", ct() - philo->data->st, philo->id, msg);
	sem_post(philo->data->print_lock);
}

void	ft_usleep(suseconds_t ms)
{
	suseconds_t	start;

	start = ct();
	while ((ct() - start) < ms)
		usleep(100);
}

static size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*creat_sem_name(const char *prefix, int num)
{
	char	*name;
	char	*num_str;
	int		i;
	int		j;
	int		prefix_len;

	prefix_len = ft_strlen(prefix);
	num_str = ft_itoa(num);
	if (!num_str)
		return (NULL);
	i = ft_strlen(num_str);
	name = malloc(prefix_len + i + 2);
	if (!name)
		return (free(num_str), NULL);
	name[0] = '/';
	i = 1;
	j = 0;
	while (prefix[j])
		name[i++] = prefix[j++];
	j = 0;
	while (num_str[j])
		name[i++] = num_str[j++];
	name[i] = '\0';
	return (free(num_str), name);
}
