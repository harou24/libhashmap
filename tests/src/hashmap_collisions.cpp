#include <string.h>
#include <ctype.h>
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

#define TEST_SIZE 256
static_assert(TEST_SIZE > 0, "test requirement not met");

static void	__randinit()
{
	static bool israndinit;

	if (!israndinit) {
		srand(time(NULL));
		israndinit = true;
	}
}

static char	get_random_char()
{
	char c;
	__randinit();

	c = rand() % 127;
	while (!isprint(c)) {
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

TEST_CASE( "basics", "[hashmap]" ) {
	const size_t max_size = TEST_SIZE;
	for (size_t size = 1; size < max_size; size++) {
		void *hm = hm_new(size);
		REQUIRE(hm != NULL);
		CHECK(hm_size(hm) == 0);
		hm_destroy(hm, free);
	}
	REQUIRE(hm_new(0) == NULL);
}

TEST_CASE( "set and unset", "[hashmap]" ) {
	const size_t max_size = TEST_SIZE;
	char *key = (char *)"key";
	char *value = (char *)"value";

	for (size_t size = 1; size < max_size; size++) {
		void *hm = hm_new(size);
		REQUIRE(hm != NULL);
		CHECK(hm_set(hm, key, ft_strdup(value)) != NULL);
		CHECK(hm_set(hm, key, ft_strdup(value)) != NULL);
		hm_remove(hm, key, free);
		CHECK(hm_get(hm, key) == NULL);
		CHECK(hm_set(hm, key, ft_strdup(value)) != NULL);
		CHECK(hm_get(hm, key) != NULL);
		hm_destroy(hm, free);
	}
	REQUIRE(hm_new(0) == NULL);
}

TEST_CASE( "collisions with various sizes", "[hashmap]" ) {
	const size_t max_size = TEST_SIZE;
	char *key = (char *)"key";
	char *value = (char *)"value";

	for (size_t size = 1; size < max_size; size++) {
		void *hm = hm_new(size);
		REQUIRE(hm != NULL);

		for (size_t i = 0; i < 2 * size; i++) {
			char *v = ft_strdup(value);
			REQUIRE(hm_set(hm, key, v) != NULL);
		}
		CHECK(hm_size(hm) == 2 * size);
		hm_destroy(hm, free);
	}
}

TEST_CASE( "collisions with various sizes and multiple of the same key", "[hashmap]" ) {
	const size_t max_size = TEST_SIZE;
	char *key = (char *)"key";
	char *value = (char *)"value";

	for (size_t size = 1; size < max_size; size++) {
		void *hm = hm_new(size);
		REQUIRE(hm != NULL);

		for (size_t i = 0; i < TEST_SIZE; i++) {
			char *v = ft_strdup(value);
			REQUIRE(hm_set(hm, key, v) != NULL);
		}
		CHECK(hm_size(hm) == TEST_SIZE);
		CHECK(hm_get(hm, key));
		CHECK(strcmp((char *)hm_get(hm, key), value) == 0);
		hm_destroy(hm, free);
	}
}

TEST_CASE( "collisions with various sizes and different keys", "[hashmap]" ) {
	const size_t max_size = TEST_SIZE;
	for (size_t size = 1; size < max_size; size++) {
		void *hm = hm_new(size);
		REQUIRE(hm != NULL);

		for (size_t i = 0; i < TEST_SIZE; i++) {
			char *key = (char *)malloc(TEST_SIZE);
			key[TEST_SIZE - 1] = '\0';
			char *value = ft_strdup("value");
			CHECK(hm_set(hm, key, value) != NULL);
			free(key);
		}
		CHECK(hm_size(hm) == TEST_SIZE);
		hm_destroy(hm, free);
	}
}

TEST_CASE( "collisions for random keys/values with various sizes and different keys", "[hashmap]" ) {
	const size_t max_size = TEST_SIZE;
	for (size_t size = 1; size < max_size; size++) {
		void *hm = hm_new(size);
		REQUIRE(hm != NULL);

		for (size_t i = 1; i < TEST_SIZE; i++) {
			const size_t keylen = i;
			const size_t valuelen = i;
			char *key = (char *)malloc(keylen);
			fill_string_with_random_ascii(key, keylen);
			char *value = (char *)malloc(valuelen);
			fill_string_with_random_ascii(value, valuelen);
			CHECK(hm_set(hm, key, value) != NULL);
			free(key);
		}
		CHECK(hm_size(hm) == TEST_SIZE - 1);
		hm_destroy(hm, free);
	}
}
