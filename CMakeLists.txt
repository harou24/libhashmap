cmake_minimum_required(VERSION 3.5)
project(hashmap)
add_library(hashmap STATIC
src/hash_map.c
)
target_include_directories(hashmap PUBLIC
inc
lib/libft/inc
)
target_link_libraries(hashmap lib/libft)
