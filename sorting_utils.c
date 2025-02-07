/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:25:11 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/28 11:19:53 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_command(t_token *token)
{
	if (token->before == NULL && is_operator(token->str) == 0)
		return (1);
	if (token->before != NULL && token->before->str[0] != '<' \
	&& token->before->str[0] != '>' && is_operator(token->str) == 0)
	{
		token = token->before;
		while (token != NULL && token->str[0] != '|')
		{
			if (token->command == 1)
				return (0);
			token = token->before;
		}
		return (1);
	}
	return (0);
}

int	is_option(t_token *token)
{
	if (token->before != NULL && is_operator(token->before->str) == 0 \
	&& is_command(token) != 1 && token->str[0] == '-')
		return (1);
	return (0);
}

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
	if (is_command(token) == 0 && is_option(token) == 0 \
	&& is_operator(token->str) == 0)
		return (1);
	return (0);
}

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(str, "cd", ft_strlen("cd")) == 0)
		return (1);
	if (ft_strncmp(str, "pwd", ft_strlen("pwd")) == 0)
		return (1);
	if (ft_strncmp(str, "export", ft_strlen("export")) == 0)
		return (1);
	if (ft_strncmp(str, "unset", ft_strlen("unset")) == 0)
		return (1);
	if (ft_strncmp(str, "env", ft_strlen("env")) == 0)
		return (1);
	if (ft_strncmp(str, "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}
