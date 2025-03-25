/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:55:48 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/25 14:15:50 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	signal_handler(int info)
{
	int	sig;

	sig = 1;
	while (sig < _NSIG)
	{
		if (sig != SIGINT)
			signal(sig, SIG_IGN);
		++sig;
	}
	if (info == 1)
		signal(SIGINT, handler);
	else
		signal(SIGINT, handler_interractive);
	return ;
}
