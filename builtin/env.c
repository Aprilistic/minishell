/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:58:48 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/05 22:06:13 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(char **env)
{
	int	env_index;

	env_index = 0;
	while (env[env_index])
	{
		printf("%s\n", env[env_index]);
		env_index++;
	}
	exit(0);
}
