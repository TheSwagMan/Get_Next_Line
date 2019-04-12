/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:34:43 by tpotier           #+#    #+#             */
/*   Updated: 2019/04/12 22:58:43 by tpotier          ###   ########.fr       */
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

ssize_t	get_fd_str(char **str, t_list **l, int fd)
{
	char		*buff;
	ssize_t		size;

	buff = (char *)malloc((BUFF_SIZE + 1) * sizeof(*buff));
	*str = del_fd(l, fd);
	if (*str)
		return (ft_strlen(*str));
	size = read(fd, buff, BUFF_SIZE);
	buff[size] = '\0';
	*str = ft_strdup(buff);
	return (size);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*states = NULL;
	ssize_t			s;
	char			*str;
	int				to_ret;

	*line = NULL;
	str = NULL;
	to_ret = 10;
	while (1)
	{
		if ((s = get_fd_str(&str, &states, fd)) < 0)
			to_ret = -1;
		if (to_ret == 10 && ft_strlen_bfrchr(str, '\n', (size_t *)&s))
		{
			str[s] = '\0';
			set_fd(&states, ft_strdup(str + s + 1), fd);
			to_ret = ft_strncat_mal(line, str, (size_t)s) ? 1 : -1;
		}
		to_ret = (to_ret == 10 && s == 0) ? 0 : to_ret;
		to_ret = (to_ret == 10 && !ft_strncat_mal(line, str, s)) ? -1 : to_ret;
		(void)(to_ret != 10 ? free(str) : 0);
		if (to_ret != 10)
			return (to_ret);
	}
}
