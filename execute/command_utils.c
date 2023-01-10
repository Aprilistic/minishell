/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:48:05 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/08 17:56:53 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_helper(t_exec *exec, int should_init)
{
	if (should_init)
	{
		exec->old_fd[0] = STDIN_FILENO;
		exec->new_fd[1] = STDOUT_FILENO;
		exec->save[0] = dup(STDIN_FILENO);
		exec->save[1] = dup(STDOUT_FILENO);
		exec->idx = -1;
		ignore_sigint();
		return ;
	}
	dup2(exec->save[0], STDIN_FILENO);
	dup2(exec->save[1], STDOUT_FILENO);
	close(exec->save[0]);
	close(exec->save[1]);
}

void	deal_with_output(t_metadata *cmd, int idx, int *change_cnt)
{
	int	fd;

	fd = open(cmd->token[idx + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		perror("");
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	free(cmd->token[idx]);
	free(cmd->token[idx + 1]);
	cmd->token[idx] = NULL;
	cmd->token[idx + 1] = NULL;
	(*change_cnt) += 2;
}

void	deal_with_append(t_metadata *cmd, int idx, int *change_cnt)
{
	int	fd;

	fd = open(cmd->token[idx + 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		perror("");
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	free(cmd->token[idx]);
	free(cmd->token[idx + 1]);
	cmd->token[idx] = NULL;
	cmd->token[idx + 1] = NULL;
	(*change_cnt) += 2;
}

void	deal_with_input(t_metadata *cmd, int idx, int *change_cnt)
{
	int	fd;

	fd = open(cmd->token[idx + 1], O_RDONLY);
	if (fd == -1)
		perror("");
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	free(cmd->token[idx]);
	free(cmd->token[idx + 1]);
	cmd->token[idx] = NULL;
	cmd->token[idx + 1] = NULL;
	(*change_cnt) += 2;
}

void	deal_with_heredoc(t_metadata *cmd, int idx,
	int *change_cnt, t_exec *exec)
{
	int		fd;
	char	*line;

	unlink(HEREDOC_FILE);
	fd = open(HEREDOC_FILE, O_CREAT | O_RDWR, 0644);
	dup2(exec->save[0], STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, cmd->token[idx + 1]))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	fd = open(HEREDOC_FILE, O_CREAT | O_RDWR, 0644);
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(cmd->token[idx]);
	free(cmd->token[idx + 1]);
	cmd->token[idx] = NULL;
	cmd->token[idx + 1] = NULL;
	(*change_cnt) += 2;
}
