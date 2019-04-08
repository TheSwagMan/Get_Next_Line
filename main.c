/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:57:17 by tpotier           #+#    #+#             */
/*   Updated: 2019/04/09 00:41:46 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>



int		strncat_mal(char **s1, char *s2, size_t n);
int	main(void)
{
	char	*s;

	while (get_next_line(0, &s) > 0)
	{
		ft_putendl(s);
	}
	ft_putstr("ok");
	return (0);
}
