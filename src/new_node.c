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

t_hm_node			*new_node(const char *_key, void *_value)
{
	t_hm_node *node;
   
	node = ft_calloc(sizeof(t_hm_node), 1);
	if (node)
	{
		node->key = ft_strdup(_key);
		node->value = _value;
	}
	return (node);
}

