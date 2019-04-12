/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:57:17 by tpotier           #+#    #+#             */
/*   Updated: 2019/04/12 20:40:36 by tpotier          ###   ########.fr       */
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

	fds = (int *)malloc((argc - 1) * sizeof(*fds));
	n = -1;
	while (++n < argc - 1)
		fds[n] = open(argv[n + 1], O_RDONLY);
	n = 0;
	s = NULL;
	while (1)
	{
		if (get_next_line(fds[n], &s) > 0)
		{
			ft_putnbr(n);
			ft_putstr(") ");
			ft_putendl(s);
			free(s);
		}
		n = (n + 1) % (argc - 1);
	}
	return (0);
}
