/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:56:50 by jinheo            #+#    #+#             */
/*   Updated: 2022/12/30 20:22:02 by jinheo           ###   ########.fr       */
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

int	get_command_count(char *command)
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

void	get_token_count(char *commandline, t_metadata **command)
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

int	tokenize(char *commandline, t_metadata **command)
{
	int	command_count;

	command_count = get_command_count(commandline);
	*command = malloc(sizeof(t_metadata) * (command_count + 1));
	if (*command == NULL)
		return (ERROR);
	(*command)[command_count].token = (void *)1;
	get_token_count(commandline, command);
	return (0);
}
