/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:46:30 by jverdier          #+#    #+#             */
/*   Updated: 2025/02/06 15:56:01 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(t_data *data, char **envp)
{
	data->last_exit_status = 0;
	data->env = create_env(envp);
	if (data->env == NULL)
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	data->paths = make_paths(envp);
	if (data->paths == NULL)
	{
		free_dtab(data->env);
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	}
	data->nb_pipe = 0;
	data->pid = NULL;
	data->pipefd = NULL;
	data->files = malloc(sizeof(t_files));
	if (data->files == NULL)
	{
		free_dtab(data->env);
		free_dtab(data->paths);
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	}
	data->files->file_in = 0;
	data->files->file_out = 0;
	data->tokens = NULL;
	return (0);
}

int	*pid_alloc(int nb_commands)
{
	int	*pid;

	pid = malloc(sizeof(pid_t) * nb_commands);
	if (!pid)
		return (NULL);
	return (pid);
}

int	**pipefd_alloc(int nb_pipes)
{
	int	**pipefd;

	pipefd = (int **)malloc(sizeof(int *) * nb_pipes);
	if (!pipefd)
		return (NULL);
	pipefd = make_pipefds(pipefd, nb_pipes);
	if (pipefd == NULL)
		return (NULL);
	return (pipefd);
}

int	**make_pipefds(int **pipefd, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		if (pipe(pipefd[i]) == -1)
		{
			while (i >= 0)
			{
				free(pipefd[i]);
				--i;
			}
			free(pipefd);
			return (NULL);
		}
		i++;
	}
	return (pipefd);
}

int	prep_pipe(t_data *data)
{
	data->pid = pid_alloc(data->nb_pipe + 1);
	if (data->pid == NULL)
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	data->pipefd = pipefd_alloc(data->nb_pipe);
	if (data->pipefd == NULL)
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	return (0);
}
