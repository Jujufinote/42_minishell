/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:46:49 by jverdier          #+#    #+#             */
/*   Updated: 2025/02/07 15:13:26 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	free_dtab(data->env);
	free_dtab(data->paths);
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
	while (i < data->nb_pipe)
	{
		free(data->pipefd[i]);
		i++;
	}
	free(data->pipefd);
	data->pipefd = NULL;
/*	i = 0;
	while (i < data->nb_pipe + 1)
	{
		waitpid(data->pid[i], NULL, 0);
		i++;
	}*/
	free(data->pid);
	data->pid = NULL;
	return ;
}
