/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:39:01 by jverdier          #+#    #+#             */
/*   Updated: 2025/04/01 14:17:48 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_hd(int **hdfd, int i, char *delimiter)
{
	char	*line;

	if (delimiter == NULL)
	{
		ft_putstr_fd("Error in memory allocation\n", 2);
		return ;
	}
	while (1)
	{
		line = readline("> ");
		if (line == NULL \
		|| ft_strncmp(line, delimiter, ft_strlen(line) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, hdfd[i][1]);
		ft_putstr_fd("\n", hdfd[i][1]);
		free(line);
	}
	free(delimiter);
	close(hdfd[i][1]);
	return ;
}

int	redir_hd(t_data *data, t_token *token, int i)
{
	if (token->before->str[0] == '<' && token->before->op == 2)
	{
		dup2(data->hd->hdfd[data->hd->num_hd][0], STDIN_FILENO);
		if (i > 0)
			close(data->pipe->pipefd[i - 1][0]);
	}
	return (0);
}

int	is_hd_alone(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0 && is_whitespace(str[i]) == 1)
		++i;
	if (str[i] != 0 && str[i] == '<' && str[i + 1] == '>')
	{
		i += 2;
		while (str[i] != 0 && is_whitespace(str[i]) == 1)
			++i;
		if (str[i] == 0)
			return (0);
		while (str[i] != 0 && is_whitespace(str[i]) == 0)
			++i;
		while (str[i] != 0 && is_whitespace(str[i]) == 1)
			++i;
		if (str[i])
			return (1);
	}
	return (0);
}

void	next_hd(t_data *data, t_token *token)
{
	while (token != NULL && ft_strncmp(token->post_str, "|", 2) != 0)
	{
		if (is_redirection(token) == 1)
		{
			token = token->next;
			if (token->before->str[0] == '<' && token->before->op == 2)
				data->hd->num_hd += 1;
		}
		token = token->next;
	}
	return ;
}

void	free_hd(t_data *data)
{
	int	i;

	i = 0;
	if (data->hd->hdfd != NULL)
	{
		while (i < data->hd->nb_hd)
		{
			free(data->hd->hdfd[i]);
			i++;
		}
		free(data->hd->hdfd);
		data->hd->hdfd = NULL;
	}
	return ;
}
