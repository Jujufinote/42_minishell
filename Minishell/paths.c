/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:40:46 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/20 18:31:05 by jverdier         ###   ########.fr       */
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

int		ft_is_file(char *path)
{
	struct stat st;

	if (stat(path, &st) == 0)
	{
		if (S_ISREG(st.st_mode))
			return (0);
	}
	return (1);
}

char	*ft_access(char **envp, char *cmd)
{
	char	**paths;
	char	*path;

	if (cmd == NULL)
		return (NULL);
	if (*cmd != '\0' && ft_is_file(cmd) == 0 && access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		ft_putstr_fd(cmd, 2);
		return (ft_putstr_fd(" : Permission denied\n", 2), NULL);
	}
	paths = make_paths(envp);
	path = verif_path(paths, cmd);
	free_dtab(paths);
	return (path);
}

char	*verif_path(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*path2;

	i = -1;
	while (paths != NULL && *cmd != '\0' && paths[++i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		if (path == NULL)
			return (perror("Error in memory allocation "), NULL);
		path2 = ft_strjoin(path, cmd);
		free(path);
		if (path2 == NULL)
			return (perror("Error in memory allocation "), NULL);
		if (ft_is_file(path2) == 0 && access(path2, F_OK) == 0)
		{
			if (access(path2, X_OK) == 0)
				return (path2);
			ft_putstr_fd(cmd, 2);
			return (ft_putstr_fd(" : Permission denied\n", 2), free(path2), NULL);
		}
		free(path2);
	}
	ft_putstr_fd(cmd, 2);
	return (ft_putstr_fd(" : Command not found\n", 2), NULL);
}
