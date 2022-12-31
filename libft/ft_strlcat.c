/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:19:09 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:34:28 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	idx;
	size_t	appendable_size;
	char	*ptr;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (d_len > dstsize)
		return (s_len + dstsize);
	appendable_size = 0;
	if (d_len + 1 < dstsize)
		appendable_size = dstsize - 1 - d_len;
	ptr = dst + d_len;
	idx = 0;
	while (idx < appendable_size && idx < s_len)
	{
		*(ptr + idx) = *(src + idx);
		idx++;
	}
	*(ptr + idx) = 0;
	if (d_len > dstsize)
		return (s_len + dstsize);
	return (d_len + s_len);
}
