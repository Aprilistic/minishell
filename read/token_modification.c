/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_modification.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:39:14 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/03 21:52:26 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//char *commandline, t_metadata *command

void	trim_quote(char **token)
{
	char	*current_token;
	char	*replacement;
	char	quote[2];

	quote[0] = 0;
	quote[1] = 0;
	current_token = *token;
	if (current_token[0] == '\'' || current_token[0] == '\"')
		quote[0] = current_token[0];
	replacement = ft_strtrim(current_token, quote);
	free(current_token);
	*token = replacement;
}

static int	get_key_size(char *token)
{
	int	size;

	if (token[0] != '$')
		return (0);
	if (token[1] == '?')
		return (1);
	size = 1;
	while (token[size] && !ft_strchr("$ \t\n", token[size]))
		size++;
	return (size - 1);
}

void	replace_env_variable(char **token, char **env)
{
	char	*replacement;
	char	*env_value;
	char	*dollar_sign;
	int		prefix_size;

	dollar_sign = ft_strchr(*token, '$');
	if (dollar_sign == NULL)
		return ;
	prefix_size = dollar_sign - *token;
	env_value = get_value_from_environ(dollar_sign + 1, env);
	replacement = (char *)malloc(ft_strlen(env_value) + prefix_size + 1);
	ft_memcpy(replacement, *token, prefix_size);
	ft_memcpy(replacement + prefix_size, env_value, ft_strlen(env_value) + 1);
	free(*token);
	free(env_value);
	*token = replacement;
}
