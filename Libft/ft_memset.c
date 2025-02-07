/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:33:37 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/01 10:38:12 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p_s;
	unsigned char	c_char;

	p_s = (unsigned char *)s;
	c_char = (unsigned char)c;
	while (n > 0)
	{
		*p_s++ = c_char;
		n--;
	}
	return (s);
}
