/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:37:35 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/14 17:10:40 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_argcount(const char *input)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (input[i])
	{
		if (input[i] == '%' && ft_isformat(input[i + 1]))
			res++;
		i++;
	}
	return (res);
}
