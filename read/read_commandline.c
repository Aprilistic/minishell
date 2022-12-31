/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commandline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinheo <jinheo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 13:45:06 by jinheo            #+#    #+#             */
/*   Updated: 2022/12/31 13:18:50 by jinheo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//오류 처리 부분 규칙 정하기
// 반환값으로 오류여부 처리(이중포인터 이용) or NULL으로 처리(객체 반환)
int	read_commandline(t_metadata **command, char **env)
{
	char		*commandline;
	int			read_again;

	//입력
	commandline = ft_strdup("");
	read_again = handle_input_line(&commandline, "미니쉘> ");
	while (read_again)
		read_again = handle_input_line(&commandline, "> ");
	add_history(commandline);
	//파싱
	printf("%s\n", commandline);
	
	t_metadata	*temp;
	int	idx = 0;
	tokenize(commandline, &temp);
	while (1)
	{
		if (temp[idx].token == (void *)1)
			break ;
		printf("cmd: %d, token_count: %d\n", idx, temp[idx].token_count);
		idx++;
	}
	free(temp);
	free(commandline);
	return (0);
}
