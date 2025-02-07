/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:33:49 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/22 22:01:57 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_env(char **envp)
{
	char	**env;
	int		len;
	int		i;

	len = 0;
	while (envp[len] != NULL)
		++len;
	env = malloc(sizeof(char *) * (len + 1));
	if (env == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		env[i] = ft_strdup(envp[i]);
		if (env[i] == NULL)
			return (NULL);
		++i;
	}
	env[i] = NULL;
	return (env);
}

int	add_env(t_data *data, char *var)
{
	char	**env2;
	int		len;
	int		i;

	len = 0;
	while (data->env[len] != NULL)
		++len;
	env2 = malloc(sizeof(char *) * (len + 2));
	if (env2 == NULL)
		return (printf("Error in memory allocation\n"), 1);
	i = 0;
	while (i < len)
	{
		env2[i] = ft_strdup(data->env[i]);
		if (env2[i] == NULL)
			return (printf("Error in memory allocation\n"), 1);
		++i;
	}
	env2[i] = ft_strdup(var);
	env2[++i] = NULL;
	free_dtab(data->env);
	data->env = env2;
	return (0);
}

char	**env_alloc(char **env)
{
	int		len;
	
	len = 0;
	while (env[len] != NULL)
		++len;
	return (malloc(sizeof(char *) * (len)));
}

int	supp_env(t_data *data, char *name)
{
	char	**env2;
	int		i;
	int		j;

	env2 = env_alloc(data->env);
	if (env2 == NULL)
		return (free(name), ft_putstr_fd("Error in memory allocation\n", 2), 1);
	i = 0;
	j = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], name, ft_strlen(name)) == 0)
			++i;
		if (data->env[i] == NULL)
			break;
		env2[j] = ft_strdup(data->env[i]);
		if (env2[j] == NULL)
			return (free(name), free_dtab(env2), ft_putstr_fd("Error in memory allocation\n", 2), 1);
		++i;
		++j;
	}
	env2[j] = NULL;
	free_dtab(data->env);
	data->env = env2;
	return (free(name), 0);
}

int	modif_env(t_data *data, char *str)
{
	char	*name;
	int		i;

	name = getname(str);
	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(data->env[i], name, ft_strlen(name)) == 0)
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(str);
			if (data->env[i] == NULL)
				return (printf("Error in memory allocation\n"), 1);
			free(name);
			return (0);
		}
		++i;
	}
	free(name);
	return (0);
}
