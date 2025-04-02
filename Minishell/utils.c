/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:08:35 by jverdier          #+#    #+#             */
/*   Updated: 2025/04/02 17:00:23 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	length(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

char	*strjoin(char *s1, char *s2, int len)
{
	char	*s3;
	int		total_length;
	int		i;
	int		j;

	if (s1 != NULL)
		total_length = ft_strlen(s1) + ft_strlen(s2) + 1;
	else
		total_length = ft_strlen(s2) + 1;
	s3 = (char *)malloc(sizeof(char) * (total_length));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	if (s1 != NULL)
	{
		while (s1[j])
			s3[i++] = s1[j++];
		free(s1);
	}
	j = 0;
	while (s2[j] && j < len)
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

int	count_pipe(t_token *token)
{
	int	pipe;

	pipe = 0;
	while (token != NULL)
	{
		if (token->op == 1 && ft_strncmp(token->base, "|", 2) == 0)
			++pipe;
		token = token->next;
	}
	return (pipe);
}

int	count_hd(t_token *token)
{
	int	hd;

	hd = 0;
	while (token != NULL)
	{
		if (token->op == 2 && ft_strncmp(token->post_str, "<<", 3) == 0)
			++hd;
		token = token->next;
	}
	return (hd);
}

char	*howsub(char *s, int i)
{
	int	j;

	j = i;
	if (is_operator(&s[j]) > 0)
	{
		j += is_operator(&s[j]);
		return (ft_substr(s, i, j - i));
	}
	while (is_whitespace(s[j]) != 1 && is_operator(&s[j]) == 0 && s[j] != '\0')
	{
		if (s[j] == '\'')
		{
			++j;
			j += length(&s[j], '\'');
		}
		if (s[j] == '\"')
		{
			++j;
			j += length(&s[j], '\"');
		}
		++j;
	}
	return (ft_substr(s, i, j - i));
}
