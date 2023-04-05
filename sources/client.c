/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 19:25:09 by fra           #+#    #+#                 */
/*   Updated: 2023/04/05 13:42:56 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	g_bit_sent;

void	send_signal(pid_t pid, int condition)
{
	if (kill(pid, 0))
		ft_raise_error("(minitalk) lost connection", NULL, 1);
	else if (condition)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
}

void	send_string(pid_t pid, char *string)
{
	int	mask;

	while (1)
	{
		mask = 0b10000000;
		while (mask)
		{
			g_bit_sent = 0;
			send_signal(pid, ((unsigned char) *string) & mask);
			while (! g_bit_sent)
				;
		mask >>= 1;
		}
		if (! *string++)
			break ;
	}
}

void	client_handler(int signum)
{
	if (signum == SIGUSR1)
		g_bit_sent = 1;
	else if (signum == SIGUSR2)
	{
		ft_printf("Message sent\n");
		exit(EXIT_SUCCESS);
	}
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

int	main(int argc, char **argv)
{
	int					status;
	struct sigaction	action;

	status = 0;
	action.sa_handler = &client_handler;
	sigemptyset(&(action.sa_mask));
	status += sigaction(SIGUSR1, &action, NULL);
	status += sigaction(SIGUSR2, &action, NULL);
	printf("arg1: %s\n arg2: %s\n", argv[1], argv[2]);
	if (status)
		ft_raise_error("(minitalk) Error setting handler for signal", NULL, 1);
	// else if (argc != 3 || ! check_pid(argv[1]))
	// 	ft_raise_error("(minitalk) Input error", NULL, 1);
	// else
	send_string(ft_atoi(argv[1]), argv[2]);
	return (0);
}
