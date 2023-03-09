/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngalzand <ngalzand@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:15:56 by ngalzand          #+#    #+#             */
/*   Updated: 2022/11/22 13:15:58 by ngalzand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*get_next_line(int fd);
int			read_next_line(int fd, char **temp);
char		*create_newline(char *temp);
char		*remake_temp(char *temp);
size_t		ft_strlen_gnl(const char *s);
char		*ft_freetmp_gnl(char **temp, char **line, int freeline);
long int	contain_char_gnl(char *s);
char		*ft_strjoin_gnl(char *s1, char *s2);
void		*ft_calloc_gnl(size_t count, size_t size);

#endif
