/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:32:18 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/15 19:17:04 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ft_atol(av[1]) > 200)
	{
		printf("Error: invalid argument!\n");
		return (1);
	}
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("Error: invalid argument!\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	routine_helper(t_data *data, int i)
{
	if (data->number_of_philo == 1)
	{
		if (pthread_detach(data->philo[i].thread))
		{
			printf("Error: Detach Err.\n");
			return (1);
		}
	}
	else
	{
		if (pthread_join(data->philo[i].thread, NULL))
		{
			printf("Error: Join Err.\n");
			return (1);
		}
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo[0].data->number_of_philo == 1)
	{
		pthread_mutex_lock(philo->right_fork);
		write_message(philo, "has taken a fork");
		pthread_mutex_unlock(philo->right_fork);
		philo->data->end = 1;
		dieorlife(philo);
		return (arg);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo, 1);
	while (dieorlife(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

static int	start_program(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, routine,
				(void *)&data->philo[i]))
			return (1);
		i++;
	}
	dead_check(data);
	i = -1;
	while (++i < data->number_of_philo)
		if (routine_helper(data, i))
			break ;
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (!(ac == 5 || ac == 6))
	{
		printf("Error: number of invalid arguments!\n");
		return (1);
	}
	if (arg_check(av))
		return (1);
	if (init_data(&data, av) || init_philo(&data) || init_fork(&data)
		|| init_mutex(&data))
	{
		printf("Error: initialize failed!\n");
		return (1);
	}
	start_program(&data);
	end_program(&data);
}
