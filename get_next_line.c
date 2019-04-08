/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:34:43 by tpotier           #+#    #+#             */
/*   Updated: 2019/04/08 21:53:39 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Get the size of a given str until occurence of char c
** Returns 1 if the char is found else 0
*/

int		strlen_bfrchr(char *s, char c, size_t *size)
{
	if (!s || !size)
		return (0);
	*size = 0;
	while (s[*size] && s[*size] != c)
		*(size++);
	return (*s[size] ? 1 : 0);
}

/*
** Reallocates and cat a new str to a given str (only n chars + '\0')
** Given str can be NULL and the return value will just be a copy of the str
** to cat.
** return 1 on success
*/

int		strncat_mal(char **s1, char *s2, size_t n)
{
	char	*new;
	size_t	k;
	size_t	i;

	if (n == 0 || !s1)
		return (0);
	i = 0;
	if (*s1)
		i = ft_strlen(*s1);
	if (!(new = (char *)malloc((i + n + 1) * sizeof(char))))
		return (0);
	k = 0;
	while (*s1 && k < i)
	{
		new[k] = (*s1)[k];
		k++;
	}
	new[k + n] = '\0';
	while (s2 && n--)
		new[k + n] = s2[n];
	free(*s1);
	*s1 = new;
	return (1);
}

/*
** Return the a pointer on the fd corresponding to fd, and create one if none is
** found.
*/

t_fb	*get_corresponding_fd(t_list **l, int fd)
{
	t_list	*li;
	t_list	*new;

	if (!l)
		return (NULL);
	li = *l;
	while (li)
	{
		if (((t_fb *)(li->content))->fd == fd)
			return (li->content);
		li = li->next;
	}
	if (!(new = (t_list *)malloc(sizeof(*new))))
		return (NULL);
	new->next = NULL;
	if (!(new->content = (t_fb *)malloc(sizeof(t_fb))))
		return (NULL);
	((t_fb *)(new->content))->fd = fd;
	((t_fb *)(new->content))->buff = NULL;
	li = *l;
	if (!*l)
		return ((*l = new)->content);
	while (li && li->next)
		li = li->next;
	return ((li->next = new)->content);
}

void	cat_next_line(t_list *list, t_fb *fb, char **line)
{
	char	buff[BUFF_SIZE + 1];
	char	first;
	char	*temp;
	size_t	s;
	size_t	n;

	first = 1;
	while (first || (!strlen_bfrchr(temp, '\n', &s) && n))
	{
		temp = buff;
		if (fb->buff)
		{
			n = read(fd, buff, BUFF_SIZE);
			buff[n] = '\0';
		} else {
			temp = fb->buff;
			n = s;
		}
		strncat_mal(line, temp, n);
		first = 0;
	}
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*list;
	int				n;
	int				k;
	t_fb			*t;

	if (!line)
		return (-1);
	*line = NULL;
	t = get_corresponding_fd(&list, fd);
	if (t->buff)
		strncat_mal(line, t->buff, ft_strlen(t->buff));
	while ((n = read(fd, buff, BUFF_SIZE)))
	{
		buff[n] = '\0';
		k = strlen_bfrchr(buff, '\n');
		strncat_mal(line, buff, k);
		ft_putnbr(n);
		ft_putnbr(BUFF_SIZE);
		if (n != BUFF_SIZE)
			return (0);
		else
		{
			t->buff = ft_strdup(buff + k);
			return (1);
		}
	}
	return (-1);
}
