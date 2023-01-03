/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:56:50 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/03 21:51:59 by jinheo           ###   ########.fr       */
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
	else if (!ft_strchr("| \t\n\"\'", (int)*addr))
	{
		while (!ft_strchr("| \t\n\"\'", (int)*(addr)))
			addr++;
		addr--;
	}
	return (addr);
}

void	allocate_command_slot(char *commandline, t_metadata **command)
{
	int	command_count;

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

static char	*get_current_token(char *addr, char **env)
{
	char	*token;
	int		token_size;
	char	*temp;

	token_size = skip_current_token(addr) - addr + 1;
	token = (char *)malloc(token_size + 1);
	ft_memcpy(token, addr, token_size);
	token[token_size] = 0;
	trim_quote(&token);
	replace_env_variable(&token, env);
	return (token);
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
			(*command)[command_index].token_count = token_index;
			token_index = 0;
			command_index++;
			if (*commandline == 0)
				break ;
		}
		else if (!ft_strchr("| \t\n", (int)*commandline))
		{
			if (*commandline == '\'' || *commandline == '\"')
				(*command)[command_index].token_quote_flag[token_index] = 1;
			(*command)[command_index].token[token_index++]
				= get_current_token(commandline, env);
			commandline = skip_current_token(commandline);
		}
		commandline++;
	}
}
