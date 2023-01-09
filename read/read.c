/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:51:01 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/09 14:11:40 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_input(t_metadata **command, char **env)
{
	char	*commandline;

	read_commandline(&commandline);
	if (check_syntax(commandline) == ERROR)
	{
		g_exit_code = 2;
		print_error(E_PROMPT, NULL, NULL, "syntax error");
		return (ERROR);
	}
	allocate_command_slot(commandline, command);
	allocate_token_slot(commandline, command);
	save_token(commandline, command, env);
	merge_token(command);
	free(commandline);
	return (0);
}
