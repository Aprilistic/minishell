/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:24:27 by jinheo            #+#    #+#             */
/*   Updated: 2022/12/30 18:41:22 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	t_metadata	*command;

	atexit(leaks);
	signal(SIGINT, handler);
	while (1)
	{
		//readline
		command = NULL;
		read_commandline(&command, env);

		//parse

		//execute

		//retrieve_memory
	}
	return (0);
}
