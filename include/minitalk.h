/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/16 19:25:14 by fra           #+#    #+#                 */
/*   Updated: 2023/03/30 02:03:40 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define MAX 1000
// # include <stdio.h>
# include <signal.h>    // signal(), sigemptyset(), kill(), getpid(), ...
# include <stdlib.h>    // malloc(), free(), exit()
// # include <stddef.h>
# include <unistd.h>    // write(), slep(), usleep()
# include <time.h>
# include <sys/time.h>
# include "libft.h"

// function called when server receives a signal type SIGUSR1 or SIGUSR2,
// it converts that signal into a bit, building the character and the string
// @param signum	--> type of signal
// @param client	--> istance that represents the client that sent the message
// @param ucontext  --> generic pointer (not used)
//
// return void
void	server_handler(int signum, siginfo_t *client, void *ucontext);

// function called when the client receives a signal type SIGUSR1 or SIGUSR2,
// it refresh a flag thet allows to send the next bit of the message
// @param signum	--> type of signal
//
// return void
void	client_handler(int signum);

// sends a message to the server, decomposing the sttring into characters and
// the chars into bits, it sends one and then waits for the response from the
// server
// @param pid		--> process id to send the message
// @param string	--> message to send
//
// return void
void	send_string(pid_t pid, char *string);

// checks if the process is running, if so it sends a signal (SIGUSR1 or
// SIGUSR2) dependeing if condition is 0 or 1
// @param pid		--> process id to send the signal
// @param condition	--> condition == 0 -->SIGUSR1, opposite otherwise
//
// return void
void	send_signal(pid_t pid, int condition);

// checks if the strings received is a pid: i.e. is a number greater than zero,
// and the relative process is running
// @param n	--> string to check
//
// return true/false
int		check_pid(char *n);

#endif
