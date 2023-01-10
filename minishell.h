/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:30:55 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/10 21:10:07 by jinheo           ###   ########.fr       */
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

# define F_PROMPT "M I N I S H E L L $ "
# define S_PROMPT "> "
# define E_PROMPT "M I N I S H E L L : "

int			g_exit_code;

typedef struct s_metadata
{
	int		token_count;
	char	**token;
	int		*token_quote_flag;
	int		*token_merge_flag;
}			t_metadata;

typedef struct s_exec
{
	int		idx;
	int		pid;
	int		status;
	int		save[2];
	int		old_fd[2];
	int		new_fd[2];
}			t_exec;

/* read */
int			read_commandline(char **commandline, char **env);
int			parse_input(t_metadata **command, char **env);
int			check_syntax(t_metadata *command);
void		save_token(char *commandline, t_metadata **command, char **env);
void		merge_token(t_metadata **command);

/* token related functions */
char		*skip_current_token(char *addr);
void		allocate_command_slot(char *commandline, t_metadata **command);
void		allocate_token_slot(char *commandline, t_metadata **command);
void		replace_env_variable(char **token, char **env);
int			check_quote_flag(char *commandline);
int			check_merge_flag(char *commandline);

/* signal */
void		sigint_handler(int signum);
void		handle_signal(void);
void		change_signal(void);
void		ignore_sigint(void);
void		child_signal_handler(int signum);

/* env */
char		*get_key_from_environ(int index, char **env);
char		*get_value_from_environ(char *key, char **env);
int			search_from_environ(char *token, char **env);
void		allocate_env(char **env);
void		free_env(char **env);

/* execute */
void		deal_with_output(t_metadata *cmd, int idx, int *change_cnt);
void		deal_with_append(t_metadata *cmd, int idx, int *change_cnt);
void		deal_with_input(t_metadata *cmd, int idx, int *change_cnt);
void		deal_with_heredoc(t_metadata *cmd, int idx, int *change_cnt,
				t_exec *exec);
void		deal_with_redirection(t_metadata *cmd, t_exec *exec);
void		exec_helper(t_exec *exec, int should_init);
void		execute(t_metadata *cmd, char **env);

int			check_builtin(t_metadata *command, char **env, t_exec *exec);
void		accessibility_check(char *path);

/* builtin */
void		builtin_cd(t_metadata *command, char **env);
void		builtin_echo(t_metadata *command);
void		builtin_env(char **env);
void		builtin_exit(t_metadata *command);
void		builtin_export(t_metadata *command, char **env);
void		builtin_pwd(void);
void		builtin_unset(t_metadata *command, char **env);

void		print_sorted_env(char **env);
int			modify_env(char *token, char **env);
int			put_env(t_metadata *command, char **env);

/* error */
int			print_error(char *prompt, char *command, char *token,
				char *message);

#endif
