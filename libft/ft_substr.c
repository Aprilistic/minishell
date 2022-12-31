/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:43:15 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:41:02 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	needed_size;
	size_t	copied_size;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		return (newstr = ft_calloc(1, 1));
	needed_size = 0;
	while (*(s + start + needed_size) && needed_size < len)
		needed_size++;
	newstr = (char *) malloc (needed_size + 1);
	if (!newstr)
		return (NULL);
	copied_size = 0;
	while (copied_size < needed_size)
	{
		*(newstr + copied_size) = *(s + start + copied_size);
		copied_size++;
	}
	*(newstr + copied_size) = 0;
	return (newstr);
}
