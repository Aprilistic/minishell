/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:59:32 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:34:32 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	idx;
	size_t	srcsize;

	srcsize = 0;
	while (*(src + srcsize))
		srcsize++;
	if (dstsize == 0)
		return (srcsize);
	idx = 0;
	while (idx < dstsize - 1 && *(src + idx))
	{
		*(dst + idx) = *(src + idx);
		idx++;
	}
	*(dst + idx) = 0;
	return (srcsize);
}
