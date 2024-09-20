/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:47:54 by jeportie          #+#    #+#             */
/*   Updated: 2024/09/20 17:22:13 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_split.h"

static void	ft_free_memory(char **tab, size_t i)
{
	while (i > 0)
	{
		i--;
		free(tab[i]);
	}
}

static size_t	ft_substr_len(char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

static size_t	ft_count_words(char *str, char c)
{
	size_t	nb_words;

	nb_words = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
		{
			nb_words++;
			while (*str && *str != c)
				str++;
		}
	}
	return (nb_words);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

static char	*ft_extract(const char **s, char c, char **tab, size_t i)
{
	size_t	word_len;
	char	*word;

	while (**s && **s == c)
		(*s)++;
	word_len = ft_substr_len((char *)*s, c);
	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!word)
	{
		ft_free_memory(tab, i);
		return (NULL);
	}
	ft_strlcpy(word, *s, word_len + 1);
	*s += word_len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	words;
	size_t	i;

	if (!s)
		return (NULL);
	words = ft_count_words((char *)s, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < words)
	{
		tab[i] = ft_extract(&s, c, tab, i);
		if (!tab[i])
		{
			free(tab);
			return (NULL);
		}
		i++;
	}
	if (i != words)
		return (NULL);
	tab[words] = NULL;
	return (tab);
}
