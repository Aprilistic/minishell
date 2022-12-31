/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:50:54 by jinheo            #+#    #+#             */
/*   Updated: 2022/12/31 13:05:25 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_size;
	size_t	s2_size;
	char	*newstr;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	newstr = (char *) malloc (s1_size + s2_size + 1);
	if (!newstr)
		return (NULL);
	ft_memcpy(newstr, s1, s1_size);
	ft_memcpy(newstr + s1_size, s2, s2_size);
	newstr[s1_size + s2_size] = 0;
	free((void *)s1);
	free((void *)s2);
	return (newstr);
}
