#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"
#include "hashmap_internal.h"
#include "libft.h"

size_t	nb_nodes = 1400;
size_t	hm_size = 1000;

void	run_key_null_test(void *hashmap)
{
	printf("\n\n---------Key null test-------------------------->\n\n");
	hm_set(hashmap, NULL, "value");
	printf("%s\n\n",(char *)hm_get(hashmap, NULL));
	printf("-------------------------------------------------\n\n");
}

void	run_value_null_test(void *hashmap)
{
	printf("\n\n---------Value null test----------------------->\n\n");
	hm_set(hashmap, "key", NULL);
	printf("%s\n\n", (char *)hm_get(hashmap, "key"));
	printf("-------------------------------------------------\n\n");
}

void	generate_nodes(void *hashmap)
{
	size_t	i;
	char *buffer = malloc(sizeof(char) * 20);

	
	printf("\n\n-------------Generate random data------------->\n\n");
	i = 0;
	while (i < nb_nodes)
	{
		sprintf(buffer, "Value %zu", i);
		hm_set(hashmap, ft_strdup(buffer), ft_strdup(buffer));
		i++;
	}
	printf("nb nodes generated        -->  %zu\n", nb_nodes);
	printf("Nb Collision registered   -->  %zu\n\n",hm_get_collision_count(hashmap));
	printf("<-----------------------------------------------\n\n\n");
	}

void	print_hashmap(void *hashmap)
{
	t_pair pair;
	printf("----------------Print hash map----------------->\n\n");
	pair = hm_get_seq(hashmap);
	while ((pair.u_f.key != NULL))
	{
		printf("%s   ->   %s\n", pair.u_f.key, (char *)pair.u_s.value);
		pair = hm_get_seq(hashmap);
	}
	printf("------------------------------------------------\n\n");
}

void	run_loop_test(void *hashmap)
{

	generate_nodes(hashmap);
	print_hashmap(hashmap);
}

void	check_for_leaks(void *hashmap)
{
	hm_destroy(hashmap, free);
	system("leaks a.out");
}

void	test_ft_hm_new()
{
	void *hashmap = hm_new(100);
	hm_set(hashmap, "Key", "value");
	printf("%s\n\n", (char *)hm_get(hashmap, "Key"));
}

int		main(void)
{
	void *hashmap = hm_new(hm_size);
	run_loop_test(hashmap);
	run_value_null_test(hashmap);
	run_key_null_test(hashmap);
	test_ft_hm_new();
	check_for_leaks(hashmap);
	return (0);
}
