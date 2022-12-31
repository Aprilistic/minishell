/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:19:47 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:34:09 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newstr;
	size_t	s1_len;
	size_t	copied;

	s1_len = ft_strlen(s1);
	newstr = (char *) malloc (s1_len + 1);
	if (!newstr)
		return (NULL);
	copied = 0;
	while (copied < s1_len)
	{
		*(newstr + copied) = *(s1 + copied);
		copied++;
	}
	*(newstr + copied) = 0;
	return (newstr);
}
