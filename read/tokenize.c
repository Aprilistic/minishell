/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:56:50 by jinheo            #+#    #+#             */
/*   Updated: 2022/12/30 18:43:20 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	get_command_count(char *command)
{
	int	single_quote;
	int	double_quote;
	int	command_count;

	single_quote = 0;
	double_quote = 0;
	command_count = 1;
	while (*command)
	{
		if (double_quote == 0 && *command == '\'')
			single_quote = !single_quote;
		else if (single_quote == 0 && *command == '\"')
			double_quote = !double_quote;
		else if ((double_quote == 0 && single_quote == 0) && *command == '|')
			command_count++;
		command++;
	}
	return (command_count);
}

void	get_token_count(t_metadata **command, char *commandline, int command_count)
{
	int	token_count;
	int	command_num;
	int	single_quote;
	int	double_quote;

	token_count = 0;
	command_num = 0;
	single_quote = 0;
	double_quote = 0;
	while (*commandline)
	{
		if (double_quote == 0 && *commandline == '\'')
			single_quote = !single_quote;
		else if (single_quote == 0 && *commandline == '\"')
			double_quote = !double_quote;
		else if (!(double_quote || single_quote))
		{
			if (*commandline == '|' || *commandline == NULL)
			{
				(*command)[command_num++].token_count = token_count;
				token_count = 0;
			}
			else if (*commandline == ' ' || *commandline == '\n'
				|| *commandline == '\t')
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
	(*command)[command_count].token = NULL;
}
