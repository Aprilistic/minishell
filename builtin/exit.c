/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:33:17 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/08 16:42:05 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_isspace(const char ch)
{
	if (ch == ' ' || (9 <= ch && ch <= 13))
		return (1);
	return (0);
}

static int	check_numeric_argument(char *str)
{
	size_t	checked_byte;
	int		validity;

	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	checked_byte = 0;
	validity = 1;
	while (*(str + checked_byte))
	{
		if (!ft_isdigit(str[checked_byte]))
		{
			validity = 0;
			break ;
		}
		checked_byte++;
	}
	if (checked_byte > 10)
		validity = 0;
	return (validity);
}

void	builtin_exit(t_metadata *command)
{
	int	ret;

	ret = 0;
	printf("exit\n");
	if (command->token_count >= 2)
	{
		if (!check_numeric_argument(command->token[1]))
		{
			print_error(E_PROMPT, "exit",
				command->token[1], "numeric argument required");
			ret = 2;
		}
		else if (command->token_count > 2)
		{
			print_error(E_PROMPT, "exit", NULL, "too many arguments");
			g_exit_code = 2;
			return ;
		}
		else
			ret = ft_atoi(command->token[1]);
	}
	exit(ret);
}
