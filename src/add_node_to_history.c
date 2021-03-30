/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: haachtch <haachtch@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 09:34:21 by haachtch      #+#    #+#                 */
/*   Updated: 2020/09/03 14:12:42 by haachtch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap_internal.h"

void			add_node_to_history(t_hm_node **root, t_hm_node *node)
{
	t_hm_node *lst;

	if (!*root)
	{
		(*root) = node;
	}
	else
	{
		lst = *root;
		while(lst->next)
			lst = lst->next;
		lst->next = node;
	}
}

