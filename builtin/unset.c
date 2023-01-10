/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:01:37 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/10 20:20:37 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_unset(t_metadata *command, char **env)
{
	int	token_index;
	int	env_count;
	int	env_index;

	token_index = 1;
	while (token_index < command->token_count)
	{
		env_index = search_from_environ(command->token[token_index], env);
		if (env_index == ERROR)
		{
			token_index++;
			continue ;
		}
		free(env[env_index]);
		env_count = 0;
		while (env[env_count])
			env_count++;
		while (env_index < env_count)
		{
			env[env_index] = env[env_index + 1];
			env_index++;
		}
		token_index++;
	}
	g_exit_code = 0;
}
