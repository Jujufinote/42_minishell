/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:45:32 by jverdier          #+#    #+#             */
/*   Updated: 2025/04/02 16:17:20 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_sorted(t_data *data, char **sorted, int i)
{
	int		j;

	sorted = create_env(data->env);
	if (sorted == NULL)
	{
		ft_putstr_fd("Error in memory allocation\n", 2);
		return (1);
	}
	bubble_sort_tab(sorted);
	while (sorted[++i] != NULL)
	{
		printf("declare -x ");
		j = 0;
		while (sorted[i][j] != 0 && sorted[i][j] != '=')
		{
			printf("%c", sorted[i][j]);
			++j;
		}
		if (sorted[i][j] == '=')
			printf("%c\"%s\"\n", sorted[i][j], &sorted[i][j + 1]);
		else
			printf("\n");
	}
	free_dtab(sorted);
	return (0);
}

void	print_tab(char **table)
{
	int	i;

	i = 0;
	while (table[i] != NULL)
	{
		if (ft_strchr(table[i], '=') != NULL)
			printf("%s\n", table[i]);
		++i;
	}
	return ;
}

void	print_token_echo(t_token *token)
{
	while (token != NULL && ft_strncmp(token->base, "|", 2) != 0)
	{
		if (is_redirection(token) == 1)
			token = token->next;
		else if (token != NULL)
		{
			printf("%s", token->str);
			if (find_next_arg(token->next) == 1)
				printf(" ");
		}
		token = token->next;
	}
	return ;
}

/*void	printlst(t_token **p_token)
{
	t_token	*token;

	if (p_token == NULL)
		return ;
	token = *p_token;
	printf("\n");
	while (token != NULL)
	{
		printf("before : %p\nnow : %p\nbase : %s\npost_str : %s\nstr : 
		%s\nop = %d
		\nfile = %d\nnext : %p\nnow : %p\n\n", token->before, token, token->base,
		token->post_str, token->str, token->op, token->file, token->next, token);
		token = token->next;
	}
	return ;
}*/
