/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:46:48 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/10 11:00:30 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	size_t			len;

	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		len = count;
		while (len > 0)
		{
			len--;
			*(unsigned char *)(dest + len) = *(unsigned char *)(src + len);
		}
	}
	else
	{
		len = 0;
		while (len < count)
		{
			*(unsigned char *)(dest + len) = *(unsigned char *)(src + len);
			len++;
		}
	}
	return (dest);
}
