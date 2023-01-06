/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_printenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:26:17 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/06 10:50:16 by jinheo           ###   ########.fr       */
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
	int		i;
	int		j;
	int		pivot;

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

	write(STDOUT_FILENO, "declare -x ", 12);
	equal_flag = 0;
	i = 0;
	while (1)
	{
		if (equal_flag == 0 && env[index][i] == '=')
		{
			write(STDOUT_FILENO, "=\"", 2);
			equal_flag = 1;
		}
		else if (env[index][i] == 0)
		{
			write(STDOUT_FILENO, "\"\n", 2);
			break ;
		}
		else
			write(STDOUT_FILENO, env[index] + i, 1);
		i++;
	}
}

void	print_sorted_env(char **env)
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
	quicksort(env, index_rank, 0, env_count - 1);
	index = 0;
	while (index < env_count)
	{
		print_env_in_export(index, env);
		index++;
	}
	free(index_rank);
}
