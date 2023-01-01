/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:51:01 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/01 15:34:13 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_input(t_metadata **command, char **env)
{
	char	*commandline;
	int		idx;

	read_commandline(&commandline);
	tokenize(commandline, command, env);
	free(commandline);
	return (0);
}
