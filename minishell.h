/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:30:55 by jinheo            #+#    #+#             */
/*   Updated: 2022/12/30 18:40:37 by jinheo           ###   ########.fr       */
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
	char				**token;
	int					token_count;
}						t_metadata;

/* read */
int						handle_input_line(char **commandline, char *prompt);
int						read_commandline(t_metadata **command, char **env);
int						create_t_metadata(t_metadata **ptr);

/* signal */
void					handler(int signum);

#endif
