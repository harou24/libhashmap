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

void			hm_destroy(void *_hm, void (*f)(void *))
{
	t_hash_map	*hm;
	t_hm_node	*node;
	t_hm_node	*dnode;
	
	hm = (t_hash_map *)_hm;
	node = hm->first_node;
	while(node)
	{
		dnode = node;
		node = node->next;
		f(dnode->value);
		free(dnode->key);
		free(dnode);
	}
	free(hm->nodes);
	history_destroy(hm->history, f);
	free(hm);
}

