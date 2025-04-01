/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:25:11 by jverdier          #+#    #+#             */
/*   Updated: 2025/04/01 14:24:55 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char *str)
{
	if (*str == '|')
		return (1);
	if (*str == '<')
	{
		if (str[1] == '<')
			return (2);
		else
			return (1);
	}
	if (*str == '>')
	{
		if (str[1] == '>')
			return (2);
		else
			return (1);
	}
	return (0);
}

int	is_operator_final(t_token *token)
{
	if (token->base[0] != '\'' && token->base[0] != '\"')
	{
		if (ft_strncmp(token->post_str, "|", 2) == 0)
			return (1);
		if (ft_strncmp(token->post_str, "<", 2) == 0)
			return (1);
		if (ft_strncmp(token->post_str, "<<", 3) == 0)
			return (2);
		if (ft_strncmp(token->post_str, ">", 2) == 0)
			return (1);
		if (ft_strncmp(token->post_str, ">>", 3) == 0)
			return (2);
	}
	return (0);
}

int	is_file(t_token *token)
{
	if (is_operator_final(token) == 0)
		return (1);
	return (0);
}

void	sorting(t_token *token)
{
	while (token != NULL)
	{
		token->op = is_operator_final(token);
		token->file = is_file(token);
		token = token->next;
	}
	return ;
}
