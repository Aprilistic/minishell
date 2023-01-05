/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_mergesort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:26:17 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/05 19:44:13 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	quicksort(char **env, int *index_rank, int left, int right)
{
	int		i;
	int		j;
	int		pivot;

	i = left;
	j = right;
	pivot = index_rank[(left + right) / 2];
	while (i <= j)
	{
		while (ft_strcmp(env[index_rank[i]], env[pivot]) < 0)
			i++;
		while (ft_strcmp(env[index_rank[j]], env[pivot]) > 0)
			j++;
		if (i <= j)
		{
			swap(index_rank + i, index_rank + j);
			i++;
			j--;
		}
	}
	if (left < j)
		quicksort(env, index_rank, left, j);
	if (i < right)
		quicksort(env, index_rank, i, right);
}
