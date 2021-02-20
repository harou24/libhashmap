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

static uint64_t	hash(const size_t cap, const char *key)
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

static t_hm_node			*new_node(char *_key, void *_value)
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

void			*hm_new(size_t _cap)
{
	t_hash_map	*hm;

	hm = ft_calloc(sizeof(t_hash_map), 1);
	hm->nodes = ft_calloc(sizeof(t_hm_node*), _cap);
	hm->cap = _cap;
	return ((void *)hm);
}

void			hm_destroy(void *_hm, void  (*f)(void *ptr))
{
	t_hash_map	*hm;
	t_hm_node	*node;
	t_hm_node	*dnode;
	
	hm = (t_hash_map *)_hm;
	node = hm->first_node;
	while(node)
	{
		free(node->key);
		f(node->value);
		dnode = node;
		node = node->next;
		free(dnode);
	}
	free(hm->nodes);
	free(hm);
}

static void			*hm_value_set(t_hash_map *hm,
									t_hm_node	**node,
									char *_key,
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

static void			*hm_update_value_for_collision(t_hash_map *hm,
													t_hm_node *node,
													char *_key,
													void *_value)
{
	void			*old_value;
	t_hm_node		*prev;

	prev = node;
	while (node->next)
	{
		node = node->next;
		if (ft_strcmp(node->key, _key) == 0)
		{
			old_value = node->value;
			node->value = _value;
			return (old_value);
		}
		prev = node;
	}
	prev->next = new_node(_key, _value);
	if (prev->next)
	{
		prev->next->prev = prev;
		prev->next->value = _value;
		prev->next->key = _key;
		prev->next = prev->next;
		node->next->prev = prev;
		hm->size++;
		return (_value);
	}
	else
		return (NULL);
}

void				*hm_set(void *_hm,
							char *_key,
							void *_value)
{
	void		*old_value;
	t_hash_map	*hm;
	t_hm_node	**node;
	
	if (_key == NULL)
		return (NULL);
	hm = (t_hash_map *)_hm;
	node = &hm->nodes[hash(hm->cap, _key)];
	if (*node)
	{
		if (ft_strcmp((*node)->key, _key) != 0)
		{
			hm->collisions++;
			return (hm_update_value_for_collision(hm, *node, _key, _value));
		}
		else
		{
			hm->size++;
			old_value = (*node)->value;
			(*node)->value = _value;
			return (old_value);
		}
	}
	else
		return (hm_value_set(hm, node, _key, _value));
}

t_kv_pair			hm_get_seq(const void *_hm)
{
	const t_hash_map	*hm = (t_hash_map *)_hm;
	static t_hm_node	*node;
	t_kv_pair			pair;

	node = node ? node->next : hm->first_node;
	if (node)
	{
		pair.key = node->key;
		pair.value = node->value;
	}
	else
	{
		node = hm->first_node;
		pair.key = NULL;
		pair.value = NULL;
	}
	return (pair);
}

void			*hm_get(const void *_hm, const char *_key)
{
	const t_hash_map	*hm = (t_hash_map *)_hm;
	t_hm_node			*node;

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

size_t			hm_get_collision_count(void *_hm)
{
	const t_hash_map	*hm = (t_hash_map *)_hm;

	return (hm->collisions);
}
