#ifndef HASHMAP_INTERNAL_H
# define HASHMAP_INTERNAL_H

# include <stdlib.h>
# include <stdint.h>
# include "libft.h"
# include "hashmap.h"

typedef struct s_hm_node {
	struct s_hm_node		*next;
	struct s_hm_node		*prev;
	char				*key;
	void				*value;
}		t_hm_node;

typedef struct s_hash_map {
	t_hm_node		**nodes;
	t_hm_node		*first_node;
	t_hm_node		*last_node;
	t_hm_node		*history;
	size_t			collisions;
	size_t			cap;
	size_t			size;
}		t_hash_map;

uint64_t	hash(const size_t cap, const char *key);
t_hm_node			*new_node(const char *_key, void *_value);
void			add_node_to_history(t_hm_node **root, t_hm_node *node);
void			history_destroy(t_hm_node *root, void (*f)(void *));
t_hm_node		*find_node_by_key(t_hm_node *_node, const char *_key);
void			node_remove_from_list(t_hash_map *_hm, t_hm_node *_node);
void			*hm_add_new_key(t_hash_map *hm, t_hm_node **node, const char *_key, void *_value);
void				node_destroy(t_hm_node *_to_destroy, void (*_ft_delete)(void*));
void			*hm_find_existing_node_and_replace_value(t_hash_map *hm,
													t_hm_node *node_at_index,
													const char *_key,
													void *_value);
void			*hm_insert_node(t_hash_map *hm, t_hm_node *node, t_hm_node *new);
void			*hm_handle_collision(t_hash_map *hm,
													t_hm_node *node,
													const char *_key,
													void *_value);


#endif
