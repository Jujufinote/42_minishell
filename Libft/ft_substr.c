/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:11:32 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/01 10:40:10 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	len_s;
	size_t			j;
	size_t			len_tot;
	char			*sub;

	len_s = ft_strlen(s);
	if (len <= 0)
		len = 0;
	if (start >= len_s)
		len_tot = 0;
	else
	{
		len_tot = len_s - start;
		if (len_tot > len)
			len_tot = len;
	}
	sub = (char *)malloc(sizeof(char) * (len_tot + 1));
	if (sub == NULL)
		return (NULL);
	j = 0;
	while (j < len_tot && s[start] != '\0' && start < len_s)
		sub[j++] = s[start++];
	sub[j] = '\0';
	return (sub);
}
