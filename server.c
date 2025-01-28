/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:51:48 by luinasci          #+#    #+#             */
/*   Updated: 2025/01/22 17:47:56 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minitalk.h"

t_signal_data	g_msg = {0, 0};

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
		g_msg.c &= ~(1 << g_msg.bit_count);
	else if (signum == SIGUSR2)
		g_msg.c |= (1 << g_msg.bit_count);
	g_msg.bit_count++;
	if (g_msg.bit_count == 8)
	{
		if (g_msg.c == '\0')
			write (1, "\n", 1);
		else
			write (1, &g_msg.c, 1);
		g_msg.c = 0;
		g_msg.bit_count = 0;
	}
	if (kill(info->si_pid, SIGUSR1))
		exit(EXIT_FAILURE);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("- WELCOME TO A RANDOM SERVER -\n");
	ft_printf("Your server PID is: ");
	ft_printf("%d\n", getpid());
	ft_printf("The server is now ready for your messages!\n");
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}
