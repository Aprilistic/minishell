/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_classification.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:48:05 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/03 20:40:35 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// typedef struct s_metadata
// {
// 	int		token_count;
// 	char	**token;
// 	int		*token_merge_flag;
// }			t_metadata;

//명령어가 빌트인일 때랑 아닐 때 나누기

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	deal_with_output(t_metadata *cmd, int idx)
{
	int	fd;

	fd = open(cmd->token[idx + 1], O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (perror(""));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(cmd->token[idx]);
	cmd->token[idx] = NULL;
}

void	deal_with_append(t_metadata *cmd, int idx)
{
	int	fd;

	fd = open(cmd->token[idx + 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		return (perror(""));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	free(cmd->token[idx]);
	cmd->token[idx] = NULL;
}

void	deal_with_input(t_metadata *cmd, int idx)
{
	int	fd;

	fd = open(cmd->token[idx + 1], O_RDONLY);
	if (fd == -1)
		return (perror(""));
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(cmd->token[idx]);
	cmd->token[idx] = NULL;
}

void	deal_with_heredoc(t_metadata *cmd, int idx)
{
	int		fd;
	char	*line;
	char	*limiter;

	fd = open(HEREDOC_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (perror(""));
	limiter = ft_strjoin(ft_strdup(cmd->token[idx + 1]), ft_strdup("\n"));
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, limiter))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(cmd->token[idx]);
	cmd->token[idx] = NULL;
}

void	deal_with_redirection(t_metadata *cmd)
{
	int	i;

	i = 0;
	while (cmd->token[i])
	{
		if (!ft_strcmp(cmd->token[i], ">"))
			deal_with_output(cmd, i);
		if (!ft_strcmp(cmd->token[i], ">>"))
			deal_with_append(cmd, i);
		if (!ft_strcmp(cmd->token[i], "<"))
			deal_with_input(cmd, i);
		if (!ft_strcmp(cmd->token[i], "<<"))
			deal_with_heredoc(cmd, i);
		i++;
	}
	return (0);
}

void	run_cmd(t_metadata *cmd)
{
	//if (cmd가 빌트인)
		//빌트인 처리
		//return ;
	deal_with_redirection(cmd);
	execve(cmd->token[0], cmd->token, NULL);
}

int	execute(t_metadata *cmd)
{
	int	idx;
	int	old_fd[2];
	int	new_fd[2];

	old_fd[0] = STDIN_FILENO;
	idx = 0;
	while (cmd[idx].token != NULL)
	{
		pipe(new_fd);
		if (fork() == 0)
		{
			//전에 있던 결과물을 입력값으로 받게 만든다.
			dup2(old_fd[0], STDIN_FILENO);
			//출력값을 new_fd로 보내게 만든다.
			dup2(new_fd[1], STDOUT_FILENO);
			//명령어 실행
			run_cmd(&cmd[idx]);
		}
		close(old_fd[0]);
		close(new_fd[1]);
		ft_memcpy(old_fd, new_fd, sizeof(int) * 2);
		idx++;
	}
}
