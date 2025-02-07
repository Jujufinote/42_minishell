/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 16:47:15 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/22 22:00:32 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_data *data, t_token *token)
{
	t_token	*temp;
	char	*name;
	int		exit_status;
	
	exit_status = 0;
	temp = token;
	while (temp != NULL && temp->option != 1 && temp->op != 1)
		temp = temp->next;
	if (temp != NULL && temp->option == 1)
		return (ft_putstr_fd("export : no options supported\n", 2), 1);
	while (token != NULL && token->file == 1)
	{
		name = getname(token->str);
		if (ft_strchr(token->str, '=') != NULL && ft_getenv(name, data) != NULL)
			exit_status = modif_env(data, token->str);
		else if (ft_strchr(token->str, '=') != NULL)
			exit_status = add_env(data, token->str);
		token = token->next;
		free(name);
	}
	return (exit_status);
}

int	unset(t_data *data, t_token *token)
{
	t_token	*temp;
	int		exit_status;

	exit_status = 0;
	temp = token;
	while (temp != NULL && temp->option != 1 && temp->op != 1)
		temp = temp->next;
	if (temp != NULL && temp->option == 1)
		return (ft_putstr_fd("unset : no options supported\n", 2), 1);
	while (token != NULL && token->file == 1)
	{
		if (ft_getenv(token->str, data) != NULL)
			exit_status = supp_env(data, ft_strjoin(token->str, "="));
		token = token->next;
	}
	return (exit_status);
}

int	env(char **env, t_token *token)
{
	if (token != NULL && (token->file == 1 || token->option == 1))
		return (ft_putstr_fd("env : too many arguments\n", 2), 1);
	print_tab(env);
	return (0);
}
