/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:04:19 by jverdier          #+#    #+#             */
/*   Updated: 2025/01/28 13:52:27 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checking(t_token *token)
{
	while (token != NULL)
	{
		if (is_double(token) == 1)
			return (1);
		if (is_red_ok(token) == 1)
			return (1);
		if (is_pipe_ok(token) == 1)
			return (1);
		token = token->next;
	}
	return (0);
}
