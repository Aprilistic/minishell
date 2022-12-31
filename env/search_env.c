/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:19:33 by jinheo            #+#    #+#             */
/*   Updated: 2022/12/31 18:46:44 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//returns matching index from env
int	search_from_environ(char *token, int token_size, char **env)
{
	int	env_index;

	env_index = 0;
	while (env[env_index])
	{
		if (!ft_strncmp(env[env_index], token, token_size))
			return (env_index);
		env_index++;
	}
	return (ERROR);
}
