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

void			*hm_insert_node(t_hash_map *hm, t_hm_node *node, t_hm_node *new)
{
	if (node->next) {
		t_hm_node *node_next = node->next;
		node->next = new;
		new->prev = node;
		new->next = node_next;
		node_next->prev = new;
	}
	else {
		node->next = new;
		node->next->prev = node;
		hm->last_node = new;
	}
	hm->size++;
	return (new->value);
}

