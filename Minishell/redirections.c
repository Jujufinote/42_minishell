/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 18:36:52 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/31 18:52:04 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection(t_data *data, t_token *token, int i)
{
	if (data->pipe->nb_pipe > 0)
	{
		if (redir_base(data, i) == 1)
			return (free_data(data), 1);
	}
	while (token != NULL && ft_strncmp(token->post_str, "|", 2) != 0)
	{
		if (is_redirection(token->str) == 1)
		{
			token = token->next;
			if (redir_in(data, token, i) == 1 \
			|| redir_hd(data, token, i) == 1 \
			|| redir_out(data, token, i) == 1 \
			|| redir_append(data, token, i) == 1)
				return (free_data(data), 1);
		}
		token = token->next;
	}
	return (0);
}

int	redir_base(t_data *data, int i)
{
	if (i == 0)
		dup2(data->pipe->pipefd[i][1], STDOUT_FILENO);
	else if (i < data->pipe->nb_pipe)
	{
		dup2(data->pipe->pipefd[i - 1][0], STDIN_FILENO);
		dup2(data->pipe->pipefd[i][1], STDOUT_FILENO);
	}
	else if (i == data->pipe->nb_pipe)
	{
		dup2(data->pipe->pipefd[i - 1][0], STDIN_FILENO);
		dup2(data->files->saved_out, STDOUT_FILENO);
	}
	close_unused_fd(data->pipe->pipefd, data->pipe->nb_pipe, i);
	return (0);
}

int	redir_in(t_data *data, t_token *token, int i)
{
	if (token->before->str[0] == '<' && token->before->op == 1)
	{
		if (access(token->str, F_OK | R_OK) != 0)
			return (ft_putstr_fd(token->str, 2), perror(" "), 1);
		data->files->file_in = open(token->str, O_RDONLY);
		if (data->files->file_in == -1)
			return (ft_putstr_fd("Error opening file\n", 2), 1);
		dup2(data->files->file_in, STDIN_FILENO);
		close(data->files->file_in);
		if (i > 0)
			close(data->pipe->pipefd[i - 1][0]);
	}
	return (0);
}

int	redir_out(t_data *data, t_token *token, int i)
{
	if (token->before->str[0] == '>' && token->before->op == 1)
	{
		if (access(token->str, F_OK) == 0 && access(token->str, W_OK) != 0)
			return (ft_putstr_fd(token->str, 2), perror(" "), 1);
		data->files->file_out = open(token->str,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->files->file_out == -1)
			return (ft_putstr_fd("Error opening/creating file\n", 2), 1);
		dup2(data->files->file_out, STDOUT_FILENO);
		close(data->files->file_out);
		if (i < data->pipe->nb_pipe)
			close(data->pipe->pipefd[i][1]);
	}
	return (0);
}

int	redir_append(t_data *data, t_token *token, int i)
{
	if (token->before->str[0] == '>' && token->before->op == 2)
	{
		if (access(token->str, F_OK) == 0 && access(token->str, W_OK) != 0)
			return (ft_putstr_fd(token->str, 2), perror(" "), 1);
		data->files->file_out = open(token->str,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (data->files->file_out == -1)
			return (ft_putstr_fd("Error in appending/creating file\n", 2), 1);
		dup2(data->files->file_out, STDOUT_FILENO);
		close(data->files->file_out);
		if (i < data->pipe->nb_pipe)
			close(data->pipe->pipefd[i][1]);
	}
	return (0);
}
