/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 12:40:37 by jinheo            #+#    #+#             */
/*   Updated: 2022/07/10 20:33:09 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*newobj;

	newobj = (t_list *) malloc (sizeof(t_list));
	if (!newobj)
		return (NULL);
	newobj->content = content;
	newobj->next = NULL;
	return (newobj);
}
