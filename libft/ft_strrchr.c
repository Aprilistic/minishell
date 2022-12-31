/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:38:53 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:34:55 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	int	s_size;
	int	location;

	s_size = 0;
	while (*(s + s_size))
		s_size++;
	location = s_size;
	while (location >= 0)
	{
		if (*(s + location) == (char)c)
			return ((char *)(s + location));
		location--;
	}
	return (0);
}
