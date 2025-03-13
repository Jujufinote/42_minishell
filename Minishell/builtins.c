/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:41:32 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/13 12:48:57 by jverdier         ###   ########.fr       */
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

int	pwd(void)
{
	char	*value;

	value = getcwd(NULL, 0);
	if (value == NULL)
		return (perror("pwd "), 1);
	printf("%s\n", value);
	free(value);
	return (0);
}

int	cd(t_data *data, t_token *token, char *home)
{
	char	*path;
	int		res;

	if (too_many_arg(token) == 1)
		return (1);
	res = cd_shortcuts(data, token, home);
	if (res == 1)
		return (1);
	else if (res == 0)
	{
		path = strdup(token->str);
		if (ft_strncmp(token->str, "~/", 2) == 0)
		{
			free(path);
			path = ft_strjoin(home, &token->str[1]);
			if (path == NULL)
				return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
		}
		if (chdir(path) != 0)
			return (free(path), perror("cd"), 1);
		free(path);
	}
	if (update_pwd(data) == 1)
		return (1);
	return (0);
}

int	cd_shortcuts(t_data *data, t_token *token, char *home)
{
	char	*path;

	if (token == NULL || token->file != 1 \
	|| ft_strncmp(token->str, "~", 2) == 0)
	{
		if (home == NULL)
			return (printf("cd : HOME not set\n"), 1);
		if (chdir(home) != 0)
			return (perror("cd"), 1);
		return (2);
	}
	else if (ft_strncmp(token->str, "-", 2) == 0)
	{
		path = ft_getenv("OLDPWD", data);
		if (path == NULL)
			return (ft_putstr_fd("cd : <<OLDPWD>> not set\n", 2), 1);
		ft_putstr_fd(path, data->files->saved_out);
		ft_putstr_fd("\n", data->files->saved_out);
		if (chdir(path) != 0)
			return (perror("cd "), 1);
		return (2);
	}
	return (0);
}

int	ft_exit(t_data *data, t_token *token)
{
	int		status;

	ft_putstr_fd("exit\n", data->files->saved_out);
	rl_clear_history();
	status = EXIT_SUCCESS;
	if (token != NULL && is_all_num(token->str) == 1)
		status = ft_atoi(token->str);
	if (token != NULL && is_all_num(token->str) == 0)
		ft_putstr_fd("exit : numeric argument required\n", 2);
	else if (too_many_arg(token) == 1)
		return (1);
	free_data(data);
	exit(status);
}
