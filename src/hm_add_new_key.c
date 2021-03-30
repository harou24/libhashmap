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

void			*hm_add_new_key(t_hash_map *hm,
									t_hm_node	**node,
									const char *_key,
									void *_value)
{
	*node = new_node(_key, _value);
	if (*node)
	{
		hm->size++;
		if (!hm->last_node)
		{
			hm->first_node = *node;
			hm->last_node = *node;
		}
		else
		{
			hm->last_node->next = *node;
			(*node)->prev = hm->last_node;
			hm->last_node = *node;
		}
		return (_value);
	}
	else
		return (NULL);
}

