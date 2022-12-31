/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:07:13 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:42:18 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		head;
	int		tail;
	char	*newstr;

	if (!s1 || !set)
		return (NULL);
	head = 0;
	tail = ft_strlen(s1);
	while (ft_strchr(set, *(s1 + head)) && head < tail)
		head++;
	if (head >= tail)
		return (ft_strdup(""));
	while (ft_strchr(set, *(s1 + tail)))
		tail--;
	newstr = (char *) malloc (tail - head + 2);
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, (char *)(s1 + head), tail - head + 2);
	return (newstr);
}
