/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:37:48 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/07 17:19:12 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	go_to_selected_directory(char *path, char **env)
{
	char	*old_pwd;
	char	*pwd;
	char	*new_token;

	old_pwd = getcwd(NULL, 0);
	if (chdir(path))
	{
		free(old_pwd);
		perror("미니쉘");
		exit(1);
	}
	pwd = getcwd(NULL, 0);
	new_token = ft_strjoin(ft_strdup("OLDPWD="), old_pwd);
	modify_env(new_token, env);
	free(new_token);
	new_token = ft_strjoin(ft_strdup("PWD="), pwd);
	free(new_token);
	exit(0);
}

static void	go_to_home_directory(char **env)
{
	int		env_index;

	env_index = search_from_environ("HOME", env);
	if (env_index == ERROR)
	{
		print_error(F_PROMPT, "cd", NULL, "HOME not set");
		exit(1);
	}
	if (ft_strchr(env[env_index], '=') == NULL)
	{
		print_error(F_PROMPT, "cd", NULL, "HOME not set");
		exit(1);
	}
	go_to_selected_directory(ft_strchr(env[env_index], '=') + 1, env);
}

void	builtin_cd(t_metadata *command, char **env)
{
	if (command->token_count > 2)
	{
		print_error(F_PROMPT, "cd", NULL, "too many arguments");
		exit(1);
	}
	else if (command->token_count == 2)
		go_to_selected_directory(command->token[1], env);
	else
		go_to_home_directory(env);
}