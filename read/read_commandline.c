/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commandline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:45:06 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/01 14:30:40 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	read_commandline(t_metadata **command, char **env)
{
	char		*commandline;
	int			read_again;

	//입력
	commandline = ft_strdup("");
	read_again = handle_input_line(&commandline, "미니쉘> ");
	while (read_again)
		read_again = handle_input_line(&commandline, "> ");
	add_history(commandline);
	//파싱
	printf("%s\n", commandline);
	
	t_metadata	*temp;
	int	idx = 0;
	tokenize(commandline, &temp, env);
	while (1)
	{
		if (temp[idx].token == (void *)1)
			break ;
		printf("cmd: %d, token_count: %d\n", idx, temp[idx].token_count);
		for (int i=0; i<=temp[idx].token_count; ++i)
		{
			printf("token %d: %s\n", i, temp[idx].token[i]);
			free(temp[idx].token[i]);
		}
		free(temp[idx].token);
		idx++;
	}
	free(temp);
	free(commandline);
	return (0);
}
