/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:18:09 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/28 14:00:46 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(t_token *token, int where)
{
	if (token == NULL || token->str[0] == '|')
	{
		if (where == BEFORE)
			printf("Syntax error : missing command before pipe\n");
		else if (where == AFTER)
			printf("Syntax error : missing command after pipe\n");
		return ;
	}
	else
	{
			printf("Syntax error near unexpected token : ");
			if (token->next != NULL)
				printf("\'%s\'\n", token->next->str);
			else
				printf("\'newline\'\n");
			return ;
	}
	return ;
}
