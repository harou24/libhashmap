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

void			*hm_find_existing_node_and_replace_value(t_hash_map *hm,
													t_hm_node *node_at_index,
													const char *_key,
													void *_value)
{
	void			*old_value;
	t_hm_node		*prev;

	prev = node_at_index;
	while (node_at_index->next)
	{
		node_at_index = node_at_index->next;
		if (ft_strcmp(node_at_index->key, _key) == 0)
		{
			/* we found the same key */
			old_value = node_at_index->value;

			/* dead key, add to history -> IS THIS NECCESSARY?*/
			add_node_to_history(&hm->history, new_node(node_at_index->key, old_value));

			node_at_index->value = _value;
			return (NULL);
		}
		prev = node_at_index;
	}
	return (prev);
}

