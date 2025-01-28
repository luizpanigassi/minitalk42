/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:51:46 by luinasci          #+#    #+#             */
/*   Updated: 2025/01/22 19:13:43 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minitalk_bonus.h"

int	g_bit_received = FALSE;

void	receive_signal(int sign)
{
	if (sign == SIGUSR1)
		g_bit_received = TRUE;
}

void	send_bit(int pid, unsigned char byte, int bit)
{
	if ((byte >> bit) & 1)
		kill(pid, SIGUSR2);
	else
		kill(pid, SIGUSR1);
	usleep(10000);
	while (!g_bit_received)
		pause();
	g_bit_received = FALSE;
}

void	send_unicode_char(int pid, wchar_t wc)
{
	char	buffer[MB_LEN_MAX];
	int		byte_count;
	int		i;
	int		bit;

	byte_count = wctomb(buffer, wc);
	if (byte_count == -1)
	{
		ft_printf("Error: Invalid Unicode character.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < byte_count)
	{
		bit = 0;
		while (bit < 8)
		{
			send_bit(pid, buffer[i], bit);
			bit++;
		}
		i++;
	}
}

void	send_unicode_message(int pid, wchar_t *wstr)
{
	size_t	i;

	i = 0;
	while (wstr[i] != L'\0')
	{
		send_unicode_char(pid, wstr[i]);
		i++;
	}
	send_unicode_char(pid, L'\0');
}

int	main(int argc, char **argv)
{
	int					server_pid;
	wchar_t				*unicode_message;
	struct sigaction	client_signal;

	setlocale(LC_ALL, "");
	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		unicode_message = ft_convert_to_wchar(argv[2]);
		client_signal.sa_handler = receive_signal;
		client_signal.sa_flags = 0;
		sigemptyset(&client_signal.sa_mask);
		sigaction(SIGUSR1, &client_signal, NULL);
		send_unicode_message(server_pid, unicode_message);
		free(unicode_message);
	}
	else
	{
		ft_printf("Usage: ./client [server PID] [message]\n");
	}
	return (0);
}
