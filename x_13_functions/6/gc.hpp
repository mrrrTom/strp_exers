#ifndef _MINI_GC
#define _MINI_GC
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <setjmp.h>
#include <string.h>
#include <vector>

using namespace std;

void mini_gc_free(void *ptr);
void* mini_gc_malloc(size_t req_size);
void garbage_collect(void);
void gc_init(void);
void add_roots(void * start, void * end);

struct header {
    size_t flags;
    size_t size;
    header* next_free;
};

struct gc_heap {
    header *slot;
    size_t size;
};

constexpr int TINY_HEAP_SIZE = 0x4000;
constexpr int PTRSIZE = ((size_t) sizeof(void *));
constexpr int HEADER_SIZE = ((size_t) sizeof(header));
constexpr int HEAP_LIMIT = 10000;
constexpr int ALIGN(int x, int a) { return ((x) + (a - 1)) & ~(a - 1); }
inline header* NEXT_HEADER(header* x) { return (header*)((size_t)(x+1) + x->size); }

/* flags */
constexpr int FL_ALLOC = 0x1;
constexpr int FL_MARK = 0x2;
inline void FL_SET(void* x, int f) { ((header *)x)->flags |= f; }
inline void FL_UNSET(void* x, int f) { ((header*)x)->flags &= ~(f); }
inline int FL_TEST(void* x, int f) {  return (((header *)x)->flags & f); }

static header* free_list;
static vector<gc_heap> gc_heaps; // <= HEAP_LIMIT
static size_t gc_heaps_used = 0;

struct root_range {
    void * start;
    void * end;
};

inline bool IS_MARKED(void* x) { return (FL_TEST(x, FL_ALLOC) && FL_TEST(x, FL_MARK)); }
constexpr int ROOT_RANGES_LIMIT = 1000;

static vector<root_range> root_ranges; // <= ROOT_RANGES_LIMIT
static size_t root_ranges_used = 0;
static void * stack_start = NULL;
static void * stack_end = NULL;
static gc_heap *hit_cache = NULL;
#endif
