/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:32:10 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/12 16:31:12 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!str[i])
		return (0);
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

size_t	current_time(void)
{
	size_t			current_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (current_time);
}

void	ft_usleep(t_philo *philo, size_t ms)
{
	size_t	start_time;

	start_time = current_time();
	while (current_time() - start_time < ms)
	{
		if (!dieorlife(philo))
			return ;
		usleep(500);
	}
}

void	write_message(t_philo *philo, char *state)
{
	static int	flag = 0;

	pthread_mutex_lock(&philo->data->need_mutex);
	if (philo[0].eat_done == 1)
	{
		pthread_mutex_unlock(&philo->data->need_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->need_mutex);
	pthread_mutex_lock(&philo->data->write_mutex);
	if (dieorlife(philo))
	{
		printf("%zu %d %s\n", current_time() - philo->start_time, philo->id,
			state);
		pthread_mutex_unlock(&philo->data->write_mutex);
		return ;
	}
	else if (!flag)
	{
		printf("%zu %d %s\n", current_time() - philo->start_time, philo->id,
			state);
		flag = 1;
	}
	pthread_mutex_unlock(&philo->data->write_mutex);
}
