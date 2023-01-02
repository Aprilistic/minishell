/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:30:55 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/02 19:23:45 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define ERROR -1

typedef enum e_command_type
{
	builtin,
	redirection,
	systemcall
}	t_command_type;

typedef struct s_metadata
{
	int		token_count;
	char	**token;
	int		*token_quote_flag;
}			t_metadata;

/* read */
int			read_commandline(char **commandline);
void		allocate_command_slot(char *commandline, t_metadata **command);
void		allocate_token_slot(char *commandline, t_metadata **command);
void		save_token(char *commandline, t_metadata **command, char **env);
int			parse_input(t_metadata **command, char **env);

/* signal */
void		handler(int signum);

/* env */
char		*get_value_from_environ(char *key, char **env);

/* builtin */
int			builtin_echo(t_metadata *command);

#endif
