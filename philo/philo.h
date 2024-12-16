/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgulfida <kgulfida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:32:00 by kgulfida          #+#    #+#             */
/*   Updated: 2024/11/12 16:31:27 by kgulfida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define PHILO_MAX 200

typedef struct s_philo
{
	int				id;
	int				eat_count;
	size_t			start_time;
	size_t			time_of_last_meal;
	int				eat_done;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				number_of_philo;
	int				end;
	size_t			timo_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nbr_of_times_eat;
	t_philo			philo[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	need_mutex;
}					t_data;

int					init_mutex(t_data *data);
int					init_fork(t_data *data);
int					init_philo(t_data *data);
int					init_data(t_data *data, char **av);
long				ft_atol(char *str);
size_t				current_time(void);
void				ft_usleep(t_philo *philo, size_t ms);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
void				write_message(t_philo *philo, char *state);
void				dead_check(t_data *data);
void				end_program(t_data *data);
int					is_ate(t_philo *philo);
int					dieorlife(t_philo *philo);

#endif
