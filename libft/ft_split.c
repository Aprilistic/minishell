/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinho <jinho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:44:44 by jinheo            #+#    #+#             */
/*   Updated: 2023/01/01 23:47:27 by jinho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_split(char const *s, char c);
static size_t	check_separator(char c, char now);
static size_t	get_words_count(char const *s, char c);
static size_t	get_words_size(char const *s, char c);
static void		*free_all(char **strset, size_t idx);

char	**ft_split(char const *s, char c)
{
	char	**strset;
	int		str_idx;
	size_t	s_idx;
	size_t	words_size;

	if (!s)
		return (NULL);
	strset = (char **) malloc (sizeof (char *) * (get_words_count(s, c) + 1));
	if (!strset)
		return (NULL);
	str_idx = -1;
	s_idx = 0;
	while (++str_idx < (int)get_words_count(s, c))
	{
		while (check_separator(c, *(s + s_idx)))
			s_idx++;
		words_size = get_words_size(s + s_idx, c);
		strset[str_idx] = (char *) malloc (words_size + 1);
		if (!strset[str_idx])
			return (free_all(strset, str_idx - 1));
		ft_strlcpy(strset[str_idx], (char *)(s + s_idx), words_size + 1);
		s_idx += words_size;
	}
	strset[str_idx] = 0;
	return (strset);
}

static size_t	check_separator(char c, char now)
{
	if (now == c || now == 0)
		return (1);
	return (0);
}

static size_t	get_words_count(char const *s, char c)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (!check_separator(c, *s) && check_separator(c, *(s + 1)))
			ret++;
		s++;
	}
	return (ret);
}

static size_t	get_words_size(char const *s, char c)
{
	size_t	ret;

	ret = 0;
	while (!check_separator(c, *(s + ret)))
		ret++;
	return (ret);
}

static void	*free_all(char **strset, size_t idx)
{
	size_t	cur;

	cur = 0;
	while (cur < idx)
	{
		free(strset[cur]);
		strset[cur] = NULL;
		cur++;
	}
	free(strset);
	return (NULL);
}
