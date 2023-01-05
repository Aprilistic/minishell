/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_1_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:04:44 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/05 20:06:13 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	trim_quote(char **token)
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

static char	*get_current_token(char *addr, char **env, int quote_flag)
{
	char	*token;
	int		token_size;
	char	*temp;

	token_size = skip_current_token(addr) - addr + 1;
	token = ft_calloc(sizeof(char), token_size + 1);
	ft_memcpy(token, addr, token_size);
	if (quote_flag != 1)
		replace_env_variable(&token, env);
	trim_quote(&token);
	return (token);
}

static int	count_token(char *commandline, t_metadata **command,
	int *command_index, int *token_index)
{
	(*command)[*command_index].token_count = *token_index;
	*token_index = 0;
	(*command_index)++;
	if (*commandline == 0)
		return (1);
	return (0);
}

static int	check_quote(char *commandline)
{
	int	ret;

	ret = 0;
	if (*commandline == '\'')
		ret = 1;
	else if (*commandline == '\"')
		ret = 2;
	return (ret);
}

void	save_token(char *commandline, t_metadata **command, char **env)
{
	int		command_index;
	int		token_index;

	command_index = 0;
	token_index = 0;
	while (1)
	{
		if (*commandline == '|' || *commandline == 0)
		{
			if (count_token(commandline, command, &command_index, &token_index))
				break ;
		}
		else if (!ft_strchr("| \t\n", (int)*commandline))
		{
			(*command)[command_index].token_quote_flag[token_index]
				= check_quote(commandline);
			(*command)[command_index].token[token_index]
				= get_current_token(commandline, env, check_quote(commandline));
			commandline = skip_current_token(commandline);
			if (!ft_strchr(" \n\t|", *(commandline + 1)))
				(*command)[command_index].token_merge_flag[token_index] = 1;
			token_index++;
		}
		commandline++;
	}
}
