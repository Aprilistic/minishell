/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:35:05 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/10 20:36:53 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	allocate_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		env[i] = ft_strdup(env[i]);
		i++;
	}
}

void	free_env(char **env)
{
	int	env_index;

	env_index = 0;
	while (env[env_index])
	{
		free(env[env_index]);
		env_index++;
	}
}
