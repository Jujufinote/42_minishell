/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:01:30 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/20 18:34:39 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(char *input)
{
	int	i;

	i = -1;
	while (input[++i] != '\0')
	{
		if (is_format(input[i]) != 1)
		{
			printf("%s%s%s\nSyntax error : unknown caracter '%c'\n%s", STD, BOLD, RED, input[i], RES);
			return (1);
		}
		if (is_pairs(input[i]) == 1)
		{
			++i;
			if (is_close(&input[i], input[i - 1]) == 0)
			{
				printf("%s%s%s\nSyntax error : unclosed caracter\n%s", STD, BOLD, RED, RES);
				return (1);
			}
			i += length(&input[i], input[i - 1]);
		}
	}
	return (0);
}

int	is_close(char *input, char c)
{
	int	i;

	i = 0;
	while (input[i] != '\0' && input[i] != c)
		++i;
	if (input[i] == '\0')
		return (0);
	return (1);
}
