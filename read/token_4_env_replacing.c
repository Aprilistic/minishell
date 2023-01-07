/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_4_env_replacing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:39:14 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/06 14:36:40 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_prefix_size(char *token)
{
	char	*dollar_sign;
	int		size;

	size = 0;
	dollar_sign = ft_strchr(token, '$');
	if (dollar_sign == NULL)
		size = ft_strlen(token);
	else
		size = dollar_sign - token;
	return (size);
}

static int	get_key_size(char *token)
{
	int	size;

	if (token[1] == '?' || ft_isdigit(token[1]))
		return (2);
	size = 1;
	while (token[size] && !ft_strchr("$ \t\n\'\"", token[size]))
		size++;
	return (size);
}

static char	*ft_strndup(char *str, int size)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ret = ft_memcpy(ret, str, size);
	ret[size] = 0;
	return (ret);
}

void	replace_env_variable(char **token, char **env)
{
	char	*replacement;
	char	*tmp;
	int		prefix_size;
	int		key_size;

	replacement = ft_strdup("");
	tmp = *token;
	while (1)
	{
		prefix_size = get_prefix_size(tmp);
		if (prefix_size)
		{
			replacement = ft_strjoin(replacement, ft_strndup(tmp, prefix_size));
			tmp += prefix_size;
		}
		if (ft_strrchr(tmp, '$') == NULL)
			break ;
		key_size = get_key_size(tmp);
		replacement = ft_strjoin(replacement,
				get_value_from_environ(ft_strndup(tmp, key_size), env));
		tmp += key_size;
	}
	free(*token);
	*token = replacement;
}
