/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:44:42 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:34:42 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	chk;

	chk = 0;
	while (chk < n)
	{
		if ((unsigned char)s1[chk] != (unsigned char)s2[chk])
			return ((unsigned char)s1[chk] - (unsigned char)s2[chk]);
		if ((unsigned char)s1[chk] == 0 && (unsigned char)s2[chk] == 0)
			return (0);
		chk++;
	}
	return (0);
}
