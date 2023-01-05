/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:04:24 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/05 22:07:49 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_export(t_metadata *command, char **env)
{
	if (command->token_count == 1)
	{
		print_sorted_env(env);
		exit(0);
	}
	
}
