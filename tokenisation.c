/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:12:24 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/28 11:20:18 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	sorting(t_token *token)
{
	while (token != NULL)
	{
		token->command = is_command(token);
		token->option = is_option(token);
		token->op = is_operator(token->str);
		token->file = is_file(token);
		token = token->next;
	}
	return ;
}

t_token	**tokenisation(t_data *data, char *str)
{
	t_token	**p_token;
	t_token	*new;
	char	*temp;
	int		i;

	i = 0;
	p_token = malloc(sizeof(t_token *));
	if (p_token == NULL)
		return (NULL);
	while (str[i] != '\0' && is_whitespace(str[i]) == 1)
		++i;
	temp = howsub(str, i);
	if (temp == NULL)
		return (free(p_token), NULL);
	i += ft_strlen(temp);
	*p_token = lstnew(formatting(data, temp));
	if (*p_token == NULL)
		return (lstdel(p_token), NULL);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_whitespace(str[i]) == 1)
			++i;
		if (str[i] == '\0')
			break;
		temp = howsub(str, i);
		if (temp == NULL)
			return (lstdel(p_token), NULL);
		i += ft_strlen(temp);
		new = lstnew(formatting(data, temp));
		if (new == NULL)
			return (free(temp), lstdel(p_token), NULL);
		lstadd_back(p_token, new);
	}
	sorting(*p_token);
	return (p_token);
}
