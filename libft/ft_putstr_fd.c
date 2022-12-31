/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:25:37 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:56:17 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	s_len;
	size_t	idx;

	if (!s)
		return ;
	s_len = 0;
	while (*(s + s_len))
		s_len++;
	idx = 0;
	while (idx < s_len)
	{
		write(fd, (void *)(s + idx), sizeof(char));
		idx++;
	}	
}
