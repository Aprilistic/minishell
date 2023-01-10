/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_addenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:50:21 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/10 16:39:09 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*parse_key(char *token)
{
	char	*key;
	int		key_size;

	if (!ft_isalpha(*token))
		key = NULL;
	else if (ft_strchr(token, '=') == NULL)
		key = ft_strdup(token);
	else
	{
		key_size = ft_strchr(token, '=') - token;
		key = ft_calloc(sizeof(char), key_size + 1);
		key = ft_memcpy(key, token, key_size);
	}
	return (key);
}

static char	*parse_value(char *token)
{
	char	*value;
	int		value_size;

	if (ft_strchr(token, '=') == NULL)
		value = NULL;
	else
	{
		value_size = ft_strlen(ft_strchr(token, '='));
		value = ft_calloc(sizeof(char), value_size + 1);
		value = ft_memcpy(value, ft_strchr(token, '='), value_size);
	}
	return (value);
}

static char	*get_env_dict(char *token)
{
	char	*key;
	char	*value;
	char	*ret;

	key = parse_key(token);
	if (key == NULL)
	{
		print_error(E_PROMPT, "export", token, "not a valid identifier");
		ret = NULL;
	}
	else
	{
		value = parse_value(token);
		if (value == NULL)
			ret = key;
		else
			ret = ft_strjoin(key, value);
	}
	return (ret);
}

int	modify_env(char *token, char **env)
{
	char	*key;
	char	*env_dict;
	int		env_index;

	env_dict = get_env_dict(token);
	if (env_dict == NULL)
		return (1);
	key = parse_key(token);
	env_index = search_from_environ(key, env);
	free(key);
	if (env_index == ERROR)
	{
		env_index = 0;
		while (env[env_index])
			env_index++;
		env[env_index] = env_dict;
		env[env_index + 1] = NULL;
	}
	else
	{
		ft_memcpy(env[env_index], env_dict, ft_strlen(env_dict) + 1);
		free(env_dict);
	}
	return (0);
}

int	put_env(t_metadata *command, char **env)
{
	int		token_index;
	int		exit_status;

	token_index = 1;
	exit_status = 0;
	while (token_index < command->token_count)
	{
		exit_status |= modify_env(command->token[token_index], env);
		token_index++;
	}
	return (exit_status);
}
