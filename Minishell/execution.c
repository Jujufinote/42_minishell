/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:45:12 by jverdier          #+#    #+#             */
/*   Updated: 2025/04/01 15:12:41 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_data *data)
{
	t_token	*token;

	signal_handler(1);
	token = *data->tokens;
	data->pipe->nb_pipe = count_pipe(token);
	if (prep_hd(data) == 1)
		return ;
	data->files->saved_in = dup(STDIN_FILENO);
	data->files->saved_out = dup(STDOUT_FILENO);
	if (data->pipe->nb_pipe > 0)
	{
		if (prep_pipe(data) != 1)
			exec_pipe(data, token, NULL, -1);
	}
	else
		simple_exec(data, token);
	dup2(data->files->saved_in, STDIN_FILENO);
	dup2(data->files->saved_out, STDOUT_FILENO);
	close(data->files->saved_in);
	close(data->files->saved_out);
	close_all(data->hd->hdfd, data->hd->nb_hd);
	free_hd(data);
	return ;
}

void	exec_pipe(t_data *data, t_token *token, char *result, int i)
{
	while (++i < data->pipe->nb_pipe + 1 && token != NULL)
	{
		result = formatting(data, NULL, token);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			if (result == NULL)
				exit(EXIT_FAILURE);
			if (redirection(data, token, i) == 1)
				exit(EXIT_FAILURE);
			if (is_builtin(token->str) == 1)
				exec_builtin(data, token, 1, 0);
			else
				ft_execute(data, build_command_tab(token));
		}
		next_hd(data, token);
		token = token->next;
		while (token != NULL && ft_strncmp(token->before->base, "|", 2) != 0)
			token = token->next;
	}
	close_all(data->pipe->pipefd, data->pipe->nb_pipe);
	ft_wait(data, -1);
	free_pipe(data);
}

void	simple_exec(t_data *data, t_token *token)
{
	char	*result;

	result = formatting(data, NULL, token);
	data->pid1 = fork();
	if (data->pid1 == 0)
	{
		if (result == NULL)
			exit(EXIT_FAILURE);
		if (redirection(data, token, 0) == 1)
			exit(EXIT_FAILURE);
		if (is_builtin(token->str) == 1)
			exec_builtin(data, token, 0, 0);
		else
			ft_execute(data, build_command_tab(token));
	}
	ft_wait(data, -2);
	if (result != NULL)
		exec_builtin_base(data, token);
	return ;
}

void	exec_builtin(t_data *data, t_token *token, int info, int exit_status)
{
	if (ft_strncmp(token->str, "echo", ft_strlen("echo") + 1) == 0)
		exit_status = ft_echo(token->next);
	else if (ft_strncmp(token->str, "pwd", ft_strlen("pwd") + 1) == 0)
		exit_status = pwd();
	else if (ft_strncmp(token->str, "env", ft_strlen("env") + 1) == 0)
		exit_status = env(data->env, token->next);
	else if (info == 1 && ft_strncmp(token->str, "exit", ft_strlen("exit") + 1) == 0)
		exit_status = ft_exit(data, token->next);
	else if (info == 1 && ft_strncmp(token->str, "cd", ft_strlen("cd") + 1) == 0)
		exit_status = cd(data, token->next, ft_getenv("HOME", data));
	else if (info == 1 && ft_strncmp(token->str, "export", ft_strlen("export") + 1) == 0)
		exit_status = export(data, token->next);
	else if (info == 1 && ft_strncmp(token->str, "unset", ft_strlen("unset") + 1) == 0)
		exit_status = unset(data, token->next);
	if (exit_status == 1)
	{
		free_data(data);
		exit(EXIT_FAILURE);
	}
	if (exit_status == 0)
	{
		free_data(data);
		exit(EXIT_SUCCESS);
	}
}

void	exec_builtin_base(t_data *data, t_token *token)
{
	if (ft_strncmp(token->str, "cd", ft_strlen("cd") + 1) == 0)
		data->last_exit_status = cd(data, token->next, ft_getenv("HOME", data));
	else if (ft_strncmp(token->str, "export", ft_strlen("export") + 1) == 0)
		data->last_exit_status = export(data, token->next);
	else if (ft_strncmp(token->str, "unset", ft_strlen("unset") + 1) == 0)
		data->last_exit_status = unset(data, token->next);
	else if (ft_strncmp(token->str, "exit", ft_strlen("exit") + 1) == 0)
		data->last_exit_status = ft_exit(data, token->next);
	return ;
}
