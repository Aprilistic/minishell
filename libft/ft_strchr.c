/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:48:48 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:34:07 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	s_size;
	size_t	location;

	s_size = ft_strlen(s);
	location = 0;
	while (location <= s_size)
	{
		if (*(s + location) == (char)c)
			return ((char *)(s + location));
		location++;
	}
	return (0);
}
