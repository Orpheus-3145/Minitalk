/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 19:25:04 by fra           #+#    #+#                 */
/*   Updated: 2023/03/20 20:24:47 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#define MAX 1000

void	server_handler(int signum, siginfo_t *client, void *ucontext)
{
	static int	i = 0, len = 0, maxlen = 0;
	static char	received;
	static char *msg;
	char * tmp;
	int			end_msg;

	(void) ucontext;
	received <<= 1;
	received += signum == SIGUSR2;
	end_msg = 0;
	
	if (++i == 8)
	{
		end_msg = ! received;
		msg[len] = received;
		len++;
		i = 0;
	}
	if (len == maxlen)
	{
		maxlen += MAX;
		tmp = malloc(maxlen);
		ft_strlcpy(tmp, msg, maxlen - MAX + 1);
		free(msg);
		msg = tmp;
	}
	send_signal(client->si_pid, end_msg);
	if (! end_msg)
		return ;
	ft_printf("%s\n", msg);
	free(msg);
	msg = NULL;
	maxlen = 0;
	len = 0;
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
