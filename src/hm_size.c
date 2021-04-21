#include "hashmap_internal.h"

size_t	hm_size(const void *_hm)
{
	const t_hash_map	*hm = (t_hash_map *)_hm;

	return (hm->size);
}
