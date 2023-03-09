/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:10:46 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/15 12:48:10 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_putstr(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return (ft_putstr("(null)", fd));
	while (s[i])
	{
		if (ft_putchar(s[i], fd) == -1)
			return (-1);
		i++;
	}
	return (i);
}
