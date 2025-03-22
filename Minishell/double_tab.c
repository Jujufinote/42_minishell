/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:01:19 by jverdier          #+#    #+#             */
/*   Updated: 2025/03/21 14:24:24 by jverdier         ###   ########.fr       */
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
	while (token != NULL && ft_strncmp(token->post_str, "|", 2) != 0)
	{
		if (is_redirection(token->str) == 1)
			token = token->next->next;
		if (token != NULL && is_operator(token->str) == 0)
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
	while (i < length && token != NULL && ft_strncmp(token->post_str, "|", 2) != 0)
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

void	swap_pchar(char **p1, char **p2)
{
	char	*ptemp;

	ptemp = *p1;
	*p1 = *p2;
	*p2 = ptemp;
	return ;
}

void	bubble_sort_tab(char **sorted)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (sorted[i] != NULL)
	{
		j = i + 1;
		temp = i;
		while (sorted[j] != NULL)
		{
			if (ft_strncmp(sorted[temp], sorted[j], ft_strlen(sorted[i])) > 0)
				temp = j;
			++j;
		}
		swap_pchar(&sorted[i], &sorted[temp]);
		++i;
	}
	return ;
}
