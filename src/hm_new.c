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

void	*hm_new(size_t _cap)
{
	t_hash_map	*hm;

	if (_cap == 0)
		return (NULL);
	hm = ft_calloc(sizeof(t_hash_map), 1);
	hm->nodes = ft_calloc(sizeof(t_hm_node *), _cap);
	hm->cap = _cap;
	return ((void *)hm);
}
