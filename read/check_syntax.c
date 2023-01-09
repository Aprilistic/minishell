/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 13:59:19 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/09 20:36:18 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// bash: syntax error near unexpected token `|’
// bash: syntax error near unexpected token `>'
// bash: syntax error near unexpected token `newline'


static int	print_syntax_error(char *token)
{
	write(STDERR_FILENO, E_PROMPT, ft_strlen(E_PROMPT));
	write(STDERR_FILENO, "syntax error near unexpected token `", 37);
	write(STDERR_FILENO, token, ft_strlen(token));
	write(STDERR_FILENO, "'\n", 2);
	return (ERROR);
}

int	check_syntax(t_metadata *command)
{
	int	token_index;

	while (command->token)
	{
		if (command->token_count == 0)
			return (print_syntax_error("|"));
		token_index = 0;
		while (token_index < command->token_count)
		{
			if (ft_strchr("<>", command->token[token_index][0]))
			{
				if (token_index + 1 >= command->token_count)
					return (print_syntax_error("newline"));
				else if (ft_strchr("<>", command->token[token_index + 1][0]))
					return (print_syntax_error(command->token[token_index]));
			}
			token_index++;
		}
		command++;
	}
	return (0);
}
