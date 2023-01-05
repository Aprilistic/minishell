/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:04:24 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/05 21:39:31 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_export(t_metadata *command, char **env)
{
	if (command->token_count == 1)
	{
		print_sorted_env(env);
		return (0);
	}
}
