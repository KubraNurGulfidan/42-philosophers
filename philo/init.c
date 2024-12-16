/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:32:32 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/12 15:35:29 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	pthread_mutex_init(&data->end_mutex, NULL);
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->eat_mutex, NULL);
	pthread_mutex_init(&data->need_mutex, NULL);
	return (0);
}

int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].start_time = current_time();
		data->philo[i].time_of_last_meal = current_time();
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].eat_done = 0;
		data->philo[i].data = data;
		if (i == 0)
			data->philo[i].right_fork = &data->forks[data->number_of_philo - 1];
		else
			data->philo[i].right_fork = &data->forks[i - 1];
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **av)
{
	data->number_of_philo = ft_atol(av[1]);
	data->timo_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->nbr_of_times_eat = ft_atol(av[5]);
	else
		data->nbr_of_times_eat = -1;
	data->end = 0;
	return (0);
}
