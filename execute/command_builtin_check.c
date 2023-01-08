/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builtin_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:24:40 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/08 15:46:32 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_metadata *command, char **env)
{
	char	*token;
	int		ret;

	ret = 1;
	token = command->token[0];
	if (!ft_strcmp("cd", token))
		builtin_cd(command, env);
	else if (!ft_strcmp("echo", token))
		builtin_echo(command);
	else if (!ft_strcmp("env", token))
		builtin_env(env);
	else if (!ft_strcmp("exit", token))
		builtin_exit(command);
	else if (!ft_strcmp("export", token))
		builtin_export(command, env);
	else if (!ft_strcmp("pwd", token))
		builtin_pwd();
	else if (!ft_strcmp("unset", token))
		builtin_unset(command, env);
	else
		ret = 0;
	return (ret);
}
