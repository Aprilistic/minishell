/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accessibility_check.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:40:07 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/10 13:30:05 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_access_error(char *path)
{
	write(STDERR_FILENO, E_PROMPT, ft_strlen(E_PROMPT));
	write(STDERR_FILENO, path, ft_strlen(path));
	perror(": ");
}

int	accessibility_check(char *path)
{
	if (access(path, F_OK))
	{
		print_error(E_PROMPT, NULL, path, "command not found");
		return (127);
	}
	else if (access(path, X_OK))
	{
		print_access_error(path);
		return (126);
	}
	return (0);
}
