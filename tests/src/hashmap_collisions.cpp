#include <string.h>
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

void	__randinit()
{
	static bool israndinit;

	if (!israndinit) {
		srand(time(NULL));
		israndinit = true;
	}
}

char	get_random_char()
{
	char c;
	__randinit();

	c = rand() % 127;
	while (c != 9 && c != 10 && c <= 32 && c >= 127) {
		c = rand() % 127;
	}
	return (c);
}

static void fill_string_with_random_ascii(char *buf, size_t buflen)
{
	for (size_t i = 0; i < buflen; i++) {
		buf[i] = get_random_char();
	}
	buf[buflen - 1] = '\0';
}

TEST_CASE( "collisions with various sizes", "[hashmap]" ) {
	const size_t max_size = 10000;
	for (size_t size = 0; size < max_size; size++) {
		void *hm = hm_new(size);
		REQUIRE(hm != NULL);
		hm_destroy(hm, free);
	}
}

TEST_CASE( "collisions with various sizes and multiple of the same key", "[hashmap]" ) {
	const size_t max_size = 1024;
	char *key = (char *)"key";
	char *value = (char *)"value";

	for (size_t size = 0; size < max_size; size++) {
		void *hm = hm_new(size);
		REQUIRE(hm != NULL);

		size_t i = 0;
		while(i < 1024)
		{
			char *v = ft_strdup(value);
			REQUIRE(hm_set(hm, key, v) != NULL);
			i++;
		}
		REQUIRE(hm_get(hm, key));
		CHECK(strcmp((char *)hm_get(hm, key), value) == 0);
		hm_destroy(hm, free);
	}
}

TEST_CASE( "collisions with various sizes and different keys", "[hashmap]" ) {
	const size_t max_size = 10000;
	for (size_t size = 0; size < max_size; size++) {
		void *hm = hm_new(size);
		REQUIRE(hm != NULL);

		size_t i = 0;
		while(i < 10000)
		{
			char *key = (char *)malloc(1024);
			key[1023] = '\0';
			char *value = ft_strdup("value");
			REQUIRE(hm_set(hm, key, value) != NULL);
			free(key);
			i++;
		}
		hm_destroy(hm, free);
	}
}

TEST_CASE( "collisions for random keys/values with various sizes and different keys", "[hashmap]" ) {
	const size_t max_size = 1024;
	for (size_t size = 0; size < max_size; size++) {
		void *hm = hm_new(size);
		REQUIRE(hm != NULL);

		size_t i = 0;
		while(i < 1024)
		{
			const size_t keylen = i;
			const size_t valuelen = i;
			char *key = (char *)malloc(keylen);
			fill_string_with_random_ascii(key, keylen);
			char *value = (char *)malloc(valuelen);
			fill_string_with_random_ascii(value, valuelen);
			REQUIRE(hm_set(hm, key, value) != NULL);
			free(key);
			i++;
		}
		hm_destroy(hm, free);
	}
}
