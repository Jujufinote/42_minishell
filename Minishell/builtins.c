/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:41:32 by jverdier          #+#    #+#             */
/*   Updated: 2025/04/02 16:18:15 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_token *token)
{
	int	nline;

	nline = 1;
	while (token != NULL && ft_strncmp(token->base, "|", 2) != 0 \
	&& is_redirection(token) == 1)
		token = token->next->next;
	while (token != NULL && ft_strncmp(token->base, "|", 2) != 0 \
	&& is_valid_opt_echo(token->str) == 1)
	{
		if (is_redirection(token) == 1)
			token = token->next;
		nline = 0;
		token = token->next;
	}
	print_token_echo(token);
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

	if (token != NULL && too_many_arg(token, "cd") == 1)
		return (1);
	while (token != NULL && ft_strncmp(token->base, "|", 2) != 0 \
	&& is_redirection(token) == 1)
		token = token->next->next;
	res = cd_shortcuts(data, token, home);
	if (res == 1)
		return (1);
	else if (res == 0)
	{
		path = ft_strdup(token->str);
		if (chdir(path) != 0)
			return (free(path), perror("cd "), 1);
		free(path);
	}
	return (update_pwd(data));
}

int	cd_shortcuts(t_data *data, t_token *token, char *home)
{
	char	*path;

	if (token == NULL || token->file != 1 \
	|| ft_strncmp(token->post_str, "$HOME", 6) == 0)
	{
		if (home == NULL)
			return (printf("cd : HOME not set\n"), 1);
		if (chdir(home) != 0)
			return (perror("cd "), 1);
		return (2);
	}
	else if (ft_strncmp(token->str, "-", 2) == 0)
	{
		path = ft_getenv("OLDPWD", data);
		if (path == NULL)
			return (ft_putstr_fd("cd : <<OLDPWD>> not set\n", 2), 1);
		printf("%s\n", path);
		if (chdir(path) != 0)
			return (perror("cd "), 1);
		return (2);
	}
	return (0);
}

int	ft_exit(t_data *data, t_token *token, int status)
{
	if (data->pipe->nb_pipe == 0)
		ft_putstr_fd("exit\n", data->files->saved_out);
	while (token != NULL && ft_strncmp(token->base, "|", 2) != 0)
	{
		if (is_redirection(token) == 1)
			token = token->next;
		else if (is_all_num(token->str) == 1)
		{
			status = ft_atoi(token->str);
			break ;
		}
		else if (is_all_num(token->str) == 0)
		{
			status = 2;
			ft_putstr_fd("exit : numeric argument required\n", 2);
			break ;
		}
		token = token->next;
	}
	if (token != NULL && is_all_num(token->str) == 1 \
	&& too_many_arg(token, "exit") == 1)
		return (1);
	rl_clear_history();
	free_data(data);
	exit(status);
}
