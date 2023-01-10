/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builtin_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:24:40 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/08 18:02:48 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builtin(t_metadata *command, char **env, t_exec *exec)
{
	char	*token;
	int		ret;

	deal_with_redirection(command, exec);
	ret = 1;
	token = command->token[0];
	if (token == NULL)
		return (0);
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
