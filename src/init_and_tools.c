/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:27:18 by rcarmen           #+#    #+#             */
/*   Updated: 2021/10/21 14:09:33 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	error(int type, char *s)
{
	if (type == 0)
	{
		write(2, s, ft_strlen(s));
		return (1);
	}
	return (0);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*
**
** Lock print muxtix and print information
** about the philosopher's condition
**
*/
void	msg(char *s, t_philo *p)
{
	pthread_mutex_lock(&p->args->message);
	printf(s, get_time() - p->args->start_time, p->id + 1);
	pthread_mutex_unlock(&p->args->message);
}

/*
**
** Initialization of the philosopher:
** 1. Id: 1-n;
** 2. Number of lunch;
** 3. Init mutex-left fork;
** 4. Args;
** 5. Start eating;
**
*/
void	init_first_philo(t_philo **philo, t_args *args)
{
	(*philo)[0].id = 0;
	(*philo)[0].num_of_lunch = 0;
	pthread_mutex_init(&(*philo)[0].left_fork, NULL);
	(*philo)[0].args = args;
	(*philo)[0].start_eating = get_time();
}

/*
**
** Initialization of the philosopher:
** 1. Id: 1 - n;
** 2. Number of lunch;
** 3. Init mutex-left fork;
** 4. Init mutex-right fork;
** 5. Args;
** 6. Start eating;
**
*/
int	init_philo(t_philo **philo, t_args *args)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * (args->num_of_philo));
	if (NULL == *philo)
		return (1);
	init_first_philo(philo, args);
	i = 1;
	while (i < args->num_of_philo)
	{
		(*philo)[i].id = i;
		(*philo)[i].num_of_lunch = 0;
		pthread_mutex_init(&(*philo)[i].left_fork, NULL);
		(*philo)[i].right_fork = &(*philo)[i - 1].left_fork;
		(*philo)[i].args = args;
		(*philo)[i].start_eating = get_time();
		i++;
	}
	(*philo)[0].right_fork = &(*philo)[i].left_fork;
	if (i == 1)
		(*philo)[0].right_fork = &(*philo)[0].left_fork;
	return (0);
}
