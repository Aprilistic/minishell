/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:09:08 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:54:20 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstr;
	size_t	s_size;
	size_t	idx;

	if (!s || !f)
		return (NULL);
	s_size = 0;
	while (*(s + s_size))
		s_size++;
	newstr = (char *) malloc (s_size + 1);
	if (!newstr)
		return (NULL);
	idx = 0;
	while (idx < s_size)
	{
		*(newstr + idx) = f((unsigned int)idx, *(s + idx));
		idx++;
	}
	*(newstr + idx) = 0;
	return (newstr);
}
