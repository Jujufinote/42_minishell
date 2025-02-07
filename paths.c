/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:40:46 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/28 11:34:07 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_paths(char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			path = envp[i];
		i++;
	}
	i = 0;
	while (path[i] && path[i] != '=')
		i++;
	i++;
	paths = ft_split(path + i, ':');
	if (paths == NULL)
		return (NULL);
	return (paths);
}

char	*ft_access(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*path2;

	i = 0;
	if (cmd == NULL || *cmd == '\0')
		return (NULL);
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		if (path == NULL)
			return (perror("Error in memory allocation "), NULL);
		path2 = ft_strjoin(path, cmd);
		free(path);
		if (path2 == NULL)
			return (perror("Error in memory allocation "), NULL);
		if (access(path2, F_OK | X_OK) == 0)
			return (path2);
		free(path2);
		i++;
	}
	return (perror("Command not found "), NULL);
}
