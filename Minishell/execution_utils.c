/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:54:56 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/12 23:55:14 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char **cmdoption, char **envp, char **env)
{
	char	*path;

	if (cmdoption == NULL)
	{
		perror("Error separation command-option ");
		exit(EXIT_FAILURE);
	}
	if (cmdoption[0] == NULL)
		exit(EXIT_SUCCESS);
	path = ft_access(envp, cmdoption[0]);
	if (path == NULL)
	{
		free_dtab(cmdoption);
		exit(errno);
	}
	if (execve(path, cmdoption, env) == -1)
	{
		perror("Error executing ");
		free(path);
		free_dtab(cmdoption);
		exit(errno);
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
			data->last_exit_status = WEXITSTATUS(status);
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
				data->last_exit_status = WEXITSTATUS(status);
		}
	}
}
