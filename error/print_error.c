/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 14:57:36 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/08 16:43:22 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(char *prompt, char *command, char *token, char *message)
{
	if (prompt)
	{
		write(STDERR_FILENO, prompt, ft_strlen(prompt));
	}
	if (command)
	{
		write(STDERR_FILENO, command, ft_strlen(command));
		write(STDERR_FILENO, ": ", 2);
	}
	if (token)
	{
		write(STDERR_FILENO, token, ft_strlen(token));
		write(STDERR_FILENO, ": ", 2);
	}
	if (message)
		write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}
