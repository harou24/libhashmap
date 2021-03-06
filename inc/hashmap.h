/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hash_map.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: haachtch <haachtch@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/13 09:37:49 by haachtch      #+#    #+#                 */
/*   Updated: 2020/09/03 13:25:32 by haachtch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBHASHMAP_H
# define LIBHASHMAP_H

#include <stddef.h>
#include "pair.h"

void			*hm_new(size_t _size);
void			hm_destroy(void *_hm, void (*f)(void *));
void			*hm_set(void *_hm, char *_key, void *_value);
void			*hm_get(const void *_hm, const char *_key);
t_pair		hm_get_seq(const void *_hm);
size_t			hm_get_collision_count(void *_hm);
void			hm_remove(void *_hm, char *_key, void (*_ft_delete)(void*));

#endif
