/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:24:27 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/10 17:19:49 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free((*command)[command_index].token_quote_flag);
		free((*command)[command_index].token_merge_flag);
		command_index++;
	}
	free((*command));
}

int	main(int argc, char **argv, char **env)
{
	t_metadata	*command;

	(void)argv;
	if (argc != 1)
	{
		write(STDERR_FILENO, "Seriously? We don't need argv. ", 32);
		write(STDERR_FILENO, "Anyeonghigyeseyo~\n", 19);
		return (222);
	}
	while (1)
	{
		handle_signal();
		command = NULL;
		if (parse_input(&command, env) == ERROR)
			g_exit_code = 1;
		else
			execute(command, env);
		retrieve_memory(&command);
	}
	return (0);
}
