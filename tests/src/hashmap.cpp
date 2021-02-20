#include <catch2/catch.hpp>

/*
 * Catch2: examples
 * for more examples checkout:
 *   https://github.com/catchorg/Catch2/tree/devel/examples
 *
 * Catch has two natural expression assertion macro's:
 * - REQUIRE() stops at first failure.
 * - CHECK() continues after failure.
 *
 * There are two variants to support decomposing negated expressions:
 * - REQUIRE_FALSE() stops at first failure.
 * - CHECK_FALSE() continues after failure.
 *
 * TEST_CASE( "Title here", "[short name]" ) {
 *     REQUIRE( [BOOLEAN CONDITION] ) ;
 * }
 */

extern "C" {
# include "hashmap.h"
# include "libft.h"
}

#include <stdio.h>
#define HM_SIZE 1000

TEST_CASE( "create_destroy hashmap", "[hashmap]" ) {
	void *hashmap = hm_new(HM_SIZE);
	REQUIRE(hashmap != NULL);
	hm_destroy(hashmap);
}

TEST_CASE( "hm_set hashmap", "[hashmap]" ) {
	void *hashmap = hm_new(HM_SIZE);
	int i = 0;
	while(i < 5)
	{
		char *key = ft_strdup("HELLO");
		char *value = ft_strdup("this");
		REQUIRE(hm_set(hashmap, key, value) != NULL);
		free(key);
		free(value);
		i++;
	}
	hm_destroy(hashmap);
}
