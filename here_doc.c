/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 11:39:01 by jverdier          #+#    #+#             */
/*   Updated: 2025/02/06 16:07:13 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_heredoc(t_data *data, t_token *token, int i)
{
	char	*line;
	
	if (token->before->str[0] == '<' && token->before->op == 2)
	{
		data->files->file_in = open(HD, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->files->file_in == -1)
			return (ft_putstr_fd("Error opening/creating heredoc file\n", 2), 1);
		while (1)
		{
			line = readline("> ");
			if (line == NULL \
			|| ft_strncmp(line, token->str, ft_strlen(line)) == 0)
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, data->files->file_in);
			ft_putstr_fd("\n", data->files->file_in);
			free(line);
		}
		redir_hd(data, i);
	}
	return (0);
}

void	redir_hd(t_data *data, int i)
{
	dup2(data->files->file_in, STDIN_FILENO);
	close(data->files->file_in);
	if (i > 0)
		close(data->pipefd[i - 1][0]);
	return ;
}
