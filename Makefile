# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/17 17:55:29 by luinasci          #+#    #+#              #
#    Updated: 2025/01/22 19:10:13 by luinasci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk

SERVER = server
CLIENT = client

SRCS_SERVER = server.c
SRCS_CLIENT = client.c
HEADERS = includes/ft_minitalk.h

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

SRCS_SERVER_BONUS = server_bonus.c utils_bonus.c
SRCS_CLIENT_BONUS = client_bonus.c utils_bonus.c
HEADERS_BONUS = includes/ft_minitalk_bonus.h

OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -Iinclude -I$(LIBFT_DIR)
CC = cc

all: $(SERVER) $(CLIENT) $(LIBFT)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(SERVER): $(OBJS_SERVER) $(HEADERS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJS_SERVER) $(LIBFT)

$(CLIENT): $(OBJS_CLIENT) $(HEADERS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJS_CLIENT) $(LIBFT)

bonus: $(SERVER)_bonus $(CLIENT)_bonus

$(SERVER)_bonus: $(OBJS_SERVER_BONUS) $(HEADERS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(SERVER)_bonus $(OBJS_SERVER_BONUS) $(LIBFT)

$(CLIENT)_bonus: $(OBJS_CLIENT_BONUS) $(HEADERS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(CLIENT)_bonus $(OBJS_CLIENT_BONUS) $(LIBFT)

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT) $(SERVER)_bonus $(CLIENT)_bonus
	$(MAKE) -C $(LIBFT_DIR) clean

re: fclean all

.PHONY: all clean fclean re bonus
