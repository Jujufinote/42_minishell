/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:30 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/13 11:46:02 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *input)
{
	int	i;

	i = 0;
	if (is_all_wp(input) == 1)
		return (1);
	while (input[i] != '\0')
	{
		if (is_format(input[i]) != 1)
		{
			printf("Syntax error : unknown caracter '%c'\n", input[i]);
			return (1);
		}
		if (is_pairs(input[i]) == 1)
		{
			if (is_close(&input[i + 1], input[i]) == 0)
			{
				printf("Syntax error : unclosed caracter\n");
				return (1);
			}
			i += length(&input[i + 1], input[i]) + 1;
		}
		++i;
	}
	return (0);
}

int	is_close(char *input, char c)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != c)
		++i;
	if (input[i] == c)
		return (1);
	return (0);
}

int	is_all_wp(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0 && is_whitespace(str[i]) == 1)
		++i;
	if (str[i] == 0)
		return (1);
	return (0);
}

int	is_format(char c)
{
	if (ft_isalnum(c) == 1 || c == '|' || c == '<' || c == '>' \
	|| c == '-' || c == '$' || is_pairs(c) == 1 || c == '/' \
	|| c == ' ' || c == '\t' || c == '.' || c == '?' || c == '=' \
	|| c == '_' || c == '~')
		return (1);
	return (0);
}
