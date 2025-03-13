/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:08:52 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/13 13:43:57 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_data *data)
{
	char	*input;

	while (1)
	{
		input = readline("\033[1;37mminishell $ \033[0m");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		prep_exec(data, input);
		free(input);
		lstdel(data->tokens);
		free(data->tokens);
		data->tokens = NULL;
	}
}

void	handler_interractive(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	char	*str;
	char	*value;
	int		shlvl;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	if (init(data, envp) == 1)
		return (free(data), ft_putstr_fd("Error in memory allocation\n", 2), 1);
	value = ft_getenv("SHLVL", data);
	shlvl = ft_atoi(value) + 1;
	value = ft_itoa(shlvl);
	str = ft_strjoin("SHLVL=", value);
	free(value);
	modif_env(data, str);
	free(str);
	signal(SIGINT, handler_interractive);
	signal(SIGQUIT, SIG_IGN);
	prompt(data);
	rl_clear_history();
	free_data(data);
	return (0);
}
