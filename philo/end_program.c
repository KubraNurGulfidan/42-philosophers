/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:33:17 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/12 15:33:23 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dieorlife(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end_mutex);
	pthread_mutex_lock(&philo->data->need_mutex);
	if (philo->data->end == 1 || philo->data->philo[0].eat_done == 1)
	{
		pthread_mutex_unlock(&philo->data->end_mutex);
		pthread_mutex_unlock(&philo->data->need_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->need_mutex);
	pthread_mutex_unlock(&philo->data->end_mutex);
	return (1);
}

static int	is_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (!is_ate(&data->philo[i]))
		{
			pthread_mutex_lock(&data->end_mutex);
			data->end = 1;
			pthread_mutex_unlock(&data->end_mutex);
			write_message(data->philo, "dead");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	is_complated_eat(t_data *data)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	if (data->nbr_of_times_eat == -1)
		return (1);
	while (i < data->number_of_philo)
	{
		pthread_mutex_lock(&data->eat_mutex);
		if (data->nbr_of_times_eat <= data->philo[i].eat_count)
			check++;
		pthread_mutex_unlock(&data->eat_mutex);
		i++;
	}
	if (check == data->number_of_philo)
	{
		pthread_mutex_lock(&data->need_mutex);
		data->philo[0].eat_done = 1;
		pthread_mutex_unlock(&data->need_mutex);
		return (0);
	}
	return (1);
}

void	dead_check(t_data *data)
{
	while (1)
	{
		if (!is_dead(data) || !is_complated_eat(data))
			break ;
	}
}

void	end_program(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->end_mutex);
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->need_mutex);
}
