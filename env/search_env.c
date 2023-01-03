/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:19:33 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/03 22:43:56 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//returns matching index from env
static int	search_from_environ(char *token, char **env)
{
	int	env_index;

	env_index = 0;
	while (env[env_index])
	{
		if (!ft_strncmp(env[env_index], token, ft_strlen(token)))
			return (env_index);
		env_index++;
	}
	return (ERROR);
}

//returns matching value with allocated memory space.
char	*get_value_from_environ(char *key, char **env)
{
	char	*value;
	int		index;

	if (key[1] == 0)
		value = ft_strdup("$");
	else if (key[1] == '?')
		value = ft_itoa((unsigned short)exit_code);
	else
	{
		index = search_from_environ(key + 1, env);
		if (index == ERROR)
			value = ft_strdup("");
		else
			value = ft_strdup(ft_strchr(env[index], '=') + 1);
	}
	free(key);
	return (value);
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
