# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/30 13:34:29 by jinheo            #+#    #+#              #
#    Updated: 2022/12/30 19:47:39 by jinheo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
#CFLAGS = -Wall -Wextra -Werror

LDFLAGS	= -L$(shell brew --prefix readline)/lib
CPPFLAGS = -I$(shell brew --prefix readline)/include

SRCS	= main.c read/read.c read/read_commandline.c read/tokenize.c signal/signal.c
OBJS	= $(SRCS:.c=.o)

NAME	= minishell

RM		= rm -rf

all : 	
			@make $(NAME)

$(NAME) : $(SRC)
			@make -C libft all
			@echo "Compiling minishell..."
			@make $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) libft/libft.a -lreadline $(LDFLAGS) $(CPPFLAGS) -o $(NAME)
			@echo "Done!"

libft :
			@make -C libft

.c.o :
			@${CC} ${CFLAGS} $(CPPFLAGS) -c $< -o $@

clean : 	
			@make -C libft clean
			@echo "Erasing .o files..."
			@$(RM) $(OBJS)

fclean : 	
			@make -C libft fclean
			@make clean
			@echo "Erasing exec files..."
			@$(RM) $(NAME)

re :
			@make fclean
			@make all