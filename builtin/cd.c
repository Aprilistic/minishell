/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 20:37:48 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/08 18:00:35 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_path_env(char *old_pwd, char **env)
{
	char	*pwd;
	char	*new_token;

	pwd = getcwd(NULL, 0);
	new_token = ft_strjoin(ft_strdup("OLDPWD="), old_pwd);
	modify_env(new_token, env);
	free(new_token);
	new_token = ft_strjoin(ft_strdup("PWD="), pwd);
	modify_env(new_token, env);
	free(new_token);
	g_exit_code = 0;
}

static void	go_to_selected_directory(char *path, char **env)
{
	char	*old_pwd;

	if (ft_strcmp(path, "-") == 0)
	{
		if (getenv("OLDPWD") == NULL)
		{
			g_exit_code = print_error(F_PROMPT, "cd", NULL, "OLDPWD not set");
			return ;
		}
		printf("%s\n", getenv("OLDPWD"));
		go_to_selected_directory(getenv("OLDPWD"), env);
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(path))
	{
		free(old_pwd);
		perror("미니쉘");
		g_exit_code = 1;
		return ;
	}
	update_path_env(old_pwd, env);
}

static void	search_from_cdpath(char *path, char **env)
{
	chdir(getenv("CDPATH"));
	go_to_selected_directory(path, env);
}

static void	go_to_home_directory(char **env)
{
	int		env_index;

	env_index = search_from_environ("HOME", env);
	if (env_index == ERROR)
	{
		print_error(F_PROMPT, "cd", NULL, "HOME not set");
		g_exit_code = 1;
	}
	else if (ft_strchr(env[env_index], '=') == NULL)
	{
		print_error(F_PROMPT, "cd", NULL, "HOME not set");
		g_exit_code = 1;
	}
	else
		go_to_selected_directory(ft_strchr(env[env_index], '=') + 1, env);
}

void	builtin_cd(t_metadata *command, char **env)
{
	if (command->token_count > 2)
	{
		print_error(F_PROMPT, "cd", NULL, "too many arguments");
		g_exit_code = 1;
	}
	else if (command->token_count == 2)
	{
		if (command->token[1][0] != '/' && getenv("CDPATH"))
			search_from_cdpath(command->token[1], env);
		else
			go_to_selected_directory(command->token[1], env);
	}
	else
		go_to_home_directory(env);
}
