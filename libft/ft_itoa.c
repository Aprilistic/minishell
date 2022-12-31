/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:05:31 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/09 17:41:25 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n);
int		ft_get_needed_length(int n);
void	ft_fill_memory(int neg, long n, int size, char **ret);

char	*ft_itoa(int n)
{
	long	temp;
	int		needed_length;
	int		neg;
	char	*ret;

	if (n == 0)
	{
		ret = (char *) malloc (2);
		ret[0] = '0';
		ret[1] = 0;
		return (ret);
	}
	temp = n;
	neg = 0;
	if (n < 0)
	{
		neg = 1;
		temp *= -1;
	}
	needed_length = ft_get_needed_length(n);
	ret = (char *) malloc (sizeof(char) * (needed_length + 1));
	if (!ret)
		return (NULL);
	ft_fill_memory(neg, temp, needed_length, &ret);
	return (ret);
}

int	ft_get_needed_length(int n)
{
	long	tmp;
	int		ret;

	ret = 0;
	tmp = n;
	if (tmp < 0)
	{
		ret++;
		tmp *= -1;
	}
	while (tmp)
	{
		tmp /= 10;
		ret++;
	}
	return (ret);
}

void	ft_fill_memory(int neg, long n, int size, char **ret)
{
	if (neg)
		(*ret)[0] = '-';
	(*ret)[size] = 0;
	while (size - 1 >= neg)
	{
		(*ret)[size - 1] = n % 10 + '0';
		n /= 10;
		size--;
	}
}
