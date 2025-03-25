/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:47:15 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/25 17:56:04 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_data *data, t_token *token)
{
	int		exit_status;

	exit_status = 0;
	if (token == NULL || (token->op == 1 && token->str[0] == '|'))
		exit_status = printf_sorted(data);
	while (token != NULL && ft_strncmp(token->post_str, "|", 2) != 0)
	{
		if (is_redirection(token->str) == 1)
			token = token->next->next;
		if (is_all_name_var(token->str) == 1)
		{
			ft_putstr_fd("export : << ", 2);
			ft_putstr_fd(token->str, 2);
			ft_putstr_fd(" >> : not a valid identifier\n", 2);
		}
		else if (ft_strchr(token->str, '=') != NULL && is_env(data->env, token->str) == 0)
			exit_status = modif_env(data, token->str);
		else if (is_env(data->env, token->str) == 1)
			exit_status = add_env(data, token->str);
		token = token->next;
	}
	return (exit_status);
}

int	unset(t_data *data, t_token *token)
{
	int		i;
	char	*var;

	while (token != NULL && ft_strncmp(token->post_str, "|", 2) != 0)
	{
		if (is_redirection(token->str) == 1)
			token = token->next->next;
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
	while (token != NULL && ft_strncmp(token->post_str, "|", 2) != 0)
	{
		if (is_redirection(token->str) == 1)
			token = token->next->next;
		else if (token != NULL && token->file == 1)
			return (ft_putstr_fd("env : too many arguments\n", 2), 1);
	}
	print_tab(env);
	return (0);
}

int	printf_sorted(t_data *data)
{
	int		i;
	int		j;
	char	**sorted;

	sorted = create_env(data->env);
	if (sorted == NULL)
	{
		ft_putstr_fd("Error in memory allocation\n", 2);
		return (1);
	}
	bubble_sort_tab(sorted);
	i = 0;
	while (sorted[i] != NULL)
	{
		printf("declare -x ");
		j = 0;
		while (sorted[i][j] != 0 && sorted[i][j] != '=')
		{
			printf("%c", sorted[i][j]);
			++j;
		}
		if (sorted[i][j] == '=')
			printf("%c\"%s\"\n", sorted[i][j], &sorted[i][j + 1]);
		else
			printf("\n");
		++i;
	}
	free_dtab(sorted);
	return (0);
}

void	print_tab(char **table)
{
	int	i;

	i = 0;
	while (table[i] != NULL)
	{
		if (ft_strchr(table[i], '=') != NULL)
			printf("%s\n", table[i]);
		++i;
	}
	return ;
}
