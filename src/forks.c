/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 21:16:29 by rcarmen           #+#    #+#             */
/*   Updated: 2021/10/21 00:11:15 by rcarmen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
**
** Take forks and print actions
**
*/
void	take_forks(t_philo *p)
{
	pthread_mutex_lock(&p->left_fork);
	msg("%llu\t%i\thas taken left fork\n", p);
	pthread_mutex_lock(p->right_fork);
	msg("%llu\t%i\thas taken right fork\n", p);
}

/*
**
** Put down forks and print actions
**
*/
void	put_down_the_forks(t_philo *p)
{
	pthread_mutex_unlock(&p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	destroy(t_philo *p)
{
	int	j;

	j = 0;
	while (j < p->args->num_of_philo)
	{
		pthread_mutex_destroy(&p[j].left_fork);
		j++;
	}
	free(p);
}
