/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:30:20 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:33:25 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	len;

	len = 0;
	if (!dst && !src)
		return (NULL);
	while (len < n)
	{
		*(unsigned char *)(dst + len) = *(unsigned char *)(src + len);
		len++;
	}
	return (dst);
}
