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

void	hm_remove(void *_hm, const char *_key, void (*_ft_delete)(void*))
{
	t_hash_map	*hm;
	t_hm_node	**to_remove;

	hm = (t_hash_map *)_hm;
	to_remove = &hm->nodes[hash(hm->cap, _key)];
	if (*to_remove)
	{
		if (ft_strcmp((*to_remove)->key, _key) != 0)
		{
			if (!(*to_remove)->next)
				return ;
			*to_remove = find_node_by_key((*to_remove)->next, _key);
			if (!*to_remove)
				return ;
		}
		node_remove_from_list(_hm, *to_remove);
		node_destroy(*to_remove, _ft_delete);
	}
}
