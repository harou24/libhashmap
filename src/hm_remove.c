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

void	hm_remove(void *_hm, const char *_key, void (*ft_free)(void*))
{
	size_t		checksum;
	t_hash_map	*hm;
	t_hm_node	*node;

	hm = (t_hash_map *)_hm;
	checksum = hash(hm->cap, _key);
	node = hm->nodes[checksum];
	if (node)
	{
		if (ft_strcmp(node->key, _key) != 0)
		{
			if (!node->next)
				return ;
			node = find_node_by_key(node->next, _key);
			if (!node)
				return ;
		}
		node_remove_from_list(_hm, node);
		node_destroy(node, ft_free);
		hm->nodes[checksum] = NULL;
	}
}
