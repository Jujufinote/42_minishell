/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:42:37 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/01 11:07:21 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	c_char;
	unsigned int	len;
	const char		*str;

	len = ft_strlen(s);
	c_char = (unsigned char)c;
	str = s + len;
	while (len + 1)
	{
		if ((unsigned char)*str == c_char)
			return ((char *)str);
		str--;
		len--;
	}
	return (NULL);
}
