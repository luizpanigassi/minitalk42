/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:51:46 by luinasci          #+#    #+#             */
/*   Updated: 2025/01/22 16:19:39 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minitalk.h"

int	g_bit_received = FALSE;

void	receive_signal(int sign)
{
	if (sign == SIGUSR1)
		g_bit_received = TRUE;
}

void	send_char(int pid, char *str, size_t len_str)
{
	int		bit;
	size_t	str_size;

	str_size = 0;
	while (str_size <= len_str)
	{
		bit = 0;
		while (bit < 8)
		{
			if ((str[str_size] >> bit) & 1)
				kill (pid, SIGUSR2);
			else
				kill (pid, SIGUSR1);
			bit++;
			usleep(10000);
			while (!g_bit_received)
				pause();
			g_bit_received = FALSE;
		}
		str_size++;
	}
}

int	main(int argc, char **argv)
{
	int					server_pid;
	struct sigaction	client_signal;

	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		client_signal.sa_handler = receive_signal;
		client_signal.sa_flags = 0;
		sigemptyset(&client_signal.sa_mask);
		sigaction(SIGUSR1, &client_signal, NULL);
		send_char(server_pid, argv[2], ft_strlen(argv[2]));
	}
	else
	{
		ft_printf("Something is wrong, here is how to use it: \n");
		ft_printf(" Type ./client [server PID] [\"message\"]\n");
	}
	return (0);
}
