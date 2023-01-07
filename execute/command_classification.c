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

// typedef struct s_metadata
// {
// 	int		token_count;
// 	char	**token;
// 	int		*token_merge_flag;
// }			t_metadata;

//cat argfile > outfile
//cat argfile >> outfile
//                       -----> cat argfile NULL outfile
//  					 -----> cat argfile NULL outfile  
int	save[2];

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

//cmd 위치 바꾸기 command로 redirection 빼고
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

void	deal_with_heredoc(t_metadata *cmd, int idx, int *change_cnt)
{
	int		fd;
	char	*line;

	if (access(HEREDOC_FILE, W_OK | R_OK) == -1)
		unlink(HEREDOC_FILE);
	fd = open(HEREDOC_FILE, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
		return (perror(""));
	dup2(save[0], STDIN_FILENO);
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

void	adjust_cmd(t_metadata *cmd, int change_cnt)
{
	int		i;
	int		put_pos;
	char	**new_token;

	new_token =\
		(char **)malloc(sizeof(char *) * (cmd->token_count - change_cnt + 1));
	new_token[cmd->token_count - change_cnt] = NULL;
	put_pos = 0;
	i = -1;
	while (++i < cmd->token_count)
		if (cmd->token[i] != NULL)
			new_token[put_pos++] = cmd->token[i];
	free(cmd->token);
	cmd->token = new_token;
}

void	deal_with_redirection(t_metadata *cmd)
{
	int	i;
	int	change_cnt;

	change_cnt = 0;
	i = -1;
	while (++i < cmd->token_count)
	{
		if (cmd->token[i] == NULL)
			continue ;
		if (!ft_strcmp(cmd->token[i], ">"))
			deal_with_output(cmd, i, &change_cnt);
		else if (!ft_strcmp(cmd->token[i], ">>"))
			deal_with_append(cmd, i, &change_cnt);
		else if (!ft_strcmp(cmd->token[i], "<"))
			deal_with_input(cmd, i, &change_cnt);
		else if (!ft_strcmp(cmd->token[i], "<<"))
			deal_with_heredoc(cmd, i, &change_cnt);
	}
	if (change_cnt > 0)
		adjust_cmd(cmd, change_cnt);
}

void	run_cmd(t_metadata *cmd)
{
	int		i;
	char	*path;
	char	*cmd_file;
	char	**splited_path;

	//if (cmd가 빌트인)
		//빌트인 처리
		//return ;
	deal_with_redirection(cmd);
	path = getenv("PATH");
	splited_path = ft_split(path, ':');
	i = -1;
	while (splited_path[++i])
	{
		cmd_file = ft_strjoin(splited_path[i], ft_strdup("/"));
		cmd_file = ft_strjoin(cmd_file, ft_strdup(cmd->token[0]));
		if (access(cmd_file, X_OK) == 0)
			execve(cmd_file, cmd->token, NULL);
	}
	free(cmd_file);
	free(splited_path);
	execve(cmd->token[0], cmd->token, NULL);
	perror("");
	exit(0);
}

int	execute(t_metadata *cmd)
{
	int	idx;
	int	old_fd[2];
	int	new_fd[2];

	old_fd[0] = STDIN_FILENO;
	new_fd[1] = STDOUT_FILENO;
	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	idx = -1;
	while (cmd[++idx].token != NULL)
	{
		if (cmd[idx + 1].token != NULL)
			pipe(new_fd);
		if (fork() == 0)
		{
			dup2(old_fd[0], STDIN_FILENO);
			if (cmd[idx + 1].token != NULL)
				dup2(new_fd[1], STDOUT_FILENO);
			run_cmd(&cmd[idx]);
		}
		close(old_fd[0]);
		close(new_fd[1]);
		ft_memcpy(old_fd, new_fd, sizeof(int) * 2);
	}
	dup2(save[0], STDIN_FILENO);
	dup2(save[1], STDOUT_FILENO);
	while (idx--)
		waitpid(-1, NULL, 0);
	return (1);
}
