/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 15:12:24 by jverdier          #+#    #+#             */
/*   Updated: 2025/04/02 18:41:40 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*formatting(t_data *data, char *base, t_token *token)
{
	char	*result;

	if (base == NULL && token == NULL)
		return (NULL);
	if (token != NULL)
	{
		while (token != NULL && ft_strncmp(token->base, "|", 2) != 0)
		{
			token->str = final_replacement(data, token->base, NULL);
			if (token->str == NULL)
				return (NULL);
			token = token->next;
		}
		return ("ok");
	}
	result = replacement(data, base, NULL);
	if (result == NULL)
		printf("Error in memory allocation\n");
	return (result);
}

char	*final_replacement(t_data *data, char *base, char *result)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '\'')
		{
			result = single_quote(base + i + 1, result);
			i += length(&base[i + 1], '\'') + 2;
		}
		else if (base[i] == '\"')
		{
			result = double_quote(data, base + i + 1, result, 1);
			i += length(&base[i + 1], '\"') + 2;
		}
		else
			result = final_replacment_next(data, base, &i, result);
		if (result == NULL)
			break ;
	}
	return (result);
}

t_token	**tokenisation(t_data *data, char *str)
{
	t_token	**p_token;
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
	*p_token = lstnew(temp, formatting(data, temp, NULL));
	if (*p_token == NULL)
		return (lstdel(p_token), NULL);
	if (create_list(data, p_token, str, i) == NULL)
		return (NULL);
	sorting(*p_token);
	return (p_token);
}

char	*replacement(t_data *data, char *base, char *result)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '\'')
		{
			result = single_quote(base + i + 1, result);
			i += length(&base[i + 1], '\'') + 2;
		}
		else if (base[i] == '\"')
		{
			result = double_quote(data, base + i + 1, result, 0);
			i += length(&base[i + 1], '\"') + 2;
		}
		else
		{
			result = strjoin(result, &base[i], 1);
			++i;
		}
		if (result == NULL)
			break ;
	}
	return (result);
}

t_token	**create_list(t_data *data, t_token **p_token, char *str, int i)
{
	t_token	*new;
	char	*temp;

	while (str[i] != '\0')
	{
		while (str[i] != '\0' && is_whitespace(str[i]) == 1)
			++i;
		if (str[i] == '\0')
			break ;
		temp = howsub(str, i);
		if (temp == NULL)
			return (lstdel(p_token), NULL);
		i += ft_strlen(temp);
		new = lstnew(temp, formatting(data, temp, NULL));
		if (new == NULL)
			return (free(temp), lstdel(p_token), NULL);
		lstadd_back(p_token, new);
	}
	return (p_token);
}
