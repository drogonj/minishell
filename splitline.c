/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 16:54:29 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/13 15:55:52 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			while (line[++i] != 39)
				if (!line[i])
					return (1);
		}
		if (line[i] == 34)
		{
			while (line[++i] != 34)
				if (!line[i])
					return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_csize(const char *s, char c)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	if (c == '\0' || s == NULL)
		return (1);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			size++;
		while (s[i] != c && s[i] != '\0')
		{
			if ((s[i] == '|' || s[i] == '<' || s[i] == '>'))
				size += 2;
			i++;
		}
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	if (s[i - 1] != c)
		size++;
	return (size);
}

static char	*ft_createstr(const char *src, char c)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i] != '\0')
		i++;
	dest = (char *)ft_calloc(i + 1, sizeof(char));
	i = -1;
	while (src[++i] != '\0')
	{
		if (src[i] == c && check_quote(dest) == 0)
			break ;
		if ((i > 0 && (src[i] == '|' || src[i] == '<' || src[i] == '>'))
			&& check_quote(dest) == 0)
			break ;
		dest[i] = src[i];
		if ((src[i + 1] == '<' || src[i + 1] == '>') && src[i] == src[i + 1])
			dest[i + 1] = src[i + 1];
		if ((src[i] == '|' || src[i] == '>' || src[i] == '<')
			&& check_quote(dest) == 0)
			break ;
	}
	return (dest);
}

char	**ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i] != NULL)
	{
		free(tab[i++]);
	}
	free(tab);
	return (NULL);
}

char	**splitline(const char *s, char c)
{
	int		i;
	char	**tab;

	i = 0;
	if (!s || (s && s[0] == '\0'))
		return (0);
	tab = (char **)ft_calloc(sizeof(char *), ft_csize(s, c) + 1);
	if (!(tab))
		return (NULL);
	while (*s == c && *s != '\0' && s != NULL)
		s++;
	while (*s != '\0' && s != NULL)
	{
		tab[i] = ft_createstr(s, c);
		if (tab[i] == NULL)
			return (ft_free_tab(tab));
		s += ft_strlen(tab[i]) - 1;
		i++;
		if (*s != '\0')
			s++;
		while (*s == c && *s != '\0')
			s++;
	}
	tab[i] = 0;
	return (tab);
}
