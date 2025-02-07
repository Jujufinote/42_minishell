/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:32:52 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/01 10:37:48 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*p_s;
	unsigned char		c_char;

	p_s = (unsigned char *)s;
	c_char = (unsigned char)c;
	while (n > 0)
	{
		if (*p_s++ == c_char)
			return ((void *)p_s - 1);
		n--;
	}
	return (NULL);
}
