/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:47:29 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:32:13 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char ch);

int	ft_atoi(const char *str)
{
	long long	ret;
	int			sign;
	size_t		checked_byte;

	ret = 0;
	sign = 1;
	checked_byte = 0;
	while (ft_isspace(*(str + checked_byte)))
		checked_byte++;
	if (*(str + checked_byte) == '-' || *(str + checked_byte) == '+')
	{
		if (*(str + checked_byte) == '-')
			sign = -1;
		checked_byte++;
	}
	while (ft_isdigit(*(str + checked_byte)))
	{
		ret *= 10;
		ret += *(str + checked_byte) - '0';
		checked_byte++;
	}
	return (ret * sign);
}

static int	ft_isspace(const char ch)
{
	if (ch == ' ' || (9 <= ch && ch <= 13))
		return (1);
	return (0);
}
