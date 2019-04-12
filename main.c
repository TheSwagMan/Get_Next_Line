/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:57:17 by tpotier           #+#    #+#             */
/*   Updated: 2019/04/13 01:20:08 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	*s;
	int		*fds;
	int		n;
	int		k;
	int		l;

	fds = (int *)malloc((argc - 1) * sizeof(*fds));
	n = -1;
	while (++n < argc - 1)
		fds[n] = open(argv[n + 1], O_RDONLY);
	n = 0;
	s = NULL;
	k = 1;
	l = -1;
	while (k < argc - 1)
	{
		if (n == 0)
		{
			l++;
			k = 0;
		}
		if (get_next_line(fds[n], &s) > 0)
		{
			ft_putstr(argv[n + 1]);
			ft_putstr(" line ");
			ft_putnbr(l);
			ft_putstr(" (");
			ft_putnbr(n);
			ft_putstr("): ");
			ft_putendl(s);
			free(s);
			s = NULL;
		}
		else
			k++;
		n = (n + 1) % (argc - 1);
	}
	return (0);
}
