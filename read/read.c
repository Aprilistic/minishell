/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:51:01 by jinheo            #+#    #+#             */
/*   Updated: 2022/12/31 20:50:06 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_quote(char *newline, int *read_again)
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
	{
		*read_again |= 1;
		return ;
	}
	double_quote = 0;
	single_quote = 0;
	*read_again = 0;
}

static void	check_pipe(char *newline, int *read_again)
{
	int	index;

	if (*read_again)
		return ;
	index = ft_strlen(newline) - 1;
	while (index + 1 && ft_strchr(" \t\n", newline[index]))
		index--;
	if (index < 0)
		return ;
	if (newline[index] == '|' && !(ft_strchr(newline + index + 1, '\'')
			|| ft_strchr(newline + index + 1, '\"')))
		*read_again |= 2;
}

// 0 : input ended, 1 : single-quote, 2 : double-quote
int	handle_input_line(char **commandline, char *prompt)
{
	char		*newline;
	static int	read_again;

	read_again = 0;
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
	check_quote(newline, &read_again);
	check_pipe(newline, &read_again);
	if (read_again)
		newline = ft_strjoin(newline, ft_strdup("\n"));
	*commandline = ft_strjoin(*commandline, newline);
	return (read_again);
}
