/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:46:49 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/13 12:10:03 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_unused_fd(int **pipefd, int nb_pipes, int i)
{
	int	j;

	j = 0;
	while (j < nb_pipes)
	{
		if (j != (i - 1))
			close(pipefd[j][0]);
		if (j != i)
			close(pipefd[j][1]);
		j++;
	}
	return ;
}

void	close_all(int **pipefd, int nb_pipes)
{
	int	j;

	j = 0;
	while (j < nb_pipes)
	{
		close(pipefd[j][0]);
		close(pipefd[j][1]);
		j++;
	}
	return ;
}

void	free_data(t_data *data)
{
	free_dtab(data->env);
	free_pipe(data);
	free(data->pipe);
	free_hd(data);
	free(data->hd);
	free(data->files);
	if (data->tokens != NULL)
	{
		lstdel(data->tokens);
		free(data->tokens);
	}
	free(data);
	return ;
}

void	free_dtab(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		++i;
	}
	free(array);
	return ;
}

void	free_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (data->pipe->pipefd != NULL && i < data->pipe->nb_pipe)
	{
		free(data->pipe->pipefd[i]);
		i++;
	}
	free(data->pipe->pipefd);
	data->pipe->pipefd = NULL;
	free(data->pid);
	data->pid = NULL;
	return ;
}
