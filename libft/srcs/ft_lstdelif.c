/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 18:41:05 by tpotier           #+#    #+#             */
/*   Updated: 2019/04/12 19:55:39 by tpotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstdelif(t_list **alst, int (*cond)(void *, size_t),
			void (*del)(void *, size_t))
{
	t_list	*prev;
	t_list	*l;
	void	*to_return;

	if (!alst || !cond || !del)
		return (NULL);
	prev = NULL;
	to_return = NULL;
	while (l)
	{
		if (cond(l->content, l->content_size))
		{
			del(l->content, l->content_size);
			to_return = l->content;
			if (prev)
				prev->next = l->next;
			else
				*alst = l->next;
			free(l);
		}
		prev = l;
		l = l->next;
	}
	return (to_return);
}
