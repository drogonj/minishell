/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:35:09 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/15 13:20:47 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int			ft_printf(int fd, const char *input, ...);
int			ft_putchar(char c, int fd);
int			ft_putstr(char *s, int fd);
int			ft_putnbr(int n, size_t len, int fd);
int			ft_putunsignednbr(unsigned int n, size_t len, int fd);
int			ft_puthex_lower(unsigned long int n, size_t len, int fd);
int			ft_puthex_upper(unsigned long int n, size_t len, int fd);
int			ft_putpointer(void *ptr, int fd);
int			ft_isformat(char c);
size_t		ft_argcount(const char *input);
int			ft_output(const char *input, int fd, va_list args, size_t argsnbr);
int			ft_outputformat(va_list args, char format, int fd);

#endif
