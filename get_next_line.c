/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:34:43 by tpotier           #+#    #+#             */
/*   Updated: 2019/04/09 01:14:25 by tpotier          ###   ########.fr       */
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

int		get_next_line(const int fd, char **line)
{
	static char	*rest = NULL;
	char		buff[BUFF_SIZE + 1];
	size_t		s;

	*line = NULL;
	while (1)
	{
		if (rest)
		{
			strcpy(buff, rest);
			free(rest);
			rest = NULL;
			s = ft_strlen(buff);
		}
		else
			s = read(fd, buff, BUFF_SIZE);
		buff[s] = '\0';
		if (strlen_bfrchr(buff, '\n', &s))
		{
			buff[s] = '\0';
			rest = ft_strdup(buff + s + 1);
			if (!strncat_mal(line, buff, s))
				return (-1);
			return (1);
		}
		if (s == 0)
			return (0);
		if (!strncat_mal(line, buff, s))
			return (-1);
	}
}
