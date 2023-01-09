/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_1_allocation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:56:50 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/09 17:46:20 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//begins at token, returns last address of token
char	*skip_current_token(char *addr)
{
	if (*addr == '\'')
		addr = ft_strchr(addr + 1, '\'');
	else if (*addr == '\"')
		addr = ft_strchr(addr + 1, '\"');
	else if (*addr == '<')
	{
		while (*addr == '<')
			addr++;
		addr--;
	}
	else if (*addr == '>')
	{
		while (*addr == '>')
			addr++;
		addr--;
	}
	else if (!ft_strchr("| \t\n\"\'<>", (int)*addr))
	{
		while (!ft_strchr("| \t\n\"\'<>", (int)*(addr)))
			addr++;
		addr--;
	}
	return (addr);
}

static int	empty_input_exception(char *commandline)
{
	while (*commandline == ' ' || *commandline == '\t' || *commandline == '\n')
		commandline++;
	if (*commandline == 0)
		return (1);
	return (0);
}

void	allocate_command_slot(char *commandline, t_metadata **command)
{
	int	command_count;

	if (empty_input_exception(commandline))
		command_count = 0;
	else
		command_count = 1;
	while (*commandline)
	{
		if (*commandline == '|')
			command_count++;
		commandline = skip_current_token(commandline);
		commandline++;
	}
	*command = malloc(sizeof(t_metadata) * (command_count + 1));
	(*command)[command_count].token = NULL;
	(*command)[command_count].token_count = 0;
}

static void	allocate_t_metadata(t_metadata *command, int token_count)
{
	command->token_count = token_count;
	command->token = ft_calloc(token_count + 1, sizeof(char *));
	command->token_quote_flag = ft_calloc(token_count, sizeof(int));
	command->token_merge_flag = ft_calloc(token_count, sizeof(int));
}

void	allocate_token_slot(char *commandline, t_metadata **command)
{
	int	command_index;
	int	token_index;

	if (empty_input_exception(commandline))
		return ;
	command_index = 0;
	token_index = 0;
	while (1)
	{
		if (*commandline == '|' || *commandline == 0)
		{
			allocate_t_metadata(&(*command)[command_index], token_index);
			token_index = 0;
			command_index++;
			if (*commandline == 0)
				break ;
		}
		else if (!ft_strchr("| \t\n", (int)*commandline))
		{
			commandline = skip_current_token(commandline);
			token_index++;
		}
		commandline++;
	}
}
