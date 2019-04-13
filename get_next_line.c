/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:34:43 by tpotier           #+#    #+#             */
/*   Updated: 2019/04/13 03:20:11 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Return the a pointer on the fd corresponding to fd, and create one if none is
** found.
*/

void	set_fd(t_list **l, char *str, int fd)
{
	t_list	*li;
	t_list	*new;

	if (!l)
		return ;
	if (!(new = (t_list *)malloc(sizeof(*new))))
		return ;
	new->next = NULL;
	if (!(new->content = (t_fb *)malloc(sizeof(t_fb))))
	{
		free(new);
		return ;
	}
	((t_fb *)(new->content))->fd = fd;
	((t_fb *)(new->content))->buff = str;
	li = *l;
	if (!*l)
		*l = new;
	else
	{
		while (li->next)
			li = li->next;
		li->next = new;
	}
}

int		check_fd(void *content, size_t size, void *comp)
{
	(void)size;
	return (((t_fb *)content)->fd == *(int *)comp);
}

char	*del_fd(t_list **l, int fd)
{
	t_fb	*last_occ;
	char	*s;

	if (!(last_occ = ft_lstdelif(l, &check_fd, &fd, NULL)))
		return (NULL);
	s = last_occ->buff;
	free(last_occ);
	return (s);
}

int		get_fd_str(char **str, t_list **l, int fd, ssize_t *s)
{
	char		*buff;

	*str = del_fd(l, fd);
	if (*str)
	{
		*s = ft_strlen(*str);
		return (0);
	}
	buff = (char *)malloc((BUFF_SIZE + 1) * sizeof(*buff));
	*s = read(fd, buff, BUFF_SIZE);
	if (*s < 0)
	{
		free(buff);
		return (-1);
	}
	buff[*s] = '\0';
	*str = ft_strdup(buff);
	free(buff);
	if (*s == BUFF_SIZE)
		return (0);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*states = NULL;
	ssize_t			s;
	char			*str;
	int				eof;

	if (!line || (*line = NULL))
		return (-1);
	str = NULL;
	while (1)
	{
		if ((eof = get_fd_str(&str, &states, fd, &s)) < 0)
			return (-1);
		if (eof && s == 0)
			return (*line && ft_strlen(*line) ? 1 : 0);
		if (ft_strlen_bfrchr(str, '\n', (size_t *)&s))
		{
			str[s] = '\0';
			eof = 1;
			set_fd(&states, ft_strdup(str + s + 1), fd);
		}
		ft_strncat_mal(line, str, (size_t)s);
		free(str);
		if (eof)
			return (1);
	}
}
