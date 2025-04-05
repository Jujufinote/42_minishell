/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   signals.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jverdier <jverdier@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/25 13:55:48 by jverdier		  #+#	#+#			 */
/*   Updated: 2025/04/05 15:32:47 by jverdier		 ###   ########.fr	   */
/*																			*/
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

void	signal_handler(int info, int sig)
{
	struct sigaction	sa;

	while (sig < _NSIG)
	{
		if (sig == SIGCHLD || sig == SIGPIPE)
		{
			sa.sa_handler = SIG_DFL;
			sigemptyset(&sa.sa_mask);
			sa.sa_flags = SA_RESTART;
			sigaction(sig, &sa, NULL);
		}
		else if (sig != SIGINT && sig != SIGQUIT \
		&& sig != SIGKILL && sig != SIGSTOP)
		{
			sa.sa_handler = SIG_IGN;
			sigemptyset(&sa.sa_mask);
			sa.sa_flags = SA_RESTART;
			sigaction(sig, &sa, NULL);
		}
		++sig;
	}
	is_interractive(sa, info);
}

void	is_interractive(struct sigaction sa, int info)
{
	if (info == 1)
	{
		sa.sa_handler = handler;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
	
		sa.sa_handler = SIG_DFL;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = handler_interractive;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
	
		sa.sa_handler = SIG_IGN;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		sigaction(SIGQUIT, &sa, NULL);
	}
	return ;
}
