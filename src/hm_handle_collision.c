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

void	*hm_handle_collision(t_hash_map *hm,
				t_hm_node *node,
					const char *_key,
						void *_value)
{
	t_hm_node	*last;

	last = hm_find_existing_node_and_replace_value(hm, node, _key, _value);
	if (!last)
		return (_value);
	return (hm_insert_node(hm, node, new_node(_key, _value)));
}
