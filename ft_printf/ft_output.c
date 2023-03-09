/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:56:34 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/15 13:09:20 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_outputformat(va_list args, char format, int fd)
{
	if (format == '%')
		return (ft_putchar('%', fd));
	else if (format == 'c')
		return (ft_putchar(va_arg(args, int), fd));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *), fd));
	else if (format == 'p')
		return (ft_putpointer(va_arg(args, void *), fd));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(args, int), 0, fd));
	else if (format == 'u')
		return (ft_putunsignednbr(va_arg(args, unsigned int), 0, fd));
	else if (format == 'x')
		return (ft_puthex_lower(va_arg(args, unsigned int), 0, fd));
	else if (format == 'X')
		return (ft_puthex_upper(va_arg(args, unsigned int), 0, fd));
	return (0);
}

int	ft_output(const char *input, int fd, va_list args, size_t argsnbr)
{
	size_t			i;
	unsigned int	printlen;
	long int		printsave;

	i = 0;
	printlen = 0;
	while (input[i])
	{
		if (input[i] == '%' && input[i + 1] && ft_isformat(input[i + 1])
			&& argsnbr-- > 0)
		{
			printsave = ft_outputformat(args, input[i++ + 1], fd);
			if (printsave < 0)
				return (-1);
			printlen += printsave;
		}
		else if (input[i] != '%')
		{
			if (ft_putchar(input[i], fd) == -1)
				return (-1);
			printlen++;
		}
		i++;
	}
	return (printlen);
}
