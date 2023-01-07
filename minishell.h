/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:30:55 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/07 16:41:33 by jinheo           ###   ########.fr       */
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
# define HEREDOC_FILE "/tmp/.here_doc"

# define F_PROMPT "미니쉘: "
# define S_PROMPT "> "

int			exit_code;

typedef enum e_command_type
{
	builtin,
	redirection,
	systemcall
}			t_command_type;

typedef struct s_metadata
{
	int		token_count;
	char	**token;
	int		*token_quote_flag;
	int		*token_merge_flag;
}			t_metadata;

/* read */
int			read_commandline(char **commandline);
int			parse_input(t_metadata **command, char **env);
void		save_token(char *commandline, t_metadata **command, char **env);
void		merge_token(t_metadata **command);

/* token related functions */
char		*skip_current_token(char *addr);
void		allocate_command_slot(char *commandline, t_metadata **command);
void		allocate_t_metadata(t_metadata *command, int token_count);
void		allocate_token_slot(char *commandline, t_metadata **command);
void		replace_env_variable(char **token, char **env);

/* signal */
void		handler(int signum);

/* env */
char		*get_key_from_environ(int index, char **env);
char		*get_value_from_environ(char *key, char **env);
int			search_from_environ(char *token, char **env);

/* execute */
int			execute(t_metadata *cmd);

/* builtin */
void		builtin_echo(t_metadata *command);
void		builtin_env(char **env);
void		builtin_exit(t_metadata *command);
void		builtin_export(t_metadata *command, char **env);
void		builtin_pwd(char **env);
void		builtin_unset(t_metadata *command, char **env);

void		print_sorted_env(char **env);
int			modify_env(char *token, char **env);
int			put_env(t_metadata *command, char **env);

/* error */
void		print_error(char *prompt, char *command,
				char *token, char *message);

#endif
