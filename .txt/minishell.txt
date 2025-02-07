/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:08:52 by jverdier          #+#    #+#             */
/*   Updated: 2025/02/03 12:03:15 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig;

void	prompt(t_data *data)
{
	char	*input;
	
	while (1)
	{
		input = readline("\n\033[1;37mminishell $ \033[0m");
		if (input == NULL)
		{
			printf("%s%s%s\nExit\n%s", STD, BOLD, GREEN, RES);
			break ;
		}
		if (*input != '\0')
			add_history(input);
		if (*input != '\0' && parsing(input) != 1)
		{
			data->tokens = tokenisation(data, input);
			if (data->tokens == NULL)
				ft_putstr_fd("Error in memory allocation\n", 2);
			else if (checking(*data->tokens) != 1)
				execution(data);
		}
		free(input);
		lstdel(data->tokens);
		free(data->tokens);
		data->tokens = NULL;
	}
}

//void	handler(int sig, siginfo_t *info, void *context)
void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		return ;
	return ;
}

int	main(int argc, char **argv, char **envp)
{
/*	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);*/
	t_data	*data;
	
	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (ft_putstr_fd("Error in memory allocation\n", 2), 1);
	if (init(data, envp) == 1)
		return (free(data), ft_putstr_fd("Error in memory allocation\n", 2), 1);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	g_sig = 0;
	prompt(data);
	rl_clear_history();
	free_data(data);
	return (0);
}
