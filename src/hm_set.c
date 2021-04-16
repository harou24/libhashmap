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

static void	*__set(t_hash_map *hm, t_hm_node **node,
			const char *_key, void *_value)
{
	void	*old_value;

	if (ft_strcmp((*node)->key, _key) != 0)
	{
		hm->collisions++;
		return (hm_handle_collision(hm, *node, _key, _value));
	}
	else
	{
		hm->size++;
		old_value = (*node)->value;
		(*node)->value = _value;
		add_node_to_history(&hm->history, new_node((*node)->key,
				old_value));
		return ((*node)->value);
	}
}

void	*hm_set(void *_hm,
			const char *_key,
				void *_value)
{
	t_hash_map	*hm;
	t_hm_node	**node;

	if (_key == NULL)
		return (NULL);
	hm = (t_hash_map *)_hm;
	node = &hm->nodes[hash(hm->cap, _key)];
	if (*node)
		return (__set(hm, node, _key, _value));
	else
		return (hm_add_new_key(hm, node, _key, _value));
}
