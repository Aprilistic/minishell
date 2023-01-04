/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:51:01 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/04 17:30:45 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_input(t_metadata **command, char **env)
{
	char	*commandline;
	int		idx;

	read_commandline(&commandline);
	allocate_command_slot(commandline, command);
	allocate_token_slot(commandline, command);
	save_token(commandline, command, env);
	merge_token(command);
	free(commandline);
	return (0);
}
