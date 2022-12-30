/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:51:01 by jinheo            #+#    #+#             */
/*   Updated: 2022/12/30 16:54:33 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_quote(char *newline)
{
	static int	single_quote;
	static int	double_quote;

	while (*newline)
	{
		if (double_quote == 0 && *newline == '\'')
			single_quote = !single_quote;
		else if (single_quote == 0 && *newline == '\"')
			double_quote = !double_quote;
		newline++;
	}
	if (double_quote || single_quote)
		return (1);
	double_quote = 0;
	single_quote = 0;
	return (0);
}

// 0 : input ended, 1 : single-quote, 2 : double-quote
int	handle_input_line(char **commandline, char *prompt)
{
	char		*newline;
	static int	read_again;

	newline = readline(prompt);
	if (newline == NULL)
	{
		if (read_again)
		{
			write(STDERR_FILENO, "미니쉘: 예상치 못한 파일의 끝\n", 43);
			free(newline);
			newline = readline(prompt);
			free(newline);
		}
		else
			printf("exit\n");
		exit(0);
	}
	read_again = check_quote(newline);
	*commandline = ft_strjoin(*commandline, newline);
	return (read_again);
}
