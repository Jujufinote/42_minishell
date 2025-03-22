/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:25:11 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/20 17:33:42 by jverdier         ###   ########.fr       */
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

int	is_file(t_token *token)
{
	if (is_operator(token->post_str) == 0)
		return (1);
	return (0);
}

void	sorting(t_token *token)
{
	while (token != NULL)
	{
		token->op = is_operator(token->post_str);
		token->file = is_file(token);
		token = token->next;
	}
	return ;
}
