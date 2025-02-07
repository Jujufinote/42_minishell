/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:45:12 by jverdier          #+#    #+#             */
/*   Updated: 2025/02/06 16:09:03 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_data *data)
{
	t_token	*token;

	token = *data->tokens;
	data->nb_pipe = count_pipe(token);
	data->files->saved_in = dup(STDIN_FILENO);
	data->files->saved_out = dup(STDOUT_FILENO);
	if (data->nb_pipe > 0)
		exec_pipe(data, token, -1);
	else if (token->str[0] == '<' && token->str[1] == '<')
		data->last_exit_status = exec_heredoc(data, token->next, 0);
	else
		simple_exec(data, token);
	dup2(data->files->saved_in, STDIN_FILENO);
	dup2(data->files->saved_out, STDOUT_FILENO);
	close(data->files->saved_in);
	close(data->files->saved_out);
	return ;
}

void	exec_pipe(t_data *data, t_token *token, int i)
{
	if (prep_pipe(data) == 1)
		return ;
	while (++i < data->nb_pipe + 1)
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			if (redirection(data, token, i) == 1)
				exit(EXIT_FAILURE);
			if (is_builtin(token->str) == 1)
				exec_builtin(data, token);
			else
				ft_execute(build_command_tab(token), data->paths, data->env);
		}
		token = token->next;
		while (token != NULL && ft_strncmp(token->before->str, "|", 2) != 0)
			token = token->next;
	}
	ft_wait(data, -1);
	close_all(data->pipefd, data->nb_pipe);
	free_pipe(data);
	return ;
}

void	simple_exec(t_data *data, t_token *token)
{
	data->pid1 = fork();
	if (data->pid1 == 0)
	{
		if (redirection(data, token, 0) == 1)
			return ;
		if (is_builtin(token->str) == 1)
			exec_builtin(data, token);
		ft_execute(build_command_tab(token), data->paths, data->env);
	}
	ft_wait(data, -2);
	return ;
}

void	exec_builtin(t_data *data, t_token *token)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strncmp(token->str, "echo", ft_strlen("echo")) == 0)
		exit_status = ft_echo(token->next);
	else if (ft_strncmp(token->str, "cd", ft_strlen("cd")) == 0)
		exit_status = cd(data, token->next);
	else if (ft_strncmp(token->str, "pwd", ft_strlen("pwd")) == 0)
		exit_status = pwd(data);
	else if (ft_strncmp(token->str, "export", ft_strlen("export")) == 0)
		exit_status = export(data, token->next);
	else if (ft_strncmp(token->str, "unset", ft_strlen("unset")) == 0)
		exit_status = unset(data, token->next);
	else if (ft_strncmp(token->str, "env", ft_strlen("env")) == 0)
		exit_status = env(data->env, token->next);
	else if (ft_strncmp(token->str, "exit", ft_strlen("exit")) == 0)
		exit_status = ft_exit(data);
	if (exit_status == 1)
		exit(EXIT_FAILURE);
	if (exit_status == 0)
		exit(EXIT_SUCCESS);
	return ;
}
