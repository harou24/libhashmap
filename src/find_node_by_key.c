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

t_hm_node		*find_node_by_key(t_hm_node *_node, const char *_key)
{
	while(_node)
	{
		if (ft_strcmp(_key, _node->key) == 0)
			break ;
		_node = _node->next;
	}
	if (!_node || ft_strcmp(_key, _node->key) != 0)
		return (NULL);
	return (_node);
}

