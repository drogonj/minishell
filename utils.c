/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcherrie <fcherrie@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:41:45 by fcherrie          #+#    #+#             */
/*   Updated: 2023/02/03 13:41:48 by fcherrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contain_char(char *s, char c)
{
	int	i;

	i = -1;
	if (!s)
		return (-1);
	while (s[++i])
		if (s[i] == c)
			return (i);
	return (-1);
}

void	*ft_realloc_tab(char **ptr, size_t new_size)
{
	void		*new_ptr;
	int			i;

	i = 0;
	if (ptr == NULL)
		return (ft_calloc(1, new_size));
	if (new_size == 0)
	{
		ft_free_tab(ptr);
		return (0);
	}
	while (ptr[i] != 0)
		i++;
	new_ptr = ft_calloc(1, new_size);
	ft_memcpy_msh(new_ptr, ptr, i);
	ft_free_tab(ptr);
	return (new_ptr);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

char	*ft_strjoin_msh(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*ptr;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!ptr)
		return (0);
	while (s1[j])
		ptr[i++] = s1[j++];
	j = 0;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}

void	*ft_memcpy_msh(char **dst, char **src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			ft_free_tab(dst);
			return (0);
		}
		i++;
	}
	return (dst);
}
