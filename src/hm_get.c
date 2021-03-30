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

void	*hm_get(const void *_hm, const char *_key)
{
	const t_hash_map	*hm = (t_hash_map *)_hm;
	t_hm_node		*node;

	if (_key == NULL)
		return (NULL);
	node = hm->nodes[hash(hm->cap, _key)];
	if (node && node->next)
	{
		while (node)
		{
			if (ft_strcmp(node->key, _key) == 0)
				return (node->value);
			node = node->next;
		}
		return (NULL);
	}
	else if (node)
		return (node->value);
	else
		return (NULL);
}
