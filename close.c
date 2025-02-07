/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:10:45 by jverdier          #+#    #+#             */
/*   Updated: 2025/02/03 11:25:58 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(t_data *data)
{
	if (data->files->is_in == 1)
	{
		dup2(data->files->saved_in, STDIN_FILENO);
		data->files->is_in = 0;
	}
	if (data->files->is_out == 1)
	{
		dup2(data->files->saved_out, STDOUT_FILENO);
		data->files->is_out = 0;
	}
	return ;
}

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
