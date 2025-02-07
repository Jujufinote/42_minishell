/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:58:20 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/01 10:40:05 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char const	*beginning;
	char const	*end;
	char		*trimmed;
	int			trimmed_length;

	if (!set)
		return ((char *)s1);
	beginning = s1;
	end = s1 + ft_strlen(s1) - 1;
	while (ft_isset(*beginning, set) == 1 && beginning)
		beginning += 1;
	while (ft_isset(*end, set) == 1 && end > beginning)
		end -= 1;
	if (end >= beginning)
		trimmed_length = end - beginning + 1;
	else
		trimmed_length = 0;
	trimmed = (char *)malloc(sizeof(char) * (trimmed_length + 1));
	if (trimmed == NULL)
		return (NULL);
	if (!s1)
		*trimmed = '\0';
	ft_strlcpy(trimmed, beginning, trimmed_length + 1);
	return (trimmed);
}
