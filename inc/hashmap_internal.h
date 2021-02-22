#ifndef LIBHASHMAP_INTERNAL_H
# define LIBHASHMAP_INTERNAL_H

# include <stdlib.h>
# include <stdint.h>
# include "libft.h"
# include "hashmap.h"

typedef struct			s_hm_node {
	char				*key;
	void				*value;
	struct s_hm_node	*next;
	struct s_hm_node	*prev;
}						t_hm_node;

typedef struct			s_hash_map {
	t_hm_node			**nodes;
	t_hm_node			*first_node;
	t_hm_node			*last_node;
	t_hm_node			*history;
	size_t				collisions;
	size_t				cap;
	size_t				size;
}						t_hash_map;

#endif
