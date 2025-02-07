/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 22:55:53 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/21 19:47:54 by jverdier         ###   ########.fr       */
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

int	update_pwd(t_data *data, t_token *token)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = ft_strjoin("OLDPWD=", ft_getenv(ft_strdup("PWD"), data));
	if (old_pwd == NULL)
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	if (token == NULL || token->file != 1)
		pwd = ft_strjoin("PWD=", ft_getenv(ft_strdup("HOME"), data));
	else if (token->str[0] == '/')
		pwd = ft_strjoin("PWD=", token->str);
	else
	{
		pwd = ft_strjoin("PWD=", ft_getenv(ft_strdup("PWD"), data));
		if (pwd == NULL)
			return (free(old_pwd), ft_putstr_fd("Error in memory allocation\n", 2), 1);
		pwd = strjoin(pwd, "/", 1);
		if (pwd == NULL)
			return (free(old_pwd), ft_putstr_fd("Error in memory allocation\n", 2), 1);
		pwd = strjoin (pwd, token->str, ft_strlen(token->str));
	}
	if (pwd == NULL)
		return (free(old_pwd), ft_putstr_fd("Error in memory allocation\n", 2), 1);
	if (modif_env(data, pwd) == 1 || modif_env(data, old_pwd) == 1)
		return (free(pwd), free(old_pwd), 1);
	return (free(old_pwd), free(pwd), 0);
}
