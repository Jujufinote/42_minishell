/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:59:20 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/31 18:36:18 by jverdier         ###   ########.fr       */
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
	if (ft_strncmp(str, "<", 2) == 0 || ft_strncmp(str, ">", 2) == 0 \
	|| ft_strncmp(str, "<<", 3) == 0 || ft_strncmp(str, ">>", 3) == 0)
		return (1);
	return (0);
}

int	is_pairs(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}
