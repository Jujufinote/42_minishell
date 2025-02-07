/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusdepomme <jusdepomme@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:07:48 by jverdier          #+#    #+#             */
/*   Updated: 2024/05/02 17:56:36 by jusdepomme       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	nb_nb;
	int	result;
	int	sign;

	nb_nb = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr) == 1)
	{
		result = result * 10 + (*nptr - 48);
		nptr++;
		nb_nb++;
	}
	if (nb_nb > 20)
		return (-1);
	return (result * sign);
}
