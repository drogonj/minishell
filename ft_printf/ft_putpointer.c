/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:40:05 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/15 12:47:54 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putpointer(void *ptr, int fd)
{
	int	len;
	int	lentmp;

	len = 0;
	lentmp = 0;
	lentmp = ft_putstr("0x", fd);
	if (lentmp == -1)
		return (-1);
	len = ft_puthex_lower((unsigned long int)(ptr), 0, fd);
	if (len == -1)
		return (-1);
	len += lentmp;
	return (len);
}
