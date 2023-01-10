/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 18:19:33 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/10 20:36:51 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key_from_environ(int index, char **env)
{
	char	*key;
	int		key_size;

	if (ft_strchr(env[index], '=') == NULL)
		key = ft_strdup(env[index]);
	else
	{
		key_size = ft_strchr(env[index], '=') - env[index];
		key = ft_calloc(sizeof(char), key_size + 1);
		key = ft_memcpy(key, env[index], key_size);
	}
	return (key);
}

//returns matching index from env
int	search_from_environ(char *token, char **env)
{
	char	*key;
	int		env_index;
	int		ret;

	env_index = 0;
	ret = ERROR;
	while (env[env_index])
	{
		key = get_key_from_environ(env_index, env);
		if (!ft_strcmp(key, token))
		{
			free(key);
			ret = env_index;
			break ;
		}
		free(key);
		env_index++;
	}
	return (ret);
}

//returns matching value with allocated memory space.
char	*get_value_from_environ(char *key, char **env)
{
	char	*value;
	int		index;

	if (key[0] == 0)
		value = ft_strdup("");
	else if (key[1] == 0)
		value = ft_strdup("$");
	else if (key[1] == '?')
		value = ft_itoa((unsigned short)g_exit_code);
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
