/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:48:05 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/06 17:03:47 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	deal_with_output(t_metadata *cmd, int idx, int *change_cnt)
{
	int	fd;

	fd = open(cmd->token[idx + 1], O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (perror(""));
	dup2(fd, STDOUT_FILENO);
	close(fd);
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
		return (perror(""));
	dup2(fd, STDOUT_FILENO);
	close(fd);
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
		return (perror(""));
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(cmd->token[idx]);
	free(cmd->token[idx + 1]);
	cmd->token[idx] = NULL;
	cmd->token[idx + 1] = NULL;
	(*change_cnt) += 2;
}

void	deal_with_heredoc(t_metadata *cmd, int idx, int *change_cnt, t_exec *exec)
{
	int		fd;
	char	*line;

	if (access(HEREDOC_FILE, W_OK | R_OK) == -1)
		unlink(HEREDOC_FILE);
	fd = open(HEREDOC_FILE, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
		return (perror(""));
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
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(cmd->token[idx]);
	free(cmd->token[idx + 1]);
	cmd->token[idx] = NULL;
	cmd->token[idx + 1] = NULL;
	(*change_cnt) += 2;
}
