/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:04:24 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/08 16:05:16 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_export(t_metadata *command, char **env)
{
	int	exit_status;
	int	token_index;

	exit_status = 0;
	if (command->token_count == 1)
	{
		print_sorted_env(env);
		exit_status = 0;
	}
	else
	{
		token_index = 1;
		while (token_index < command->token_count)
		{
			exit_status |= put_env(command, env);
			token_index++;
		}
	}
	g_exit_code = exit_status;
}
