/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_classification.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:48:05 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/02 19:44:58 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redirection(t_metadata *command)
{
}

int	check_builtin(t_metadata *command)
{
}

// 1 : builtin, 2 : redirection_detected, 4 : systemcall
int	classify_command(t_metadata *command)
{
}
