/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 19:09:59 by rcarmen           #+#    #+#             */
/*   Updated: 2021/10/21 23:21:09 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include "main.h"

/*
**
** Checks whether the number of
** meals is equal to the number -1 
** or equal to the number given as
** the fifth argument of the program
**
** And then checking whether the
** philosopher has died of hunger
**
*/
void	monitor(t_philo *p, int i)
{
	while (1)
	{
		i = 0;
		while (i < p->args->num_of_philo)
		{
			if (p->args->full_philo == p->args->num_of_philo)
			{
				pthread_mutex_lock(&p->args->message);
				printf("%llu\tall full\n", get_time() - p->args->start_time);
				destroy(p);
				return ;
			}
			ft_usleep(1);
			if (get_time() - p[i].start_eating >= \
				(unsigned long long)p->args->time_to_die)
			{
				pthread_mutex_lock(&p->args->message);
				printf("%llu\t%i\tis died\n", get_time() - \
						p->args->start_time, i + 1);
				destroy(p);
				return ;
			}
			i++;
		}
	}
}

/*
**
** Here the philosopher eats, sleeps and
** thinks until the number of his meals
** is equal to -1 (infinitely) or equal to
** the number given as the fifth argument
** of the program
**
*/
void	*life(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	while (p->num_of_lunch != p->args->nbr_each_eat)
	{
		p->num_of_lunch++;
		take_forks(p);
		if (p->num_of_lunch == p->args->nbr_each_eat)
			p->args->full_philo++;
		msg("%llu\t%i\tis eating\n", p);
		ft_usleep(p->args->time_to_eat);
		p->start_eating = get_time();
		put_down_the_forks(p);
		if (p->num_of_lunch == p->args->nbr_each_eat)
			continue ;
		msg("%llu\t%i\tis sleeping\n", p);
		ft_usleep(p->args->time_to_sleep);
		msg("%llu\t%i\tis thinking\n", p);
	}
	return (NULL);
}

/*
**
** Parsing and initialization args struct:
** 1. number of philosophers;
** 2. time to die;
** 3. time to eat;
** 4. time to sleep;
** 5. [number_of_times_each_philosopher_must_eat];
** 6. message mutex init;
** 7. start time;
** 8. full philo;
**
*/
int	parse(int ac, char **av, t_args *args)
{
	args->num_of_philo = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->nbr_each_eat = -1;
	if (ac == 6)
		args->nbr_each_eat = ft_atoi(av[5]);
	if (pthread_mutex_init(&args->message, NULL))
		return (1);
	args->start_time = get_time();
	args->full_philo = 0;
	return (0);
}

/*
**
** Checking arguments.
** Only numeric characters are accepted.
**
*/
int	is_valid(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac < 5 || ac > 6)
		return (1);
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}	
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_args	*args;
	int		i;

	args = malloc(sizeof(t_args));
	if (is_valid(ac, av) || parse(ac, av, args) || init_philo(&philo, args))
		return (error(0, "Invalid argument or syscall error.\n"));
	i = 0;
	while (i < args->num_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, &life, &philo[i]);
		pthread_detach(philo[i].thread);
		i += 2;
	}
	i = 1;
	while (i < args->num_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, &life, &philo[i]);
		pthread_detach(philo[i].thread);
		i += 2;
	}
	monitor(philo, 0);
}
