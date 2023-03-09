/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:08:07 by ngalzand          #+#    #+#             */
/*   Updated: 2023/02/01 12:08:08 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**str_to_tab(char *s)
{
	char	**tab;

	tab = (char **)ft_calloc(sizeof(char *), 2);
	if (!tab)
		return (0);
	tab[0] = ft_strdup(s);
	if (!tab[0])
	{
		ft_free_tab(tab);
		return (0);
	}
	return (tab);
}

static int	calc_malloc(char *s, t_bool part)
{
	int	i;
	int	count;
	int	count_bis;

	i = -1;
	count = 0;
	count_bis = 0;
	while (s[++i] != '=')
		count++;
	while (s[++i])
		count_bis++;
	if (part == FALSE)
		return (count + 1);
	else
		return (count_bis + 1);
}

char	**ft_split_export(char *s)
{
	int		i;
	int		j;
	char	**tab;

	if (!s)
		return (0);
	i = -1;
	j = -1;
	if (contain_char(s, '=') != -1)
		tab = (char **)ft_calloc(sizeof(char *), 3);
	else
		return (str_to_tab(s));
	if (!tab)
		return (0);
	tab[0] = (char *)ft_calloc(calc_malloc(s, FALSE), sizeof(char));
	tab[1] = (char *)ft_calloc(calc_malloc(s, TRUE), sizeof(char));
	if (!tab[0])
		return (ft_free_tab(tab));
	while (s[++i] != '=')
		tab[0][++j] = s[i];
	j = -1;
	while (s[++i])
		tab[1][++j] = s[i];
	return (tab);
}
