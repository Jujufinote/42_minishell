/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:59:20 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/23 15:21:29 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_name_var(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	return (0);
}

int	is_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_redirection(char *str)
{
	if (str[0] == '<' || str[0] == '>')
		return (1);
	return (0);
}

int	is_pairs(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}
