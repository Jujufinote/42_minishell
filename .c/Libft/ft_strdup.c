/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:34:39 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/01 11:27:52 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;
	int		s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (!s)
		s_len = 0;
	dup = (char *)malloc(sizeof(char) * (s_len + 1));
	if (dup == NULL)
		return (NULL);
	while (i < s_len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
