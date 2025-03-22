/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:30 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/21 16:37:05 by jverdier         ###   ########.fr       */
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
