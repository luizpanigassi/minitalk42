/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:51:48 by luinasci          #+#    #+#             */
/*   Updated: 2025/01/22 19:14:25 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minitalk_bonus.h"

t_signal_data	g_msg = {0, 0};

void	process_utf8_char(void)
{
	static char	utf8_char[MB_LEN_MAX];
	static int	byte_index = 0;
	static int	total_bytes = 0;

	utf8_char[byte_index++] = g_msg.c;
	if (byte_index == 1)
	{
		total_bytes = ft_count_utf8_bytes(g_msg.c);
	}
	if (byte_index == total_bytes)
	{
		if (utf8_char[0] == '\0')
		{
			write(1, "\n", 1);
		}
		else
		{
			write(1, utf8_char, total_bytes);
		}
		byte_index = 0;
		total_bytes = 0;
	}
	g_msg.c = 0;
	g_msg.bit_count = 0;
}

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
		process_utf8_char();
	}
	if (kill(info->si_pid, SIGUSR1))
		exit(EXIT_FAILURE);
}

int	main(void)
{
	struct sigaction	sa;

	setlocale(LC_ALL, "");
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
