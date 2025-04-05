/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrakoton <jrakoton@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 09:17:07 by jrakoton          #+#    #+#             */
/*   Updated: 2025/02/17 10:12:29 by jrakoton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *str1, char *str2);
int		ft_strlen_gnl(char *str);
int		ft_check_ending(char *str);
int		ft_get_index(char *str);
char	*ft_get_second(char *str);
char	*ft_get_first(char *str);
char	*ft_strdup_gnl(char *s);

#endif
