/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:51:01 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/10 20:40:57 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_input(t_metadata **command, char **env)
{
	char	*commandline;

	read_commandline(&commandline, env);
	allocate_command_slot(commandline, command);
	allocate_token_slot(commandline, command);
	save_token(commandline, command, env);
	merge_token(command);
	free(commandline);
	if (check_syntax(*command) == ERROR)
		return (ERROR);
	return (0);
}
