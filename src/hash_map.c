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

#include <assert.h>

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

static void			add_node_to_history(t_hm_node **root, t_hm_node *node)
{
	t_hm_node *lst;

	if (!*root)
	{
		(*root) = node;
	}
	else
	{
		lst = *root;
		while(lst->next)
			lst = lst->next;
		lst->next = node;
	}
}

static void			history_destroy(t_hm_node *root, void (*f)(void *))
{
	t_hm_node *prev;

	while(root)
	{
		prev = root;
		root = root->next;
		f(prev->value);
		free(prev->key);
		free(prev);
	}
}

void			*hm_new(size_t _cap)
{
	t_hash_map	*hm;

	if (_cap == 0)
		return (NULL);
	hm = ft_calloc(sizeof(t_hash_map), 1);
	hm->nodes = ft_calloc(sizeof(t_hm_node*), _cap);
	hm->cap = _cap;
	return ((void *)hm);
}

void			hm_destroy(void *_hm, void (*f)(void *))
{
	t_hash_map	*hm;
	t_hm_node	*node;
	t_hm_node	*dnode;
	
	hm = (t_hash_map *)_hm;
	node = hm->first_node;
	while(node)
	{
		dnode = node;
		node = node->next;
		f(dnode->value);
		free(dnode->key);
		free(dnode);
	}
	free(hm->nodes);
	history_destroy(hm->history, f);
	free(hm);
}

void		hm_remove(void *_hm, char *_key, void (*_ft_delete)(void*))
{
	t_hash_map	*hm;
	t_hm_node	*node;
	
	if (!_key)
		return;
	hm = (t_hash_map *)_hm;
	node = hm->first_node;
	while(node)
	{
		if (ft_strcmp(_key, node->key) == 0)
			break ;
		node = node->next;
	}
	if (ft_strcmp(_key, node->key) != 0)
		return;
	if (node->prev)
		node->prev->next = node->next;
	else
		hm->first_node = node->next;
	if (node->next)
		node->next->prev = node->prev;
	else
		hm->last_node = node->prev;
	free(node->key);
	_ft_delete(node->value);
	free(node);
}

static void			*hm_add_new_key(t_hash_map *hm,
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
			assert(!hm->first_node);
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

static void			*hm_find_existing_node_and_replace_value(t_hash_map *hm,
													t_hm_node *node_at_index,
													char *_key,
													void *_value)
{
	void			*old_value;
	t_hm_node		*prev;

	assert(node_at_index);
	assert(_key);
	prev = node_at_index;
	while (node_at_index->next)
	{
		node_at_index = node_at_index->next;
		if (ft_strcmp(node_at_index->key, _key) == 0)
		{
			/* we found the same key */
			old_value = node_at_index->value;

			/* dead key, add to history -> IS THIS NECCESSARY?*/
			add_node_to_history(&hm->history, new_node(node_at_index->key, old_value));

			node_at_index->value = _value;
			return (NULL);
		}
		prev = node_at_index;
	}
	return (prev);
}

static void			*hm_insert_node(t_hash_map *hm, t_hm_node *node, t_hm_node *new)
{
	assert(node);
	assert(new);
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

static void			*hm_handle_collision(t_hash_map *hm,
													t_hm_node *node,
													char *_key,
													void *_value)
{
	t_hm_node *last;

	last = hm_find_existing_node_and_replace_value(hm, node, _key, _value);
	if (!last) /* NULL indicates a key was found */
		return (_value);

	/* only gets here if this is a different key */
	return (hm_insert_node(hm, node, new_node(_key, _value)));
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
			/* a collision happened */
			hm->collisions++;
			assert(hm->first_node);
			assert(hm->last_node);
			assert(((*node)->prev || (*node)->next) || hm->size == 1);
			return (hm_handle_collision(hm, *node, _key, _value));
		}
		else
		{
			/* update value for key */
			hm->size++;
			old_value = (*node)->value;
			(*node)->value = _value;

			/* store ref to old value here */
			add_node_to_history(&hm->history, new_node((*node)->key, old_value));
			return ((*node)->value);
		}
	}
	else
		return (hm_add_new_key(hm, node, _key, _value));
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

	/* verify with strcmp if key is actually key ? */

	if (node && node->next)
	{
		/* check for collision */
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
