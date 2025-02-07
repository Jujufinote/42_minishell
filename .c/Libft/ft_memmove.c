/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:33:25 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/01 10:38:05 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*p_dest;
	unsigned const char	*p_src;

	if (!dest && !src)
		return (NULL);
	p_dest = dest;
	p_src = src;
	if (p_src <= p_dest && n > 0)
	{
		p_dest += n - 1;
		p_src += n - 1;
		while (n > 0)
		{
			*p_dest-- = *p_src--;
			n--;
		}
	}
	else
		p_dest = ft_memcpy(dest, src, n);
	return (dest);
}
// p_dest is a pointer on the 1st dest's cell at the beginning
// (stock dest's 1st cell's adress)
// same for p_src but with src
// *p_dest is the value in the cell
// same for src
