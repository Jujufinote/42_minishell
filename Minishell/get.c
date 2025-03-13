/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:05:54 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/13 11:48:36 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getname(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
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
	int		i;
	char	*name;
	char	*var;

	if (ft_strncmp(base, "~", ft_strlen("~")) == 0)
		return (ft_getenv("HOME", data));
	base = base + 1;
	if (ft_strncmp(base, "?", ft_strlen("?")) == 0)
		return (get_last_exit_status(data->last_exit_status));
	if (ft_strncmp(base, "0", ft_strlen("0")) == 0)
		return (BASH);
	i = 0;
	while (base[i] != '\0' && is_name_var(base[i]) == 1)
		++i;
	name = ft_substr(base, 0, i);
	if (name == NULL)
	{
		ft_putstr_fd("Error in memory allocation\n", data->files->saved_out);
		return (NULL);
	}
	var = ft_getenv(name, data);
	free(name);
	if (var == NULL)
		return ("");
	return (var);
}

int	prep_tab(char *array, int temp)
{
	int	i;

	i = 0;
	while (temp != 0 && temp > 0)
	{
		temp /= 10;
		++i;
	}
	temp = i;
	while (i < 4)
	{
		array[i] = '\0';
		++i;
	}
	return (temp);
}

char	*get_last_exit_status(int num)
{
	static char	les[4];
	int			i;

	if (num == 0)
		i = 1;
	else
		i = prep_tab(les, num);
	while (num >= 10)
	{
		les[i - 1] = num % 10 + 48;
		num /= 10;
		i--;
	}
	if (num < 10)
		les[i - 1] = num + 48;
	return (les);
}
