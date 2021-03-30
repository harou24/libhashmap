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

uint64_t	hash(const size_t cap, const char *key)
{
	uint64_t			value;
	size_t 				i;
	size_t				length;

	value = 0;
	i = 0;
	length = ft_strlen(key);
	while (i < length)
	{
		value = value * 37 +  key[i];
		i++;
	}
	value = value % cap;
	return (value);
}

