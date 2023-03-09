/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:38:41 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/15 12:58:25 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(int fd, const char *input, ...)
{
	va_list	args;
	size_t	argsnbr;
	int		res;

	res = 0;
	argsnbr = ft_argcount(input);
	va_start(args, input);
	res = ft_output(input, fd, args, argsnbr);
	va_end(args);
	return (res);
}
