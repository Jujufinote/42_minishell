/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:34:11 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/01 10:38:58 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	c_char;

	c_char = (unsigned char)c;
	while (*s != '\0')
	{
		if ((unsigned char)*s == c_char)
			return ((char *)s);
		s++;
	}
	if (c_char == '\0')
		return ((char *)s);
	return (NULL);
}
