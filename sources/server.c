/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 19:25:04 by fra           #+#    #+#                 */
/*   Updated: 2023/04/05 13:21:53 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(pid_t pid, int condition)
{
	if (kill(pid, 0))
		ft_raise_error("(minitalk) lost connection", NULL, 1);
	else if (condition)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
}

void	server_handler(int signum, siginfo_t *client, void *ucontext)
{
	static int	i;
	static char	received;
	int			end_msg;

	(void) ucontext;
	received <<= 1;
	received += signum == SIGUSR2;
	end_msg = 0;
	if (++i == 8)
	{
		write(1, &received, 1);
		end_msg = ! received;
		i = 0;
	}
	send_signal(client->si_pid, end_msg);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;
	int					status;

	pid = getpid();
	status = 0;
	ft_printf("Process id: %d\n", pid);
	action.sa_flags = SA_NODEFER | SA_RESTART;
	action.sa_sigaction = &server_handler;
	sigemptyset(&(action.sa_mask));
	status += sigaction(SIGUSR1, &action, NULL);
	status += sigaction(SIGUSR2, &action, NULL);
	if (status)
		ft_raise_error("(minitalk) Error setting handler for signal", NULL, 1);
	while (1)
		;
	return (0);
}
