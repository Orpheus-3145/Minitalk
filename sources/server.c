/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 19:25:04 by fra           #+#    #+#                 */
/*   Updated: 2023/02/02 15:16:51 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	server_handler(int signum, siginfo_t *client, void *ucontext)
{
	static int	i;
	static char	received;
	static char *msg;
	int			end_msg;

	(void) ucontext;
	received <<= 1;
	received += signum == SIGUSR2;
	end_msg = 0;
	if (++i == 8)
	{
		if (! ft_append_char(received, &msg))
			ft_raise_error("Memory not available", (void *) &msg, 1);
		end_msg = ! received;
		i = 0;
	}
	send_signal(client->si_pid, end_msg);
	if (! end_msg)
		return ;
	ft_printf("%s\n", msg);
	free(msg);
	msg = NULL;
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
		ft_raise_error("Error setting handler for signal", NULL, 1);
	while (1)
		;
	return (0);
}
