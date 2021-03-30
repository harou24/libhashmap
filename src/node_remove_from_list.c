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

void			node_remove_from_list(t_hash_map *_hm, t_hm_node *_node)
{
	if (_node->prev)
		_node->prev->next = _node->next;
	else
		_hm->first_node = _node->next;
	if (_node->next)
		_node->next->prev = _node->prev;
	else
		_hm->last_node = _node->prev;
}

