/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:55:48 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/25 15:21:17 by jverdier         ###   ########.fr       */
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
		if (sig != SIGINT && sig != SIGKILL && sig != SIGSTOP && sig != SIGCHLD && sig != SIGQUIT)
			signal(sig, SIG_IGN);
		if (sig == SIGCHLD)
			signal(sig, SIG_DFL);
		++sig;
	}
	if (info == 1)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, handler);
	}
	else
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handler_interractive);
	}
	return ;
}
