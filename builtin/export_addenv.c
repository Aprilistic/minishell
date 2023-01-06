/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_addenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:50:21 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/06 17:36:31 by jinheo           ###   ########.fr       */
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
	int		exit_status;
	char	*key;
	char	*value;
	char	*ret;

	key = parse_key(token);
	if (key == NULL)
	{
		write(STDERR_FILENO, "미니쉘: export: '", 20);
		write(STDERR_FILENO, token, ft_strlen(token));
		write(STDERR_FILENO, "' not a valid identifier\n", 26);
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

static void	modify_env(char *token, char *env_dict, char **env)
{
	char	*key;
	int		env_index;

	key = parse_key(token);
	env_index = search_from_environ(key, env);
	if (env_index == ERROR)
	{
		env_index = 0;
		while (env[env_index])
			env_index++;
		env[env_index] = env_dict;
		env[env_index + 1] = NULL;
	}
	else
		env[env_index] = env_dict;
	free(key);
}

int	put_env(t_metadata *command, char **env)
{
	int		token_index;
	int		exit_status;
	char	*env_dict;

	token_index = 1;
	exit_status = 0;
	while (token_index < command->token_count)
	{
		//possible memory leak
		env_dict = parse_env_dict(command->token[token_index]);
		if (env_dict == NULL)
			exit_status = 1;
		else
			modify_env(command->token[token_index], env_dict, env);
		token_index++;
	}
	exit(exit_status);
}
