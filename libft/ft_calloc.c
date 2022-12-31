/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 20:09:21 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/11 19:06:03 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	*checked_byte;

	p = (void *) malloc (count * size);
	if (!p)
		return (NULL);
	checked_byte = 0;
	ft_memset(p, 0, count * size);
	return (p);
}
