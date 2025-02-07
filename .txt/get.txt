/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:05:54 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/22 21:56:47 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getname(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i + 1));
}

char	*ft_getenv(char	*name, t_data *data)
{
	char	*value;
	char	*name2;
	int		i;
	
	i = 0;
	value = NULL;
	name2 = ft_strdup(name);
	if (name2 == NULL)
		return (printf("Error in memory allocation\n"), NULL);
	name2 = strjoin(name2, "=", 1);
	if (name2 == NULL)
		return (printf("Error in memory allocation\n"), NULL);
	while (data->env[i] != NULL)
	{
		if (ft_strnstr(data->env[i], name2, ft_strlen(name2)) != NULL)
			value = &data->env[i][ft_strlen(name2)];
		++i;
	}
	free(name2);
	return (value);
}

char	*grab_var(char *base, t_data *data)
{
	int	i;
	char	*name;
	char	*var;

	i = 0;
	while(base[i] != '\0' && is_name_var(base[i]) == 1)
		++i;
	name = ft_substr(base, 0, i);
	if (name == NULL)
	{
		printf("Error in memory allocation\n");
		return (NULL);
	}
	var = ft_getenv(name, data);
	free(name);
	if (var == NULL)
		return ("");
	return (var);
}
