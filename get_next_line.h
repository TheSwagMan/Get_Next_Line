/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:35:08 by tpotier           #+#    #+#             */
/*   Updated: 2019/04/07 19:51:47 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <string.h>
# include "libft.h"

# define BUFF_SIZE 32

typedef struct	s_fb
{
	char		*buff;
	int			fd;
}				t_fb;

int				get_next_line(const int fd, char **line);
t_fb			*get_corresponding_fd(t_list **l, int fd);
size_t			strlen_bfrchr(char *s, char c);
int				strncat_mal(char **s1, char *s2, size_t n);

#endif
