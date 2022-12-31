/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 19:27:44 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/11 18:59:17 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	haystack_len;
	size_t	needle_len;
	size_t	idx;

	haystack_len = ft_strlen(haystack);
	needle_len = ft_strlen(needle);
	if (!needle_len)
		return ((char *)haystack);
	if (!haystack_len)
		return (NULL);
	idx = 0;
	while (idx + needle_len <= len)
	{
		if (!ft_strncmp((char *)(haystack + idx), (char *)needle, needle_len))
			return ((char *)(haystack + idx));
		idx++;
	}
	return (NULL);
}
