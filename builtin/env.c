/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:58:48 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/08 13:45:23 by jinheo           ###   ########.fr       */
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
	g_exit_code = 0;
}
