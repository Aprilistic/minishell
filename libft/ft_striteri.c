/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:17:49 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:55:57 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	s_size;
	unsigned int	idx;

	if (!s || !f)
		return ;
	s_size = 0;
	while (*(s + s_size))
		s_size++;
	idx = 0;
	while (idx < s_size)
	{
		f(idx, (char *)(s + idx));
		idx++;
	}
}
