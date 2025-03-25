/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:43:03 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/25 17:30:33 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prep_exec(t_data *data, char *input)
{
	if (*input != '\0' && is_hd_alone(input) == 0)
		add_history(input);
	if (*input != '\0' && parsing(input) != 1)
	{
		data->tokens = tokenisation(data, input);
		if (data->tokens == NULL)
		{
			data->last_exit_status = 1;
			ft_putstr_fd("Error in memory allocation\n", 2);
		}
		else if (checking(*data->tokens) != 1)
			execution(data);
	}
	else
		data->last_exit_status = 1;
	return ;
}

int	prep_pipe(t_data *data)
{
	data->pid = pid_alloc(data->pipe->nb_pipe + 1);
	if (data->pid == NULL)
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	data->pipe->pipefd = pipefd_alloc(data->pipe->nb_pipe);
	if (data->pipe->pipefd == NULL)
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	return (0);
}

int	prep_hd(t_data *data)
{
	int		hd;
	int		i;
	t_token	*token;

	token = *data->tokens;
	hd = count_hd(token);
	data->hd->nb_hd = hd;
	data->hd->hdfd = pipefd_alloc(hd);
	if (data->hd->hdfd == NULL)
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	token = *data->tokens;
	i = 0;
	while (token != NULL)
	{
		if (token->op == 2 && ft_strncmp(token->post_str, "<<", 3) == 0)
		{
			token = token->next;
			fill_hd(data->hd->hdfd, i, final_replacement(data, token->post_str, NULL));
			++i;
		}
		token = token->next;
	}
	return (0);
}

int	prep_tab(char *array, int temp)
{
	int	i;

	i = 0;
	while (temp != 0 && temp > 0)
	{
		temp /= 10;
		++i;
	}
	temp = i;
	while (i < 4)
	{
		array[i] = '\0';
		++i;
	}
	return (temp);
}
