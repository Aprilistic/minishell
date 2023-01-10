/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessibility_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:40:07 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/10 15:08:05 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_access_error(char *path)
{
	write(STDERR_FILENO, E_PROMPT, ft_strlen(E_PROMPT));
	write(STDERR_FILENO, path, ft_strlen(path));
	perror(": ");
}

void	accessibility_check(char *path)
{
	if (path == NULL)
		exit(0);
	if (*path == '<' || *path == '>')
		exit(0);
	if (access(path, F_OK))
	{
		print_error(E_PROMPT, NULL, path, "command not found");
		exit(127);
	}
	else if (access(path, X_OK))
	{
		print_access_error(path);
		exit(126);
	}
}
