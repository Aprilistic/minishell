# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/30 13:34:29 by jinheo            #+#    #+#              #
#    Updated: 2023/01/10 20:43:04 by jinheo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

LDFLAGS	= -L$(shell brew --prefix readline)/lib
CPPFLAGS = -I$(shell brew --prefix readline)/include

SRCS	= main.c read/read.c read/read_commandline.c \
			read/token_1_allocation.c read/token_2_parsing.c read/token_3_flag.c \
			read/token_4_env_replacing.c read/token_5_merging.c read/check_syntax.c\
			signal/signal.c execute/command_classification.c execute/accessibility_check.c \
			execute/command_utils.c	execute/command_builtin_check.c env/search_env.c \
			builtin/cd.c builtin/echo.c builtin/env.c builtin/exit.c \
			builtin/export.c builtin/export_addenv.c builtin/export_printenv.c \
			builtin/pwd.c builtin/unset.c \
			error/print_error.c env/allocate_env.c
			
OBJS	= $(SRCS:.c=.o)

NAME	= minishell

RM		= rm -rf

all : 	
			@make $(NAME)

$(NAME) : $(SRCS)
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
			@echo "Erasing exec file..."
			@$(RM) $(NAME)

re :
			@make fclean
			@make all
