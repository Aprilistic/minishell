/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:24:27 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/01 15:39:21 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

static void	retrieve_memory(t_metadata **command)
{
	int	command_index;
	int	token_index;

	command_index = 0;
	while ((*command)[command_index].token)
	{
		token_index = 0;
		while (token_index < (*command)[command_index].token_count)
		{
			free((*command)[command_index].token[token_index]);
			token_index++;
		}
		free((*command)[command_index].token);
		command_index++;
	}
	free((*command));
}

void	check_command(t_metadata **command)
{
	int	command_index;

	command_index = 0;
	while ((*command)[command_index].token)
	{
		printf("cmd: %d, token_count: %d\n", command_index, (*command)[command_index].token_count);
		for (int i = 0; i < (*command)[command_index].token_count; ++i)
			printf("token %d: %s\n", i, (*command)[command_index].token[i]);
		command_index++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_metadata	*command;

	atexit(leaks);
	signal(SIGINT, handler);
	while (1)
	{
		command = NULL;
		parse_input(&command, env);
		printf("chk\n");
		check_command(&command);
		//execute

		//retrieve_memory
		retrieve_memory(&command);
	}
	return (0);
}
