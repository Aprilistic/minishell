/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_classification.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:48:05 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/06 17:03:47 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	adjust_cmd(t_metadata *cmd, int change_cnt)
{
	int		i;
	int		put_pos;
	char	**new_token;

	new_token
		= (char **)malloc(sizeof(char *) * (cmd->token_count - change_cnt + 1));
	new_token[cmd->token_count - change_cnt] = NULL;
	put_pos = 0;
	i = -1;
	while (++i < cmd->token_count)
		if (cmd->token[i] != NULL)
			new_token[put_pos++] = cmd->token[i];
	free(cmd->token);
	cmd->token = new_token;
}

void	deal_with_redirection(t_metadata *cmd, t_exec *exec)
{
	int	i;
	int	change_cnt;

	change_cnt = 0;
	i = -1;
	while (++i < cmd->token_count)
	{
		if (cmd->token[i] == NULL || cmd->token_quote_flag[i])
			continue ;
		if (!ft_strcmp(cmd->token[i], ">"))
			deal_with_output(cmd, i, &change_cnt);
		else if (!ft_strcmp(cmd->token[i], ">>"))
			deal_with_append(cmd, i, &change_cnt);
		else if (!ft_strcmp(cmd->token[i], "<"))
			deal_with_input(cmd, i, &change_cnt);
		else if (!ft_strcmp(cmd->token[i], "<<"))
			deal_with_heredoc(cmd, i, &change_cnt, exec);
	}
	if (change_cnt > 0)
		adjust_cmd(cmd, change_cnt);
}

void	run_cmd(t_metadata *cmd, t_exec *exec, char **env)
{
	int		i;
	char	*path;
	char	*cmd_file;
	char	**splited_path;

	//if (cmd가 빌트인)
	deal_with_redirection(cmd, exec);
	path = getenv("PATH");
	splited_path = ft_split(path, ':');
	i = -1;
	while (splited_path[++i])
	{
		cmd_file = ft_strjoin(splited_path[i], ft_strdup("/"));
		cmd_file = ft_strjoin(cmd_file, ft_strdup(cmd->token[0]));
		if (access(cmd_file, X_OK) == 0)
		{
			for (int i = 0; cmd->token[i]; i++)
				printf("%s\n", cmd->token[i]);
			execve(cmd_file, cmd->token, env);
		}
		free(cmd_file);
	}
	free(splited_path);
	execve(cmd->token[0], cmd->token, env);
	perror("");
	exit(0);
}

void	exec_helper(t_exec *exec, int should_init)
{
	if (should_init)
	{
		exec->old_fd[0] = STDIN_FILENO;
		exec->new_fd[1] = STDOUT_FILENO;
		exec->save[0] = dup(STDIN_FILENO);
		exec->save[1] = dup(STDOUT_FILENO);
		return ;
	}
	dup2(exec->save[0], STDIN_FILENO);
	dup2(exec->save[1], STDOUT_FILENO);
	close(exec->save[0]);
	close(exec->save[1]);
}

void	execute(t_metadata *cmd, char **env)
{
	int		idx;
	t_exec	exec;

	exec_helper(&exec, 1);
	idx = -1;
	while (cmd[++idx].token != NULL)
	{
		if (cmd[idx + 1].token != NULL)
			pipe(exec.new_fd);
		exec.pid = fork();
		if (exec.pid == 0)
		{
			if (cmd[idx + 1].token != NULL)
				dup2(exec.new_fd[1], STDOUT_FILENO);
			dup2(exec.old_fd[0], STDIN_FILENO);
			run_cmd(&cmd[idx], &exec, env);
		}
		close(exec.new_fd[1]);
		close(exec.old_fd[0]);
		ft_memcpy(exec.old_fd, exec.new_fd, sizeof(int) * 2);
	}
	while (idx--)
		if (exec.pid == waitpid(-1, &exec.status, 0))
			g_exit_code = exec.status;
	exec_helper(&exec, 0);
}
