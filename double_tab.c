/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:01:19 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/18 15:50:22 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **table)
{
	int	i;
	int	j;

	i = 0;
	while (table[i] != NULL)
	{
		j = 0;
		while (table[i][j] != '\0')
		{
			write(1, &table[i][j], 1);
			++j;
		}
		write(1, "\n", 1);
		++i;
	}
	return ;
}

int	find_len(t_token *token)
{
	int	len;

	len = 0;
	while (token != NULL && ft_strncmp(token->str, "|", 2) != 0)
	{
		if (is_redirection(token->str) == 1)
			token = token->next->next;
		if (token != NULL && is_operator(token->str) != 1)
		{
			++len;
			token = token->next;
		}
	}
	return (len);
}

char	**build_command_tab(t_token *token)
{
	char	**table;
	int		i;
	int		length;
	
	length = find_len(token);
	table = malloc(sizeof(char *) * (length + 1));
	if (table == NULL)
		return (ft_putstr_fd("Error in memory allocation\n", 2), NULL);
	i = 0;
	while (i < length && token != NULL && ft_strncmp(token->str, "|", 2) != 0)
	{
		if (is_redirection(token->str) == 1)
			token = token->next->next;
		if (token != NULL && is_operator(token->str) != 1)
		{
			table[i] = ft_strdup(token->str);
			if (table[i] == NULL)
				return (ft_putstr_fd("Error in memory allocation\n", 2), NULL);
			++i;
			token = token->next;
		}
	}
	table[i] = NULL;
	return (table);
}
