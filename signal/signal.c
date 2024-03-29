/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 16:38:47 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/10 21:15:33 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int signum)
{
	g_exit_code = 130;
	if (signum != SIGINT)
		return ;
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(130);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handle_signal(void)
{
	struct sigaction	new_act;

	new_act.sa_flags = 0;
	sigemptyset(&new_act.sa_mask);
	new_act.sa_flags = 0;
	sigemptyset(&new_act.sa_mask);
	new_act.__sigaction_u.__sa_handler = sigint_handler;
	sigaction(SIGINT, &new_act, NULL);
	new_act.__sigaction_u.__sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &new_act, NULL);
}

void	child_signal_handler(int signum)
{
	if (signum != SIGINT && signum != SIGQUIT)
		return ;
	g_exit_code = 130;
	write(STDERR_FILENO, "\n", 1);
	exit(130);
}

void	change_signal(void)
{
	struct sigaction	new_act;

	new_act.sa_flags = 0;
	sigemptyset(&new_act.sa_mask);
	new_act.__sigaction_u.__sa_handler = child_signal_handler;
	sigaction(SIGINT, &new_act, NULL);
	new_act.__sigaction_u.__sa_handler = child_signal_handler;
	sigaction(SIGQUIT, &new_act, NULL);
}

void	ignore_sigint(void)
{
	struct sigaction	new_act;

	new_act.sa_flags = 0;
	sigemptyset(&new_act.sa_mask);
	new_act.__sigaction_u.__sa_handler = SIG_IGN;
	sigaction(SIGINT, &new_act, NULL);
}
