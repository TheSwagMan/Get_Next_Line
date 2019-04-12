/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_bfrchr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 20:17:01 by tpotier           #+#    #+#             */
/*   Updated: 2019/04/12 22:41:09 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Get the size of a given str until occurence of char c
** Returns 1 if the char is found else 0
*/

int		ft_strlen_bfrchr(char *s, char c, size_t *size)
{
	if (!s || !size)
		return (0);
	*size = 0;
	while (s[*size] && s[*size] != c)
		(*size)++;
	return (s[*size] == c ? 1 : 0);
}
