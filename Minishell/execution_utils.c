/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:54:56 by jverdier          #+#    #+#             */
/*   Updated: 2025/04/02 16:06:33 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_data *data, char **cmdoption)
{
	char	*path;

	is_ok(data, cmdoption);
	path = ft_access(data->env, cmdoption[0]);
	if (path == NULL)
	{
		free_dtab(cmdoption);
		free_data(data);
		exit(errno);
	}
	if (execve(path, cmdoption, data->env) == -1)
	{
		perror("Error executing ");
		free_dtab(cmdoption);
		free_data(data);
		exit(errno);
	}
	return ;
}

void	is_ok(t_data *data, char **cmdoption)
{
	if (cmdoption == NULL)
	{
		perror("Error separation command-option ");
		free_data(data);
		exit(EXIT_FAILURE);
	}
	if (cmdoption[0] == NULL)
	{
		free_data(data);
		free_dtab(cmdoption);
		exit(EXIT_SUCCESS);
	}
	return ;
}

void	ft_wait(t_data *data, int i)
{
	int	status;

	if (i == -2)
	{
		if (waitpid(data->pid1, &status, 0) == -1)
		{
			perror("waitpid ");
			return ;
		}
		if (WIFEXITED(status))
			data->last_exit = WEXITSTATUS(status);
	}
	else
	{
		while (++i < data->pipe->nb_pipe + 1)
		{
			if (waitpid(data->pid[i], &status, 0) == -1)
			{
				perror("waitpid ");
				return ;
			}
			if (WIFEXITED(status))
				data->last_exit = WEXITSTATUS(status);
		}
	}
}

void	what_exit(t_data *data, int exit_status)
{
	if (exit_status == 1)
	{
		free_data(data);
		exit(EXIT_FAILURE);
	}
	if (exit_status == 0)
	{
		free_data(data);
		exit(EXIT_SUCCESS);
	}
	return ;
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
