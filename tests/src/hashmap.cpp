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
#define HM_SIZE 100

TEST_CASE( "create_destroy hashmap", "[hashmap]" ) {
	void *hashmap = hm_new(HM_SIZE);
	REQUIRE(hashmap != NULL);
	hm_destroy(hashmap, free);
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
		i++;
	}
	hm_destroy(hashmap, free);
}

TEST_CASE("hm_set further testing", "[hashmap]")
{
	void *hashmap = hm_new(HM_SIZE);
	extern char **environ;
	char	**env = environ;
	int i = 0;
	while (i < 15)
	{
		char *key = ft_substr(env[i], 0, 5);
		char *value = ft_substr(env[i], 6, ft_strlen(env[i]));
		REQUIRE(hm_set(hashmap, key, value) != NULL);
		free(key);
		i++;
	}
	hm_destroy(hashmap, free);
}

TEST_CASE("hm_remove test", "[hashmap]")
{
	void *hashmap = hm_new(HM_SIZE);
	extern char **environ;
	char	**env = environ;
	int i = 0;
	while (i < 15)
	{
		char *key = ft_substr(env[i], 0, 5);
		char *value = ft_substr(env[i], 6, ft_strlen(env[i]));
		REQUIRE(hm_set(hashmap, key, value) != NULL);
		free(key);
		i++;
	}
	char *to_remove = ft_strdup("SHELL");
	hm_remove(hashmap, to_remove, free);
	free(to_remove);
	hm_destroy(hashmap, free);
}

