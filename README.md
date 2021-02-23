# libhashmap
[![build](https://github.com/harou24/libhashmap/workflows/Unittests/badge.svg)](https://github.com/harou24/libhashmap/actions?workflow=Unittests)
[![linux](https://github.com/harou24/libhashmap/workflows/Linux/badge.svg)](https://github.com/harou24/libhashmap/actions?workflow=Linux)
[![macos](https://github.com/harou24/libhashmap/workflows/MacOS/badge.svg)](https://github.com/harou24/libhashmap/actions?workflow=MacOS)

Hash map implementation in C in collaboration with Stan Verschuuren (https://github.com/s-t-a-n).

### Features
- when hm_set() is called, a hash is calculated for the given key and a lookup takes place based on that key
- collision-handling: if there is collision, it is checked whether the key already has a value (it is updated) or if this is a new key (it is appended)
- the lifetime of the 'key' given as an argument to  hm_set() is bound to the hashmap (it is strdupped)
- the lifetime of the 'value' given as an argument to hm_set() is external to the hashmap (external manipulation is possible)
- all 'value' given as argument to hm_set() should not be freed outside of the hashmap -> hm_destroy() will free all 'value' arguments using the given 'void (*f)(void *)' function pointer argument.

### Flaws:
- All linked list operations should be seperated from hash_map operations
- Library is not Norminette (42 stylechecker) compliant
- Many functions should be split up into seperate functions for readability.
