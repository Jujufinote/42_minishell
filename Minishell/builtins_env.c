/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:47:15 by jverdier          #+#    #+#             */
/*   Updated: 2025/04/01 17:58:28 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_data *data, t_token *token, int exit_status, int err)
{
	if (token == NULL || (token->op == 1 && token->str[0] == '|'))
		exit_status = print_sorted(data, NULL, -1);
	while (token != NULL && ft_strncmp(token->base, "|", 2) != 0)
	{
		if (is_redirection(token) == 1)
			token = token->next;
		else if (is_all_name_var(token->str) == 1)
		{
			ft_putstr_fd("export : << ", 2);
			ft_putstr_fd(token->str, 2);
			ft_putstr_fd(" >> : not a valid identifier\n", 2);
			err = 1;
		}
		else if (ft_strchr(token->str, '=') != NULL \
		&& is_env(data->env, token->str) == 0)
			exit_status = modif_env(data, token->str, -1);
		else if (is_env(data->env, token->str) == 1)
			exit_status = add_env(data, token->str);
		token = token->next;
	}
	if (err == 1)
		return (1);
	return (exit_status);
}

int	unset(t_data *data, t_token *token)
{
	int		i;
	char	*var;

	while (token != NULL && ft_strncmp(token->base, "|", 2) != 0)
	{
		if (token != NULL && is_redirection(token) == 1)
			token = token->next;
		else
		{
			i = 0;
			var = ft_strjoin(token->str, "=");
			if (search_supp(data, token, var, i) == 1)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int	search_supp(t_data *data, t_token *token, char *var, int i)
{
	while (data->env[i] != NULL)
	{
		if (ft_strnstr(data->env[i], var, ft_strlen(var)) != NULL)
		{
			if (supp_env(data, var, 0, 0) == 1)
				return (1);
			else
				break ;
		}
		else if (ft_strnstr(data->env[i], token->str,
				ft_strlen(token->str)) != NULL)
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
	return (0);
}

int	env(char **env, t_token *token)
{
	while (token != NULL && ft_strncmp(token->base, "|", 2) != 0)
	{
		if (is_redirection(token) == 1)
			token = token->next;
		else if (token != NULL && token->file == 1)
			return (ft_putstr_fd("env : too many arguments\n", 2), 1);
		token = token->next;
	}
	print_tab(env);
	return (0);
}
