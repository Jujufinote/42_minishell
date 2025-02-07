/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:32:38 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/01 10:36:31 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	ft_filling(int n, char *string, int len)
{
	int	nb;

	if (n < 0)
	{
		string[0] = '-';
		n = -n;
	}
	while (n >= 10)
	{
		nb = n % 10;
		string[len - 1] = nb + 48;
		n /= 10;
		len--;
	}
	if (n < 10)
		string[len - 1] = n + 48;
	return ;
}

char	*ft_itoa(int n)
{
	char	*string;
	int		len;

	if (n == -2147483648)
		len = 11;
	else
		len = ft_len(n);
	string = (char *)malloc(sizeof(char) * (len + 1));
	if (string == NULL)
		return (NULL);
	string[len] = '\0';
	if (n == -2147483648)
	{
		ft_filling(n + 1, string, len);
		string[10] = '8';
	}
	else
		ft_filling(n, string, len);
	return (string);
}
