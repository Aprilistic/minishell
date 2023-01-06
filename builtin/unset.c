/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:01:37 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/06 15:48:22 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	

void	builtin_unset(t_metadata *command, char **env)
{
	int	token_index;
	int	env_index;

	token_index = 1;
	while (token_index < command->token_count)
	{
		env_index = search_from_environ(command->token[token_index], env);
		if (env_index == ERROR)
			continue ;
		
		token_index++;
	}
}
