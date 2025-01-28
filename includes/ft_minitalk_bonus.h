/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minitalk_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:25:15 by luinasci          #+#    #+#             */
/*   Updated: 2025/01/22 19:12:15 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINITALK_BONUS_H
# define FT_MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <wchar.h>
# include <locale.h>
# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

typedef struct s_signal_data
{
	char	c;
	int		bit_count;
}	t_signal_data;

int		ft_count_utf8_bytes(unsigned char c);
wchar_t	*ft_convert_to_wchar(const char *str);
void	process_utf8_char(void);

#endif
