/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:41:32 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/22 21:57:45 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_token *token)
{
	int	nline;

	nline = 1;
	while (token != NULL && is_valid_opt_echo(token->str) == 1)
	{
		nline = 0;
		token = token->next;
	}
	while (token != NULL && token->op == 0)
	{
		printf("%s", token->str);
		if (token->next != NULL && token->next->file == 1)
			printf(" ");
		token = token->next;
	}
	if (nline == 1)
		printf("\n");
	return (0);
}

int	pwd(t_data *data)
{
	char	*value;

	value = ft_getenv("PWD", data);
	if (value == NULL)
		return (perror("pwd"), 1);
	printf("%s\n", value);
	return (0);
}

int	cd(t_data *data, t_token *token)
{
	char	*home;

	home = ft_getenv("HOME", data);
	if (token != NULL && token->next != NULL \
	&& token->next->file == 1)
		return (ft_putstr_fd("cd : too many arguments\n", 2), 1);
	if (token == NULL || token->file != 1)
	{
		if (home == NULL)
			return (printf("cd : HOME not set\n"), 1);
		if (chdir(home) != 0)
			return (perror("cd"), 1);
	}
	else
	{
		if (chdir(token->str) != 0)
			return(perror("cd"), 1);
	}
	if (update_pwd(data, token) == 1)
		return (1);
	return (0);
}

int	ft_exit(t_data *data)
{
	rl_clear_history();
	free_data(data);
	exit(0);
}
