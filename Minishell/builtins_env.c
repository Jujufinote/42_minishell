/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:47:15 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/22 14:51:43 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_data *data, t_token *token)
{
	char	*name;
	int		exit_status;

	exit_status = 0;
	if (token == NULL || (token->op == 1 && token->str[0] == '|'))
		exit_status = printf_sorted(data);
	while (token != NULL && token->file == 1)
	{
		name = getname(token->str);
		if (ft_strchr(token->str, '=') != NULL && ft_getenv(name, data) != NULL)
			exit_status = modif_env(data, token->str);
		else
			exit_status = add_env(data, token->str);
		token = token->next;
		free(name);
	}
	return (exit_status);
}

int	unset(t_data *data, t_token *token)
{
	int		i;
	char	*var;

	while (token != NULL && token->file == 1)
	{
		i = 0;
		var = ft_strjoin(token->str, "=");
		while (data->env[i] != NULL)
		{
			if (ft_strnstr(data->env[i], var, ft_strlen(var)) != NULL)
			{
				if (supp_env(data, var, 0, 0) == 1)
					return (1);
				else
					break ;
			}
			else if (ft_strnstr(data->env[i], token->str, ft_strlen(token->str)) != NULL)
			{
				if (supp_env(data, ft_strdup(token->str), 0, 0) == 1)
					return (free(var), 1);
				else
				{
					free(var);
					break ;
				}
			}
			++i;
		}
		token = token->next;
	}
	return (0);
}

int	env(char **env, t_token *token)
{
	if (token != NULL && token->file == 1)
		return (ft_putstr_fd("env : too many arguments\n", 2), 1);
	print_tab(env);
	return (0);
}

int	printf_sorted(t_data *data)
{
	int		i;
	char	**sorted;

	sorted = create_env(data->env);
	if (sorted == NULL)
	{
		ft_putstr_fd("Error in memory allocation\n", data->files->saved_out);
		return (1);
	}
	bubble_sort_tab(sorted);
	i = 0;
	while (sorted[i] != NULL)
	{
		printf("declare -x %s\n", sorted[i]);
		++i;
	}
	free_dtab(sorted);
	return (0);
}
