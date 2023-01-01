/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:30:55 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/01 15:32:24 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/libft.h"
# include <stdio.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define ERROR -1

typedef struct s_metadata
{
	char	**token;
	int		token_count;
}			t_metadata;

/* read */
int			read_commandline(char **commandline);
int			tokenize(char *commandline, t_metadata **command, char **env);
int			parse_input(t_metadata **command, char **env);

/* signal */
void		handler(int signum);

/* env */
char		*get_value_from_environ(char *key, char **env);

#endif
