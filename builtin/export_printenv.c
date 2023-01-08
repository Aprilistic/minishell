/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_printenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:26:17 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/08 17:31:55 by jinheo           ###   ########.fr       */
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

static void	quicksort(char **env, int *index_rank, int left, int right)
{
	int	i;
	int	j;
	int	pivot;

	i = left;
	j = right;
	pivot = (left + right) / 2;
	while (i <= j)
	{
		while (ft_strcmp(env[index_rank[i]], env[index_rank[pivot]]) < 0)
			i++;
		while (ft_strcmp(env[index_rank[j]], env[index_rank[pivot]]) > 0)
			j--;
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

static void	print_env_in_export(int index, char **env)
{
	int	equal_flag;
	int	i;

	printf("declare -x ");
	equal_flag = 0;
	i = 0;
	while (1)
	{
		if (equal_flag == 0 && env[index][i] == '=')
		{
			printf("=\"");
			equal_flag = 1;
		}
		else if (env[index][i] == 0)
		{
			if (equal_flag)
				printf("\"");
			printf("\n");
			break ;
		}
		else
			printf("%c", env[index][i]);
		i++;
	}
}

void	print_sorted_env(char **env)
{
	int	env_count;
	int	*rank;
	int	rank_index;

	env_count = 0;
	while (env[env_count])
		env_count++;
	rank = (int *)malloc(sizeof(int) * env_count);
	rank_index = 0;
	while (rank_index < env_count)
	{
		rank[rank_index] = rank_index;
		rank_index++;
	}
	quicksort(env, rank, 0, env_count - 1);
	rank_index = 0;
	while (rank_index < env_count)
	{
		print_env_in_export(rank[rank_index], env);
		rank_index++;
	}
	free(rank);
}
