/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:34:43 by tpotier           #+#    #+#             */
/*   Updated: 2019/04/10 18:56:55 by tpotier          ###   ########.fr       */
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
		(*size)++;
	return (s[*size] == c ? 1 : 0);
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

	if (!s1)
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

char	*del_fd(t_list *l, int fd)
{
	t_list	*prev;
	char	*s;

	prev = NULL;
	while (l)
	{
		if (((t_fb *)l->content)->fd == fd)
		{
			if (!prev)
				prev = l;
			if (prev->next && prev->next->next)
				prev->next = prev->next->next;
			else
				prev->next = NULL;
			s = ((t_fb *)l->content)->buff;
			free(l->content);
			free(l);
			return (s);
		}
		prev = l;
		l = l->next;
	}
	return (NULL);
}

ssize_t	get_fd_str(char **str, t_list *l, int fd)
{
	char		buff[BUFF_SIZE + 1];
	ssize_t		size;

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

	*line = NULL;
	str = NULL;
	while (1)
	{
		s = get_fd_str(&str, states, fd);
		if (s < 0)
			return (-1);
		if (strlen_bfrchr(str, '\n', (size_t *)&s))
		{
			str[s] = '\0';
			set_fd(&states, ft_strdup(str + s + 1), fd);
			if (!strncat_mal(line, str, (size_t)s))
			{
				free(str);
				return (-1);
			}
			free(str);
			return (1);
		}
		if (s == 0)
		{
			free(str);
			return (0);
		}
		if (!strncat_mal(line, str, s))
		{
			free(str);
			return (-1);
		}
	}
}
