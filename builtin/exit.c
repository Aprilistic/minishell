/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:33:17 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/04 20:39:47 by jinheo           ###   ########.fr       */
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

	checked_byte = 0;
	while (ft_isspace(str[checked_byte]))
		checked_byte++;
	if (str[checked_byte] == '-' || str[checked_byte] == '+')
		checked_byte++;
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
	return (validity);
}

void	builtin_exit(t_metadata *command)
{
	int	ret;

	ret = 0;
	printf("exit\n");
	if (command->token_count > 2)
	{
		write(STDERR_FILENO, "미니쉘: exit: too many arguments\n", 37);
		ret = 2;
	}
	else if (command->token_count == 2)
	{
		if (!check_numeric_argument(command->token[1]))
		{
			write(STDERR_FILENO, "미니쉘: exit: ", 18);
			write(STDERR_FILENO, command->token[1],
				ft_strlen(command->token[1]));
			write(STDERR_FILENO, ": numeric argument required\n", 27);
			ret = 2;
		}
		else
			ret = ft_atoi(command->token[1]);
	}
	exit_code = ret;
	exit(ret);
}
