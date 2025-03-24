/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:12:53 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/23 15:14:35 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_alloc(char **env)
{
	int		len;

	len = 0;
	while (env[len] != NULL)
		++len;
	return (malloc(sizeof(char *) * (len)));
}

int	*pid_alloc(int nb_commands)
{
	int	*pid;

	pid = malloc(sizeof(pid_t) * nb_commands);
	if (!pid)
		return (NULL);
	return (pid);
}

int	**pipefd_alloc(int nb_pipes)
{
	int	**pipefd;

	pipefd = (int **)malloc(sizeof(int *) * nb_pipes);
	if (!pipefd)
		return (NULL);
	pipefd = make_pipefds(pipefd, nb_pipes);
	if (pipefd == NULL)
		return (NULL);
	return (pipefd);
}
