/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:32:25 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/12 15:32:28 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	write_message(philo, "is sleeping");
	ft_usleep(philo, philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	write_message(philo, "is thinking");
	return ;
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	write_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	write_message(philo, "has taken a fork");
	write_message(philo, "is eating");
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->time_of_last_meal = current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->eat_mutex);
	ft_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	is_ate(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->data->eat_mutex);
	time = current_time();
	if (time - philo->time_of_last_meal >= philo->data->timo_to_die)
	{
		pthread_mutex_unlock(&philo->data->eat_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->eat_mutex);
	return (1);
}
