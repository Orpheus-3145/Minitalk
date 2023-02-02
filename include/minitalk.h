/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 19:25:14 by fra           #+#    #+#                 */
/*   Updated: 2023/01/30 23:13:53 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include "libft.h"

void	server_handler(int signum, siginfo_t *client, void *ucontext);

void	client_handler(int signum);

void	send_string(pid_t pid, char *string);

void	send_signal(pid_t pid, int condition);

int		check_pid(char *n);

#endif
