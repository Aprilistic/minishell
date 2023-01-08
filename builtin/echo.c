/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 15:49:39 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/08 13:25:44 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_no_nl(char *token)
{
	int	ret;

	ret = 0;
	if (*token == '-')
	{
		token++;
		while (*token)
		{
			if (*token == 'n')
				ret = 1;
			else
			{
				ret = 0;
				break ;
			}
			token++;
		}
	}
	return (ret);
}

void	builtin_echo(t_metadata *command)
{
	int	no_nl;
	int	index;

	no_nl = 0;
	index = 1;
	while (index < command->token_count)
	{
		if (!check_no_nl(command->token[index]))
			break ;
		no_nl = 1;
		index++;
	}
	while (index < command->token_count)
	{
		printf("%s", command->token[index]);
		if (index != command->token_count)
			printf(" ");
		index++;
	}
	if (!no_nl)
		printf("\n");
	g_exit_code = 0;
}
