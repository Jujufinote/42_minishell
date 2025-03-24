/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:46:30 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/23 15:14:33 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init(t_data *data, char **envp)
{
	data->last_exit_status = 0;
	data->env = create_env(envp);
	if (data->env == NULL)
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	if (init_structs(data) == 1)
		return (1);
	data->pid = NULL;
	data->pipe->nb_pipe = 0;
	data->pipe->pipefd = NULL;
	data->hd->hdfd = NULL;
	data->hd->nb_hd = 0;
	data->hd->num_hd = 0;
	data->files->file_in = 0;
	data->files->file_out = 0;
	data->tokens = NULL;
	return (0);
}

int	init_structs(t_data *data)
{
	data->pipe = malloc(sizeof(t_pipe));
	if (data->pipe == NULL)
	{
		free_dtab(data->env);
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	}
	data->hd = malloc(sizeof(t_hd));
	if (data->hd == NULL)
	{
		free_dtab(data->env);
		free(data->pipe);
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	}
	data->files = malloc(sizeof(t_files));
	if (data->files == NULL)
	{
		free_dtab(data->env);
		free(data->pipe);
		free(data->hd);
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	}
	return (0);
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
