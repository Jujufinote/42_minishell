/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_all.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:19:47 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/28 13:41:31 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_all_num(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		++i;
	}
	return (1);
}

int	is_all_name_var(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) == 1 || str[i] == '_')
		return (1);
	while (str[i] != 0 && str[i] != '=')
	{
		if (is_name_var(str[i]) == 0)
			return (1);
		++i;
	}
	return (0);
}
