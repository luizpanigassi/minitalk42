/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:31:55 by luinasci          #+#    #+#             */
/*   Updated: 2025/01/22 18:38:11 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_minitalk_bonus.h"

wchar_t	*ft_convert_to_wchar(const char *str)
{
	size_t	i;
	size_t	len;
	wchar_t	*wstr;

	len = mbstowcs(NULL, str, 0);
	if (len == (size_t)-1)
	{
		ft_printf("Error: Invalid UTF-8 string.\n");
		exit(EXIT_FAILURE);
	}
	wstr = malloc((len + 1) * sizeof(wchar_t));
	if (!wstr)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < len + 1)
	{
		wstr[i] = L'\0';
		i++;
	}
	mbstowcs(wstr, str, len + 1);
	return (wstr);
}

int	ft_count_utf8_bytes(unsigned char c)
{
	if ((c & 0x80) == 0)
		return (1);
	else if ((c & 0xE0) == 0xC0)
		return (2);
	else if ((c & 0xF0) == 0xE0)
		return (3);
	else if ((c & 0xF8) == 0xF0)
		return (4);
	else
	{
		ft_printf("Error: Invalid UTF-8 byte.\n");
		exit(EXIT_FAILURE);
	}
}
