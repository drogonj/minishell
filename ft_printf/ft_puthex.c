/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:22:05 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/15 12:47:20 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_lower(unsigned long int n, size_t len, int fd)
{
	const char	base[17] = "0123456789abcdef";
	int			lentmp;

	lentmp = 0;
	if (n >= 16)
	{
		lentmp = ft_puthex_lower(n / 16, len, fd);
		if (lentmp == -1)
			return (-1);
		len += lentmp;
		ft_puthex_lower(n % 16, len, fd);
	}
	else
	{
		if (ft_putchar(base[n], fd) == -1)
			return (-1);
	}
	return (++len);
}

int	ft_puthex_upper(unsigned long int n, size_t len, int fd)
{
	const char	base[17] = "0123456789ABCDEF";
	int			lentmp;

	lentmp = 0;
	if (n >= 16)
	{
		lentmp = ft_puthex_upper(n / 16, len, fd);
		if (lentmp == -1)
			return (-1);
		len += lentmp;
		ft_puthex_upper(n % 16, len, fd);
	}
	else
	{
		if (ft_putchar(base[n], fd) == -1)
			return (-1);
	}
	return (++len);
}
