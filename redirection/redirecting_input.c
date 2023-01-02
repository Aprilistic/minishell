/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:08:05 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/02 14:13:22 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_file(char *infile, char **envp)
{
	int	fd[2];
	int	pid;
	int	status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (access(infile, R_OK) < 0)
		{
			write(STDERR_FILENO, "Can't open file: ", 17);
			write(STDERR_FILENO, infile, ft_strlen(infile));
			write(STDERR_FILENO, "\n", 1);
			exit(0);
		}
		dup2(open(infile, O_RDONLY), STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execute_command("cat", envp);
		exit(0);
	}
	waitpid(pid, &status, WNOHANG);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
}
