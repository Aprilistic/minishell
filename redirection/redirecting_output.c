/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:08:46 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/02 14:08:02 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirecting_output(t_metadata *command)
{
	
}

void	close_file(char *outfile, char **envp, int append)
{
	int	fd[2];
	int	pid;
	int	status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (!access(outfile, W_OK) || (access(outfile, F_OK) == -1))
		{
			if (append)
				dup2(open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644),
					STDOUT_FILENO);
			else
				dup2(open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644),
					STDOUT_FILENO);
			execute_command("cat", envp);
		}
		else
			perror("");
		exit(0);
	}
	waitpid(pid, &status, WNOHANG);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
}
