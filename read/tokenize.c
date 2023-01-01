/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:56:50 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/01 15:35:05 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*skip_this_token(char *addr)
{
	if (*addr == '\'')
		addr = ft_strchr(addr + 1, '\'');
	else if (*addr == '\"')
		addr = ft_strchr(addr + 1, '\"');
	else if (!ft_strchr(" \t\n", (int)*addr))
	{
		while (!ft_strchr(" \t\n", (int)*(addr++)))
			;
		addr--;
	}
	return (addr);
}

static int	get_command_count(char *command)
{
	int	command_count;

	command_count = 1;
	while (*command)
	{
		if (*command == '|')
			command_count++;
		command = skip_this_token(command);
		command++;
	}
	return (command_count);
}

static void	get_token_count(char *commandline, t_metadata **command)
{
	int	command_num;
	int	token_count;

	command_num = 0;
	token_count = 0;
	while (1)
	{
		if (*commandline == '|' || *commandline == 0)
		{
			(*command)[command_num].token_count = token_count;
			(*command)[command_num].token
				= (char **)malloc(sizeof(char *) * token_count);
			token_count = 0;
			command_num++;
			if (*commandline == 0)
				break ;
		}
		else if (!ft_strchr(" \t\n", (int)*commandline))
		{
			commandline = skip_this_token(commandline);
			token_count++;
		}
		commandline++;
	}
}

static char	*get_token(char *addr, char **env)
{
	char	*token;
	int		token_size;
	char	*temp;

	token_size = skip_this_token(addr) - addr + 1;
	token = (char *)malloc(token_size + 1);
	ft_memcpy(token, addr, token_size);
	token[token_size] = 0;
	if (*token == '$')
	{
		temp = get_value_from_environ(token + 1, env);
		free(token);
		token = temp;
	}
	return (token);
}

static void	parse_token(char *commandline, t_metadata **command, char **env)
{
	int		command_index;
	int		token_index;
	char	*parsed_token;

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
		else if (!ft_strchr(" \t\n", (int)*commandline))
		{
			(*command)[command_index].token[token_index]
				= get_token(commandline, env);
			commandline = skip_this_token(commandline);
			token_index++;
		}
		commandline++;
	}
}

int	tokenize(char *commandline, t_metadata **command, char **env)
{
	int	command_count;

	command_count = get_command_count(commandline);
	*command = malloc(sizeof(t_metadata) * (command_count + 1));
	if (*command == NULL)
		return (ERROR);
	(*command)[command_count].token = NULL;
	get_token_count(commandline, command);
	parse_token(commandline, command, env);
	return (0);
}
