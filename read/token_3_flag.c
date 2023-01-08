/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_3_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:04:44 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/08 14:13:31 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	check_quote_flag(char *commandline)
{
	int	ret;

	ret = 0;
	if (*commandline == '\'')
		ret = 1;
	else if (*commandline == '\"')
		ret = 2;
	return (ret);
}

int	check_merge_flag(char *commandline)
{
	int ret;

	ret = 1;
	if (ft_strchr(" \n\t|", *(commandline + 1)))
		ret = 0;
	else if (*commandline == '<' || *commandline == '>')
		ret = 0;
	else if (*(commandline + 1) == '<' || *(commandline + 1) == '>')
		ret = 0;
	return (ret);
}
