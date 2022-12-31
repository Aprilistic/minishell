/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:19:33 by jinheo            #+#    #+#             */
/*   Updated: 2022/12/31 21:24:12 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//returns matching index from env
static int	search_from_environ(char *token, int token_size, char **env)
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

//returns matching value with allocated memory space.
char	*get_value_from_environ(char *key, char **env)
{
	int	index;

	index = search_from_environ(key, ft_strlen(key), env);
	if (index == ERROR)
		return (ft_strdup(""));
	return (ft_strdup(ft_strchr(env[index], '=') + 1));
}

void	add_env_var(char *key, char *value, char **env)
{
	int	env_index;

	env_index = 0;
	while (env[env_index])
		env_index++;
	//careful memory leak check needed
	env[env_index] = ft_strjoin(ft_strjoin(ft_strdup(key), ft_strdup("=")),
			ft_strdup(value));
	env[env_index + 1] = NULL;
}
