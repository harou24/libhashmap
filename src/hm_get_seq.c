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

static	void	set_pair_to_null(t_pair *pair)
{
	pair->u_f.key = NULL;
	pair->u_s.value = NULL;
}

t_pair	hm_get_seq(const void *_hm)
{
	const t_hash_map	*hm = (t_hash_map *)_hm;
	static t_hm_node	*node;
	t_pair				pair;

	if (_hm == NULL)
	{
		node = NULL;
		set_pair_to_null(&pair);
		return (pair);
	}
	if (node != NULL)
		node = node->next;
	else
		node = hm->first_node;
	if (node)
	{
		pair.u_f.key = node->key;
		pair.u_s.value = node->value;
	}
	else
	{
		node = hm->first_node;
		set_pair_to_null(&pair);
	}
	return (pair);
}
