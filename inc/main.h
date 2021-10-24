/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:30:04 by rcarmen           #+#    #+#             */
/*   Updated: 2021/10/24 13:23:59 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_args
{
	pthread_mutex_t		message;
	int					full_philo;
	unsigned long long	start_time;
	int					time_to_die;
	int					time_to_eat;
	int					num_of_philo;
	int					nbr_each_eat;
	int					time_to_sleep;
}								t_args;

typedef struct s_philo
{
	unsigned int		id;
	pthread_mutex_t		food;
	t_args				*args;
	pthread_t			thread;
	pthread_mutex_t		left_fork;
	pthread_mutex_t		*right_fork;
	unsigned long long	start_eating;
	int					num_of_lunch;
}						t_philo;

int		error(int type, char *s, t_philo **philo, t_args **args);
void	init_first_philo(t_philo **philo, t_args *args);
void	monitor(t_philo **p, int i, t_args **args);
int		init_philo(t_philo **philo, t_args *args);
int		parse(int ac, char **av, t_args *args);
void	destroy(t_args **args, t_philo **p);
void	ft_usleep(long int time_in_ms);
void	put_down_the_forks(t_philo *p);
int		is_valid(int ac, char **av);
void	msg(char *s, t_philo *p);
void	take_forks(t_philo *p);
void	*life(void *philo);
int		ft_strlen(char *s);
int		ft_isspace(char c);
int		ft_atoi(char *np);
int		ft_isdigit(int c);
long	get_time(void);

#endif
