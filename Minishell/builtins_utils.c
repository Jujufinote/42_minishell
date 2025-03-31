/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:55:53 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/31 18:28:05 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_opt_echo(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		++i;
	}
	return (1);
}

int	update_pwd(t_data *data)
{
	char	*pwd;
	char	*temp;
	char	*old_pwd;

	old_pwd = ft_strjoin("OLDPWD=", ft_getenv("PWD", data));
	if (old_pwd == NULL)
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	if (modif_env(data, old_pwd) == 1)
		return (free(old_pwd), 1);
	free(old_pwd);
	temp = getcwd(NULL, 0);
	if (temp == NULL)
		return (perror("getcwd "), 1);
	pwd = ft_strjoin("PWD=", temp);
	if (pwd == NULL)
		return (free(temp), ft_putstr_fd("Error in memory allocation\n", 2), 1);
	free(temp);
	if (modif_env(data, pwd) == 1)
		return (free(pwd), 1);
	free(pwd);
	return (0);
}

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str) + 1) == 0)
		return (1);
	if (ft_strncmp(str, "cd", ft_strlen(str) + 1) == 0)
		return (1);
	if (ft_strncmp(str, "pwd", ft_strlen(str) + 1) == 0)
		return (1);
	if (ft_strncmp(str, "export", ft_strlen(str) + 1) == 0)
		return (1);
	if (ft_strncmp(str, "unset", ft_strlen(str) + 1) == 0)
		return (1);
	if (ft_strncmp(str, "env", ft_strlen(str) + 1) == 0)
		return (1);
	if (ft_strncmp(str, "exit", ft_strlen(str) + 1) == 0)
		return (1);
	return (0);
}

int	too_many_arg(t_token *token, char *cmd)
{
	if (token != NULL && ft_strncmp(token->post_str, "|", 2) != 0)
	{
		while (token != NULL && ft_strncmp(token->post_str, "|", 2) != 0)
		{
			if (is_redirection(token->str) == 1)
				token = token->next;
			else if (token->file == 1)
			{
				token = token->next;
				break ;
			}
			token = token->next;
		}
		while (token != NULL && ft_strncmp(token->post_str, "|", 2) != 0)
		{
			if (is_redirection(token->str) == 1)
				token = token->next;
			else if (token->file == 1)
			{
				ft_putstr_fd(cmd, 2);
				return (ft_putstr_fd(" : too many arguments\n", 2), 1);
			}
			token = token->next;
		}
	}
	return (0);
}

int	find_next_arg(t_token *token)
{
	while (token != NULL && ft_strncmp(token->post_str, "|", 2) != 0)
	{
		if (is_redirection(token->str) == 1)
			token = token->next;
		else if (token->file == 1)
			return (1);
		token = token->next;
	}
	return (0);
}
