/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:54:56 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/28 14:30:55 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_data *data, char **cmdoption)
{
	char	*path;

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
