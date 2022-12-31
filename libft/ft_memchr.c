/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:08:51 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:33:14 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	checked_byte;
	char	*temp;

	checked_byte = 0;
	while (checked_byte < n)
	{
		temp = (char *)(s + checked_byte);
		if (*temp == (char)c)
			return ((void *)(s + checked_byte));
		checked_byte++;
	}
	return (0);
}
