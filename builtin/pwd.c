/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:42:46 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/07 17:20:56 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_pwd(void)
{
	char	*buf;

	buf = (char *)malloc(__DARWIN_MAXPATHLEN + 1);
	getcwd(buf, __DARWIN_MAXPATHLEN);
	printf("%s\n", buf);
	free(buf);
	exit(0);
}
