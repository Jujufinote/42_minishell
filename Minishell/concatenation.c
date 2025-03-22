/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:26:40 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/21 17:59:18 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*final_replacement(t_data *data, char *base, char *result)
{
	int		i;
	char	*var;

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
		else if (base[i] == '$' && (is_name_var(base[i + 1]) == 1 || base[i + 1] == '?'))
		{
			var = grab_var(base + i, data);
			if (var == NULL)
				return (NULL);
			result = strjoin(result, var, ft_strlen(var));
			if (result == NULL)
				return (NULL);
			++i;
			while (base[i] != '?' && base[i] && is_name_var(base[i]) == 1)
				++i;
			if (base[i] == '?')
				++i;
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

char	*single_quote(char *base, char *result)
{
	int	i;

	i = 0;
	while (base[i] != '\'' && base[i] != '\0')
		++i;
	result = strjoin(result, base, i);
	return (result);
}

char	*double_quote(t_data *data, char *base, char *result, int is_ok)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	if (is_ok == 1)
	{
		while (base[i] != '\"' && base[i] != '\0' && (base[i] != '$' || (base[i] == '$' && is_name_var(base[i + 1]) == 0 && base[i + 1] != '?')))
			++i;
	}
	else
	{
		while (base[i] != '\"' && base[i] != '\0')
			++i;
	}
	result = strjoin(result, base, i);
	if (result == NULL)
		return (NULL);
	if (is_ok == 1 && base[i] == '$' && (is_name_var(base[i + 1]) == 1 || base[i + 1] == '?'))
	{
		var = grab_var(base + i, data);
		if (var == NULL)
			return (NULL);
		result = strjoin(result, var, ft_strlen(var));
		if (result == NULL)
			return (NULL);
		j = 0;
		++i;
		while (base[i] != '?' && base[i + j] && is_name_var(base[i + j]) == 1)
			++j;
		if (base[i] == '?')
			++i;
		result = double_quote(data, &base[i] + j, result, 1);
	}
	return (result);
}
