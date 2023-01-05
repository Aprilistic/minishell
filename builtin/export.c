/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:04:24 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/05 14:43:56 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quickSort(int arr[], int left, int right)
{
	int	i;
	int	j;
	int	pivot;
	int	temp;

	i = left;
	j = right;
	pivot = arr[(left + right) / 2];
	while (i <= j)
	{
		while (arr[i] < pivot)
			i++; // arr[i] ≥ pivot 일 때까지, left에서 오른쪽 방향으로 탐색
		while (arr[j] > pivot)
			j--; // arr[j] ≤ pivot 일 때까지, right에서 왼쪽 방향으로 탐색
		if (i <= j) // 큰 값이 작은 값보다 왼쪽에 있으면
		{
			// SWAP(arr[i], arr[j])
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}
	/* 재귀(recursion) */
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

static void	print_sorted_env(char **env)
{
	int	env_count;
	int	*index_rank;
	int	index;

	env_count = 0;
	while (env[env_count])
		env_count++;
	env_count--;
	index_rank = (int *)malloc(sizeof(int) * env_count);
	index = 0;
	while (index < env_count)
	{
		index_rank[index] = index;
		index++;
	}
}

int	builtin_export(t_metadata *command, char **env)
{
	if (command->token_count == 1)
	{
		print_sorted_env(env);
		return (0);
	}
}
