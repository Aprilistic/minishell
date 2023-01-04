/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_3_merging.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:55:30 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/04 17:07:48 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_new_token_count(t_metadata *command)
{
	int	token_index;
	int	token_count;

	token_index = 0;
	token_count = command->token_count;
	while (token_index < command->token_count)
	{
		if (command->token_merge_flag[token_index])
			token_count--;
		token_index++;
	}
	return (token_count);
}

static char	**make_new_token(t_metadata *command)
{
	char	**ret;
	char	*tmp;
	int		new_index;
	int		old_index;

	ret = ft_calloc(get_new_token_count(command) + 1, sizeof(char *));
	tmp = ft_strdup("");
	new_index = 0;
	old_index = 0;
	while (old_index < command->token_count)
	{
		if (command->token_merge_flag[old_index])
		{
			tmp = ft_strjoin(tmp, command->token[old_index]);
		}
		else
		{
			ret[new_index] = ft_strjoin(tmp, command->token[old_index]);
			new_index++;
			tmp = ft_strdup("");
		}
		old_index++;
	}
	free(tmp);
	return (ret);
}

static int	*make_new_token_quote_flag(t_metadata *command)
{
	int	*ret;
	int	tmp;
	int	new_index;
	int	old_index;

	ret = ft_calloc(get_new_token_count(command), sizeof(int));
	new_index = 0;
	old_index = 0;
	tmp = command->token_quote_flag[old_index];
	while (old_index < command->token_count)
	{
		if (!command->token_merge_flag[old_index])
		{
			ret[new_index] = tmp;
			tmp = command->token_quote_flag[old_index];
		}
		tmp &= command->token_quote_flag[old_index];
		old_index++;
	}
	return (ret);
}

static void	update_token(t_metadata *command)
{
	char	**new_token;
	int		*new_quote;
	int		new_token_count;

	new_token = make_new_token(command);
	new_quote = make_new_token_quote_flag(command);
	new_token_count = get_new_token_count(command);
	free(command->token);
	free(command->token_quote_flag);
	command->token = new_token;
	command->token_quote_flag = new_quote;
	command->token_count = new_token_count;
}

void	merge_token(t_metadata **command)
{
	int	command_count;
	int	command_index;
	int	token_index;

	command_count = 0;
	while ((*command)[command_count].token)
		command_count++;
	printf("cmd cnt: %d\n", command_count);
	command_index = 0;
	while (command_index < command_count)
	{
		update_token(&(*command)[command_index]);
		command_index++;
	}
}
