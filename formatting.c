/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:26:40 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/22 21:53:39 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*formatting(t_data *data, char *base)
{
	char	*result;

	if (base == NULL)
		return (base);
	result = replacement(data, base, NULL);
	free(base);
	if (result == NULL)
		printf("Error in memory allocation\n");
	return (result);
}

char	*replacement(t_data *data, char *base, char *result)
{
	int	i;
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
			result = double_quote(data, base + i + 1, result);
			i += length(&base[i + 1], '\"') + 2;
		}
		else if (base[i] == '$' && base[i + 1] != '?')
		{
			var = grab_var(base + i + 1, data);
			if (var == NULL)
				return (NULL);
			result = strjoin(result, var, ft_strlen(var));
			if (result == NULL)
				return (NULL);
			i += length(&base[i], ' ');
		}
		else
		{
			result = strjoin(result, &base[i], 1);
			++i;
		}
		if (result == NULL)
			break;
	}
	return (result);
}

char	*single_quote(char *base, char *result)
{
	int	i;

	i  = 0;
	while (base[i] != '\'' && base[i] != '\0')
		++i;
	result = strjoin(result, base, i);
	return (result);
}

char	*double_quote(t_data *data, char *base, char *result)
{
	int i;
	char	*var;

	i = 0;
	while (base[i] != '\"' && base[i] != '\0' && base[i] != '$')
		++i;
	result = strjoin(result, base, i);
	if (result == NULL)
		return (NULL);
	if (base[i] == '$' && base[i + 1] != '?')
	{
		var = grab_var(base + i + 1, data);
		if (var == NULL)
			return (NULL);
		result = strjoin(result, var, ft_strlen(var));
		if (result == NULL)
			return (NULL);
		if (base[i + 1] == '{')
			result = double_quote(data, &base[i] + length(&base[i], '}'), result);
		else
			result = double_quote(data, &base[i] + length(&base[i], ' '), result);
	}
	return (result);
}
