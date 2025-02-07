/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:54:56 by jverdier          #+#    #+#             */
/*   Updated: 2025/02/07 15:19:48 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(char **cmdoption, char **paths, char **env)
{
	char	*path;

	if (cmdoption == NULL)
	{
		perror("Error separation command-option ");
		exit(EXIT_FAILURE);
	}
	path = ft_access(paths, cmdoption[0]);
	if (path == NULL)
	{
		free_dtab(cmdoption);
		exit(EXIT_FAILURE);
	}
	printf("exec\n");
	if (execve(path, cmdoption, env) == -1)
	{
		perror("Error executing ");
		free(path);
		free_dtab(cmdoption);
		exit(EXIT_FAILURE);
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
		while (++i < data->nb_pipe + 1)
		{
			if (waitpid(data->pid[i], &status, 0) == -1)
			{
				perror("waitpid ");
				return ;
			}
			printf("fin wait %d\n", i);
			if (WIFEXITED(status))
				data->last_exit_status = WEXITSTATUS(status);
		}
	}
}
