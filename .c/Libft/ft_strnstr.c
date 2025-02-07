/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:42:11 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/01 10:39:52 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	length;
	int		i;

	i = 0;
	length = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0' && len >= ft_strlen(little))
	{
		if (ft_strncmp(big + i, little, length) == 0)
			return ((char *)big + i);
		len--;
		i++;
	}
	return (NULL);
}
