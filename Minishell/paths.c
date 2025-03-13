/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:40:46 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/13 12:20:41 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_paths(char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	path = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			path = envp[i];
		i++;
	}
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i] && path[i] != '=')
		i++;
	i++;
	paths = ft_split(path + i, ':');
	if (paths == NULL)
		return (NULL);
	return (paths);
}

char	*ft_access(char **envp, char *cmd)
{
	char	**paths;
	char	*path;

	if (cmd == NULL)
		return (NULL);
	if (*cmd != '\0' && access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	paths = make_paths(envp);
	path = verif_path(paths, cmd);
	free(paths);
	if (path != NULL)
		return (path);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : Command not found\n", 2);
	return (NULL);
}

char	*verif_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*path2;

	i = 0;
	while (paths != NULL && *cmd != '\0' && paths[i] != NULL)
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
	return (NULL);
}
