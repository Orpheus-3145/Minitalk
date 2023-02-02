/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/19 22:45:51 by fra           #+#    #+#                 */
/*   Updated: 2023/01/30 23:14:23 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(pid_t pid, int condition)
{
	if (kill(pid, 0))
		ft_raise_error("lost connection", NULL, 1);
	else if (condition)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
}

int	check_pid(char *n)
{
	int	pid;

	pid = ft_atoi(n);
	if (pid != (int) ft_atol(n))
		return (0);
	else if (! pid && *n != '0')
		return (0);
	else if (kill(pid, 0))
		return (0);
	else
		return (1);
}
