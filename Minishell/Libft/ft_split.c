/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jverdier <jverdier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:46:46 by jverdier          #+#    #+#             */
/*   Updated: 2024/03/02 15:20:24 by jverdier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

static int	ft_count(char const *s, char c)
{
	int	word;
	int	i;

	word = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (i == 0 && s[i] != c)
			word++;
		else if (s[i] == c && s[i + 1] != c \
				&& s[i + 1] != '\0')
			word++;
		i++;
	}
	return (word);
}

static void	ft_free(char **array, int j)
{
	while (j >= 0)
	{
		free(array[j]);
		j--;
	}
	free(array);
	return ;
}

static int	filling(char const *s, char c, int word, char **array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (word > 0)
	{
		while (s[i] == c)
			i++;
		array[j] = ft_substr(s, i, length(&s[i], c));
		if (array[j] == NULL)
		{
			ft_free(array, j);
			return (0);
		}
		i += length(&s[i], c);
		j++;
		word--;
	}
	array[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		word;

	word = ft_count(s, c);
	array = (char **)malloc(sizeof(char *) * (word + 1));
	if (array == NULL)
	{
		free(array);
		return (NULL);
	}
	if (filling(s, c, word, array) == 0)
		return (NULL);
	return (array);
}
